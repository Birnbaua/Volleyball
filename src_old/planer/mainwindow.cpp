/****************************************************************************
**
** Copyright (C) 2015 cfeil
** Contact:
**
** Description:
** organize volleyball tournament up to 35 teams
**
** Version:
** v1.0 ... implemented game plan system, tournament setup (time, sets, ...),
**          calculations, web views, postgresql database, reports
**
** v1.1 ... remastered system, removed web views,
**          use sqlite for datastorage
**
** v1.2 ... fixed commit bug for sqltablemodels => dont use removecolumn,
**          instead tableview => hidecolumn, add widget to show results
**          and game plan => use view_division_results in view_all_results,
**          fixed tableview input and column numbers,
**          fixed generate zwischenrunde_spielplan, fixed insert
**          fieldnumbers and fieldnames, add time calculation for whole
**          tournament
**
** v1.3 ... added game plan for 35 teams, 
**          added key events to itemdelegates, handle copy and paste, return
**          esc keys, fixed recalculate time event, added icons to widgets
**          
** v1.4 ... added game plan for 40 teams, bugfix for checkequalresults
**          in vorrunde and zwischenrunde, handling for two or more
**          equal teams, add button function to show platzierungen_view =>
**          show new window to show results, catch button click generate
**          if round was already generated
**
** v1.5 ... rebuild ergebnisse widget, uses now editable sqltablemodelnow
**          for tickets, to solve internal and external double team results
**          rebuild spiele und ergebnisse widget, get result data via views
**          bugfix add kreuzspiel gametime to start time platzspiele
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window title and icon
    this->setWindowTitle("Volleyball Tournament Organizer V1.5");
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));

    // create logging
    m_Log = new logging();
    m_Log->setFileAsLogTarget("sys.log");
    connect(m_Log, SIGNAL(logLog(QString)), this, SLOT(messageBoxCritical(QString)));
    connect(this, SIGNAL(mainLog(QString)), m_Log, SLOT(write(QString)));

    // check database file
    QFile dbFile("./resources/data.sqlite");
    if(dbFile.size() == 0)
    {
        messageBoxCritical("Die Datei '" + dbFile.fileName() + "' ist fehlerhaft, bitte überprüfen Sie die Datei!");
        endProgram();
    }

    // create database
    m_Db = new database();
    m_Db->dbIsSqlite("./resources/data.sqlite");
    connect(m_Db, SIGNAL(dbError(QString)), this, SLOT(messageBoxCritical(QString)));
    connect(m_Db, SIGNAL(dbLog(QString)), m_Log, SLOT(write(QString)));

    // open database
    if(!m_Db->openDb())
    {
        endProgram();
    }

    // string list mit gruppenkürzel a bis f
    grPrefix << "a"<< "b"<< "c"<< "d"<< "e"<< "f" << "g" << "h";
    headerPrefix << "A"<< "B"<< "C"<< "D"<< "E"<< "F" << "G" << "H";

    // update tournament time calculation
    timerUpdateTournamentTime = new QTimer(this);
    connect(timerUpdateTournamentTime, SIGNAL(timeout()), SLOT(updateTournamentTime()));

    // add clipboard management
    clipboard = QApplication::clipboard();

    // create calculations
    m_Calculate = new calculate();

    // create read/write settings
    m_Set = new settings(m_Db);
    connect(m_Set, SIGNAL(settingsLog(QString)), m_Log, SLOT(write(QString)));
    connect(m_Set, SIGNAL(updateUi(dataUi)), this, SLOT(updateSettingsToUi(dataUi)));
    connect(this, SIGNAL(updateSettings(dataUi)), m_Set, SLOT(updateUiToSettings(dataUi)));
    
    // create vorrunde
    m_Vorrunde = new vorrunde(m_Db, m_Calculate, grPrefix);
    connect(m_Vorrunde, SIGNAL(vorrundeLog(QString)), m_Log, SLOT(write(QString)));

    // create zwischenrunde
    m_Zwischenrunde = new zwischenrunde(m_Db, m_Calculate, grPrefix);
    connect(m_Zwischenrunde, SIGNAL(zwischenrundeLog(QString)), m_Log, SLOT(write(QString)));
    
    // create zwischenrunde
    m_Kreuzspiele = new kreuzspiele(m_Db, m_Calculate, grPrefix);
    connect(m_Kreuzspiele, SIGNAL(kreuzspieleLog(QString)), m_Log, SLOT(write(QString)));

    // create zwischenrunde
    m_Platzspiele = new platzspiele(m_Db, m_Calculate, grPrefix);
    connect(m_Kreuzspiele, SIGNAL(kreuzspieleLog(QString)), m_Log, SLOT(write(QString)));

    // get settings to ui
    m_Set->updateSettingsToUi();

    // get data for tableview fields
    initTableViewFields();

    // get data for tableview teams
    initTableViewTeams();

    // get data for tableview vorrunde
    initTableViewVorrunde(m_DataSettings.satzVr);
    if(m_Db->read("SELECT * FROM vorrunde_spielplan").count() > 0)
        setVorrundeParams();

    // get data for tableview zwischenrunde
    initTableViewZwischenrunde(m_DataSettings.satzZw);
    if(m_Db->read("SELECT * FROM zwischenrunde_spielplan").count() > 0)
        setZwischenrundeParams();

    // get data for tableview kreuzspiele
    initTableViewKreuzspiele(m_DataSettings.satzKr);
    if(m_Db->read("SELECT * FROM kreuzspiele_spielplan").count() > 0)
        setKreuzspieleParams();

    // get data for tableview platzspiele
    initTableViewPlatzspiele(m_DataSettings.satzPl);
    if(m_Db->read("SELECT * FROM platzspiele_spielplan").count() > 0)
        setPlatzspieleParams();

    configChanged = false;
    msChanged = false;
    vrChanged = false;
    zwChanged = false;
    krChanged = false;
    plChanged = false;

    timerUpdateTournamentTime->start(15 * 1000);
}

MainWindow::~MainWindow()
{
    endProgram();
    delete ui;
}

void MainWindow::endProgram()
{
    delete m_Platzspiele;
    delete m_Kreuzspiele;
    delete m_Zwischenrunde;
    delete m_Vorrunde;
    delete m_Set;
    delete m_Db;
    delete m_Calculate;
    delete m_Log;
}

// create critical messagebox
void MainWindow::messageBoxCritical(QString msg)
{
    QMessageBox::critical(this, "Fehler", msg, "OK");
}

// create info messagebox
void MainWindow::messageBoxInformation(QString msg)
{
    QMessageBox::information(this, "Info", msg, "OK");
}

// create messagebox
void MainWindow::messageBoxWarning(QString msg)
{
    QMessageBox::warning(this, "Warnung", msg, "OK");
}

// show games and results window
void MainWindow::on_pushButtonShowAllResultsWindow_clicked()
{
    m_VaR = new view_all_results(0, m_Db);
    m_VaR->setAttribute(Qt::WA_DeleteOnClose);
    m_VaR->setgrPrefix(grPrefix);
    m_VaR->startUpdateUi(5);
    m_VaR->show();
}

// check if user wants to continue action
bool MainWindow::userCheckButton(QString msg, QString head)
{
    QMessageBox qmb(this);
    qmb.setText(msg);
    qmb.setWindowTitle(head);
    qmb.addButton(QMessageBox::Yes);
    qmb.addButton(QMessageBox::No);
    qmb.exec();

    if (qmb.result() == QMessageBox::Yes)
        return true;

    return false;
}

// copy event
void MainWindow::copyEvent(QTableView *tv)
{
    QModelIndex index = tv->currentIndex();
    QString copyToClipboard = index.model()->data(index.model()->index(index.row(), index.column())).toString();
    clipboard->setText(copyToClipboard);
}

// paste event
void MainWindow::pasteEvent(QTableView *tv, QSqlTableModel *model)
{
    QTableView *qtv = tv;
    const QMimeData *mdata = clipboard->mimeData();

    if(mdata->hasText())
    {
        QStringList list = mdata->text().split("\n");
        int row = qtv->currentIndex().row(), col = qtv->currentIndex().column();

        foreach(QString values, list)
        {
            if(values != "")
            {
                QStringList svalues = values.split("\t");
                int scol = col;

                foreach(QString svalue, svalues)
                {
                    model->setData(model->index(row, scol), svalue);
                    scol++;
                }
            }
            if(row < model->rowCount())
                row++;
            else
                break;
        }
    }
}

// update tournament time label
void MainWindow::updateTournamentTime()
{
    QList<QVariant> var = returnTime();
    QTime time = QTime::fromString(var.at(0).toString(), "hh:mm");
    int rC = var.at(1).toInt();
    int addT = 0, addTZw = 0, addTKr = 0, addTPl = 0;
    int tC = m_Set->getTeamsCount(tmTeams);

    // add zwischenrunde
    addTZw += m_DataSettings.pauseVrZw * 60;
    addTZw += (tmVr->rowCount()) * (((m_DataSettings.satzZw * m_DataSettings.minSatzZw) + m_DataSettings.pauseMinZw) * 60)
            / m_DataSettings.anzFelder;

    // add kreuzsspiele
    switch(tC)
    {
        case 20:
            addTKr += (((m_DataSettings.satzKr * m_DataSettings.minSatzKr) + m_DataSettings.pauseMinKr) * 60) * 8 / m_DataSettings.anzFelder;
            break;
        case 25:
            addTKr += (((m_DataSettings.satzKr * m_DataSettings.minSatzKr) + m_DataSettings.pauseMinKr) * 60) * 10 / m_DataSettings.anzFelder;
            break;
        case 28:
        case 30:
        case 35:
        case 40:
            addTKr += (((m_DataSettings.satzKr * m_DataSettings.minSatzKr) + m_DataSettings.pauseMinKr) * 60) * 12 / m_DataSettings.anzFelder;
            break;
    }
    addTKr += m_DataSettings.pauseZwKr * 60;

    // add platzspiele
    addTPl += m_DataSettings.pauseKrPl * 60;
    addTPl += (((tC / 2)-1) * (((m_DataSettings.satzPl * m_DataSettings.minSatzPl)) * 60) / m_DataSettings.anzFelder)
                + (m_DataSettings.zeitFinale * 60)
                + (m_DataSettings.pausePlEhrung * 60);

    switch(rC)
    {
        case 1:
            // add time from last vorrunde game
            addT = ((m_DataSettings.satzVr * m_DataSettings.minSatzVr) + m_DataSettings.pauseMinVr) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTZw);
            time = time.addSecs(addTKr);
            time = time.addSecs(addTPl);
            break;
        case 2:
            // add time from last zwischenrunde game
            addT = ((m_DataSettings.satzZw * m_DataSettings.minSatzZw) + m_DataSettings.pauseMinZw) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTKr);
            time = time.addSecs(addTPl);
            break;
        case 3:
            // add time from last kreuzspiel game
            addT = ((m_DataSettings.satzKr * m_DataSettings.minSatzKr) + m_DataSettings.pauseMinKr) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTPl);
            break;
        case 4:
            addT = (m_DataSettings.zeitFinale * 60) + (m_DataSettings.pausePlEhrung * 60);
            time = time.addSecs(addT);
            break;
        default:
            break;
    }

    ui->labelTournamentEnd_2->setText(time.toString("hh:mm"));
}

// return last time from round
QList<QVariant> MainWindow::returnTime()
{
    if(m_Db->read("SELECT * FROM platzspiele_spielplan").count() > 0)
        return QList<QVariant>() << m_Db->read("SELECT MAX(zeit) FROM platzspiele_spielplan ORDER BY id").at(0).at(0) << 4;

    if(m_Db->read("SELECT * FROM kreuzspiele_spielplan").count() > 0)
        return QList<QVariant>() << m_Db->read("SELECT MAX(zeit) FROM kreuzspiele_spielplan ORDER BY id").at(0).at(0) << 3;

    if(m_Db->read("SELECT * FROM zwischenrunde_spielplan").count() > 0)
        return QList<QVariant>() << m_Db->read("SELECT MAX(zeit) FROM zwischenrunde_spielplan ORDER BY id").at(0).at(0) << 2;

    if(m_Db->read("SELECT * FROM vorrunde_spielplan").count() > 0)
        return QList<QVariant>() << m_Db->read("SELECT MAX(zeit) FROM vorrunde_spielplan ORDER BY id").at(0).at(0) << 1;

    return QList<QVariant>() << "00:00" << 0;
}

// get configuration and set ui controls
void MainWindow::updateSettingsToUi(dataUi settings)
{
    m_DataSettings = settings;
    
    ui->spinBoxAnzahlfelder->setValue(m_DataSettings.anzFelder);
    if(m_DataSettings.krSpiele == 1)
    {
        ui->checkBoxKreuzspiele->setChecked(true);
    }
    else
    {
        ui->checkBoxKreuzspiele->setChecked(false);
    }
    ui->timeEditStartTurnier->setTime(QTime::fromString(m_DataSettings.startTurnier));
    ui->spinBoxPauseVrZw->setValue(m_DataSettings.pauseVrZw);
    ui->spinBoxPauseZwKr->setValue(m_DataSettings.pauseZwKr);
    ui->spinBoxPauseKrPl->setValue(m_DataSettings.pauseKrPl);
    ui->spinBoxSatzVr->setValue(m_DataSettings.satzVr);
    ui->spinBoxMinProSatzVr->setValue(m_DataSettings.minSatzVr);
    ui->spinBoxPauseMinVr->setValue(m_DataSettings.pauseMinVr);
    ui->spinBoxSatzZw->setValue(m_DataSettings.satzZw);
    ui->spinBoxMinProSatzZw->setValue(m_DataSettings.minSatzZw);
    ui->spinBoxPauseMinZw->setValue(m_DataSettings.pauseMinZw);
    ui->spinBoxSatzKr->setValue(m_DataSettings.satzKr);
    ui->spinBoxMinProSatzKr->setValue(m_DataSettings.minSatzKr);
    ui->spinBoxPauseMinKr->setValue(m_DataSettings.pauseMinKr);
    ui->spinBoxSatzPl->setValue(m_DataSettings.satzPl);
    ui->spinBoxMinProSatzPl->setValue(m_DataSettings.minSatzPl);
    ui->spinBoxZeitFinale->setValue(m_DataSettings.zeitFinale);
    ui->spinBoxPausePlEhrung->setValue(m_DataSettings.pausePlEhrung);
}

// set configuration from ui controls
void MainWindow::updateUiToSettings()
{
    m_DataSettings.startTurnier = ui->timeEditStartTurnier->time().toString("hh:mm");

    if(ui->checkBoxKreuzspiele->isChecked())
        m_DataSettings.krSpiele = 1;
    else
        m_DataSettings.krSpiele = 0;

    m_DataSettings.pauseVrZw = ui->spinBoxPauseVrZw->value();
    m_DataSettings.pauseZwKr = ui->spinBoxPauseZwKr->value();
    m_DataSettings.pauseKrPl = ui->spinBoxPauseKrPl->value();
    m_DataSettings.satzVr = ui->spinBoxSatzVr->value();
    m_DataSettings.minSatzVr = ui->spinBoxMinProSatzVr->value();
    m_DataSettings.pauseMinVr = ui->spinBoxPauseMinVr->value();
    m_DataSettings.satzZw = ui->spinBoxSatzZw->value();
    m_DataSettings.minSatzZw = ui->spinBoxMinProSatzZw->value();
    m_DataSettings.pauseMinZw = ui->spinBoxPauseMinZw->value();
    m_DataSettings.satzKr = ui->spinBoxSatzKr->value();
    m_DataSettings.minSatzKr = ui->spinBoxMinProSatzKr->value();
    m_DataSettings.pauseMinKr = ui->spinBoxPauseMinKr->value();
    m_DataSettings.satzPl = ui->spinBoxSatzPl->value();
    m_DataSettings.minSatzPl = ui->spinBoxMinProSatzPl->value();
    m_DataSettings.zeitFinale = ui->spinBoxZeitFinale->value();
    m_DataSettings.pausePlEhrung = ui->spinBoxPausePlEhrung->value();
    m_DataSettings.anzFelder = ui->spinBoxAnzahlfelder->value();
    
    emit updateSettings(m_DataSettings);
}

//  init table view felder
void MainWindow::initTableViewFields()
{
    emit mainLog("INFO:: init tableview fields");
    QStringList columns;
    columns << "Feldnummer" << "Feldname";

    tmFields = m_Db->createSqlTableModel("felder", columns);
    ui->tableViewFields->setModel(tmFields);
    connect(tmFields, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(fieldsValueChanged()));
}

//  init table view felder
void MainWindow::initTableViewTeams()
{
    emit mainLog("INFO:: init tableview teams");
    QStringList columns;
    columns << "ID" << "Gruppe A" << "Gruppe B" << "Gruppe C" << "Gruppe D" 
            << "Gruppe E" << "Gruppe F" << "Gruppe G" << "Gruppe H";

    tmTeams = m_Db->createSqlTableModel("mannschaften", columns);

    ui->tableViewTeams->setModel(tmTeams);
    ui->tableViewTeams->hideColumn(0);
    connect(tmTeams, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(teamsValueChanged()));
}

// table view felder value changed
void MainWindow::fieldsValueChanged()
{
    if(!configChanged)
        emit mainLog("SETTINGS:: configuration changed");

    configChanged = true;
}

// table view teams value changed
void MainWindow::teamsValueChanged()
{
    if(!msChanged)
        emit mainLog("SETTINGS:: teams changed");

    msChanged = true;
}

// set table field row count
void MainWindow::on_spinBoxAnzahlfelder_valueChanged(int arg1)
{
    emit mainLog("INFO:: field count changed to" + QString::number(arg1));
    m_Set->setFieldsTableRows(arg1);
    initTableViewFields();
    configChanged = true;
}

// button save configuration
void MainWindow::on_pushButtonConfigSave_clicked()
{
    if(userCheckButton("Bitte bestätigen um die Turniereinstellungen zu speichern.","Turniereinstellungen"))
    {
        emit mainLog("SETTINGS:: saving configuration");
        if(m_Db->commitSqlTableModel(tmFields))
        {
            // commit changes to db
            this->updateUiToSettings();
            configChanged = false;
            messageBoxInformation("Turniereinstellungen gespeichert");
            return;
        }

        emit mainLog("ERROR:: saving configuration failed");
        messageBoxCritical("Turniereinstellungen speichern fehlgeschlagen!");
        return;
    }
    emit mainLog("INFO:: SETTINGS config aborted");
    messageBoxInformation("Turniereinstellungen speichern abgebrochen!");
}

// button rollback changes
void MainWindow::on_pushButtonConfigRollback_clicked()
{
    if(!configChanged)
    {
        emit mainLog("SETTINGS:: no configuration changed, discarding configuration aborted");
        messageBoxInformation("Keine Änderungen in der Konfiguration festgestellt, verwerfen abgebrochen!");
        return;
    }

    if(userCheckButton("Bitte bestätigen um die Änderungen in der Konfiguration zu verwerfen.","Konfiguration"))
    {
        // do db rollback
        emit mainLog("SETTINGS:: rollback configuration");
        tmFields->database().rollback();

        // read vars and set gui controls
        m_Set->updateSettingsToUi();
        initTableViewFields();

        configChanged = false;
        messageBoxInformation("Änderungen in der Konfiguration wurden verworfen");
        return;
    }

    emit mainLog("SETTINGS:: rollback configuration aborted");
    messageBoxInformation("Verwerfen der Änderungen in der Konfiguration abgebrochen");
}

// button reset config
void MainWindow::on_pushButtonConfigReset_clicked()
{
    if(userCheckButton("Bitte bestätigen um die getätigten Turniereinstellungen zu verwerfen.","Turniereinstellungen"))
    {
        // reset config
        emit mainLog("INFO:: reset configuration");
        m_Set->resetConfig();
        m_Set->updateSettingsToUi();

        messageBoxInformation("Turniereinstellungen wurden verworfen");
        configChanged = false;
        return;
    }
    emit mainLog("SETTINGS:: discard saving config aborted");
    messageBoxInformation("Turniereinstellungen verwerfen abgebrochen!");
}

void MainWindow::on_pushButtonSaveTeams_clicked()
{
    if(!msChanged)
    {
        emit mainLog("INFO:: no team value changed, abort save");
        messageBoxInformation("Keine Mannschaftsänderung durchgeführt, speichern abgebrochen!");
        return;
    }

    if(m_Set->checkDoubleTeamNames(tmTeams))
    {
        emit mainLog("INFO:: no double team names");
        if(userCheckButton("Bitte bestätigen um die Mannschaften zu speichern.","Mannschaften"))
        {
            emit mainLog("INFO:: saving teams");
            if(m_Db->commitSqlTableModel(tmTeams))
            {
                msChanged = false;
                messageBoxInformation("Mannschaften wurden gespeichert");
                return;
            }

            emit mainLog("ERROR:: saving teams failed");
            messageBoxCritical("Mannschaften speichern fehlgeschlagen!");
        }
        return;
    }

    emit mainLog("ERROR:: double team names");
    messageBoxCritical("Doppelte Mannschaftsnamen vorhanden, speichern abgebrochen!");
}

void MainWindow::on_pushButtonResetTeams_clicked()
{
    if(userCheckButton("Bitte bestätigen um die Mannschaften zu löschen.","Mannschaften"))
    {
        emit mainLog("INFO:: deleting teams");
        m_Set->resetTeams();
        initTableViewTeams();
        messageBoxInformation("Mannschaften wurden zurückgesetzt");
        msChanged = false;
        return;
    }

    emit mainLog("INFO:: deleting teams aborted");
    messageBoxInformation("Mannschaften speichern abgebrochen!");
}

void MainWindow::on_pushButtonPrintTeams_clicked()
{
    if(userCheckButton("Bitte bestätigen um Mannschaften zu drucken.","Mannschaften"))
    {
        // todo namen in pdfdatei schreiben
    }
}

// ****************************************************************************************************
// functions VORRUNDE
// ****************************************************************************************************
void MainWindow::initTableViewVorrunde(int hideCol)
{
    emit mainLog("INFO:: init tableview vorrunde");
    QStringList columns;
    m_VrItemDelegate = new itemdelegate();

    columns << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr" << "Feldname" << "Mannschaft A"
        <<"Mannschaft B" << "Schiedsgericht" << "Satz 1 A" << "Satz 1 B" << "Satz 2 A"
        << "Satz 2 B" << "Satz 3 A" << "Satz 3 B";

    tmVr = m_Db->createSqlTableModel("vorrunde_spielplan", columns);

    connect(tmVr, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(vrValueChanged()));

    ui->tableViewVorrunde->setModel(tmVr);
    ui->tableViewVorrunde->hideColumn(0);
    ui->tableViewVorrunde->setItemDelegate(m_VrItemDelegate);

    connect(m_VrItemDelegate, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyVrTableView()));
    connect(m_VrItemDelegate, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteVrTableView()));
    connect(m_VrItemDelegate, SIGNAL(enterKeyEvent()), this, SLOT(vrValueChanged()));

    switch(hideCol)
    {
        case 1: ui->tableViewVorrunde->setColumnHidden(11,true);
                ui->tableViewVorrunde->setColumnHidden(12,true);
                ui->tableViewVorrunde->setColumnHidden(13,true);
                ui->tableViewVorrunde->setColumnHidden(14,true);
                break;
        case 2: ui->tableViewVorrunde->setColumnHidden(11,false);
                ui->tableViewVorrunde->setColumnHidden(12,false);
                ui->tableViewVorrunde->setColumnHidden(13,true);
                ui->tableViewVorrunde->setColumnHidden(14,true);
                break;
        case 3: ui->tableViewVorrunde->setColumnHidden(11,false);
                ui->tableViewVorrunde->setColumnHidden(12,false);
                ui->tableViewVorrunde->setColumnHidden(13,false);
                ui->tableViewVorrunde->setColumnHidden(14,false);
                break;
    }
}

void MainWindow::setVorrundeParams()
{
    m_Vorrunde->setParams(m_DataSettings.startTurnier, m_DataSettings.satzVr, m_DataSettings.minSatzVr, m_DataSettings.pauseMinVr,
                                  m_DataSettings.anzFelder, m_Set->getTeamsCount(tmTeams), m_Set->getFieldNames());
}

void MainWindow::copyVrTableView()
{
    copyEvent(ui->tableViewVorrunde);
}

void MainWindow::pasteVrTableView()
{
    pasteEvent(ui->tableViewVorrunde, tmVr);
}

void MainWindow::vrValueChanged()
{
    if(!vrChanged)
        emit mainLog("SETTINGS:: vorrunde changed");

    switch(ui->tableViewVorrunde->currentIndex().column())
    {
        case 3: emit mainLog("INFO:: recalculate time vorrunde");
                m_Vorrunde->recalculateTimeSchedule(ui->tableViewVorrunde, tmVr);
                break;
    }

    vrChanged = true;
}

void MainWindow::vrValueChangedFinishEdit()
{
    vrValueChanged();
    ui->tableViewVorrunde->clearSelection();
}

void MainWindow::on_pushButtonVrGenerate_clicked()
{
    emit mainLog("INFO:: generate vorrunde");

    if(tmVr->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    setVorrundeParams();
    m_Vorrunde->generate();
    initTableViewVorrunde(m_DataSettings.satzVr);
    messageBoxInformation("Vorrunde wurde generiert");
    on_pushButtonVrSave_clicked();
}

void MainWindow::on_pushButtonVrClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Vorrunde zurückzusetzen.", "Vorrunde"))
    {
        emit mainLog("INFO:: deleting vorrunde");
        m_Vorrunde->clear();
        on_pushButtonVrSave_clicked();
        initTableViewVorrunde(m_DataSettings.satzVr);
        emit mainLog("Vorrundespielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit mainLog("INFO:: reset vorrunde aborted");
    messageBoxInformation("Zurücksetzen von Vorrundespielplan und Ergebnissen abgebrochen!");
}

void MainWindow::on_pushButtonVrSave_clicked()
{
    emit mainLog("INFO:: saving vorrunde");

    if(m_Db->commitSqlTableModel(tmVr))
    {
        messageBoxInformation("Vorrunde wurde gespeichert");
        m_Vorrunde->calculateResult();
        vrChanged = false;
        return;
    }

    messageBoxCritical("Vorrunde speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonVrChangeGames_clicked()
{

}

void MainWindow::on_pushButtonVrPrint_clicked()
{

}

void MainWindow::on_pushButtonVrResult_clicked()
{
    QStringList columnName;

    m_VrResults = new view_division_results(0, m_Db);
    connect(m_VrResults, SIGNAL(viewdivisionresultsLog(QString)), m_Log, SLOT(write(QString)));
    m_VrResults->setAttribute(Qt::WA_DeleteOnClose);

    columnName << "ID" << "Mannschaft" << "Satzpunkte" << "Spielpunkte" << "int. W" << "ext. W";
    m_Vorrunde->calculateResult();

    m_VrResults->init("vorrunde_erg_gr", grPrefix);

    m_VrResults->show();
}

// ****************************************************************************************************
// functions ZWISCHENRUNDE
// ****************************************************************************************************
void MainWindow::initTableViewZwischenrunde(int hideCol)
{
    emit mainLog("INFO:: init tableview zwischenrunde");
    QStringList columns;
    m_ZwItemDelegate = new itemdelegate();

    columns << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr" << "Feldname" << "Mannschaft A"
        <<"Mannschaft B" << "Schiedsgericht" << "Satz 1 A" << "Satz 1 B" << "Satz 2 A"
        << "Satz 2 B" << "Satz 3 A" << "Satz 3 B";

    tmZw = m_Db->createSqlTableModel("zwischenrunde_spielplan", columns);

    connect(tmZw, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(zwValueChanged()));

    ui->tableViewZwischenrunde->setModel(tmZw);
    ui->tableViewZwischenrunde->hideColumn(0);

    ui->tableViewZwischenrunde->setItemDelegate(m_ZwItemDelegate);
    connect(m_ZwItemDelegate, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyZwTableView()));
    connect(m_ZwItemDelegate, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteZwTableView()));
    connect(m_ZwItemDelegate, SIGNAL(enterKeyEvent()), this, SLOT(zwValueChanged()));

    switch(hideCol)
    {
        case 1: ui->tableViewZwischenrunde->setColumnHidden(11,true);
                ui->tableViewZwischenrunde->setColumnHidden(12,true);
                ui->tableViewZwischenrunde->setColumnHidden(13,true);
                ui->tableViewZwischenrunde->setColumnHidden(14,true);
                break;
        case 2: ui->tableViewZwischenrunde->setColumnHidden(11,false);
                ui->tableViewZwischenrunde->setColumnHidden(12,false);
                ui->tableViewZwischenrunde->setColumnHidden(13,true);
                ui->tableViewZwischenrunde->setColumnHidden(14,true);
                break;
        case 3: ui->tableViewZwischenrunde->setColumnHidden(11,false);
                ui->tableViewZwischenrunde->setColumnHidden(12,false);
                ui->tableViewZwischenrunde->setColumnHidden(13,false);
                ui->tableViewZwischenrunde->setColumnHidden(14,false);
                break;
    }
}

void MainWindow::setZwischenrundeParams()
{
    QStringList vrParams = m_Db->read("SELECT runde, spiel, zeit FROM vorrunde_spielplan ORDER BY id DESC LIMIT 1").at(0);
    m_Zwischenrunde->setParams(vrParams.at(2), m_DataSettings.pauseVrZw, m_DataSettings.satzZw, m_DataSettings.minSatzZw, m_DataSettings.pauseMinZw,
                                  m_DataSettings.anzFelder, m_Set->getTeamsCount(tmTeams), m_Set->getFieldNames(),
                               vrParams.at(0).toInt(), vrParams.at(1).toInt());
}

void MainWindow::copyZwTableView()
{
    copyEvent(ui->tableViewZwischenrunde);
}

void MainWindow::pasteZwTableView()
{
    pasteEvent(ui->tableViewZwischenrunde, tmZw);
}

void MainWindow::zwValueChanged()
{
    if(!zwChanged)
        emit mainLog("SETTINGS:: zwischenrunde changed");

    switch(ui->tableViewZwischenrunde->currentIndex().column())
    {
        case 3: emit mainLog("INFO:: recalculate time zwischenrunde");
                m_Zwischenrunde->recalculateTimeSchedule(ui->tableViewZwischenrunde, tmZw);
                break;
    }

    zwChanged = true;
}

void MainWindow::zwValueChangedFinishEdit()
{
    zwValueChanged();
    ui->tableViewZwischenrunde->setFocus();
}

void MainWindow::on_pushButtonZwGenerate_clicked()
{
    if(tmZw->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    QStringList equalDivisionResults = m_Vorrunde->checkEqualDivisionResults();

    if(equalDivisionResults.count() > 0)
    {
        if(equalDivisionResults.at(0) == "0")
        {
            equalDivisionResults.removeAt(0);
            emit mainLog("WARNING:: equal vorrunde division results");
            messageBoxWarning("Achtung! Vorrunde, Gleichstände zwischen den Mannschaften "
                              + equalDivisionResults.at(1) + " und " + equalDivisionResults.at(2) + " entdeckt!"
                              "\nDirektes Duell bei Spielnr. " +  equalDivisionResults.at(0) +
                              "\nZwischenrunde generieren wird abgebrochen!");
            return;
        }
        else if(equalDivisionResults.at(0) == "1")
        {
            equalDivisionResults.removeAt(0);
            emit mainLog("WARNING:: equal vorrunde division results");

            QString msgtext = "Achtung! Vorrunde, Gleichstände zwischen mehrere Mannschaften entdeckt!\n";
            msgtext += "Folgende Mannschaften sind betroffen:";

            foreach(QString equaldivisionteam, equalDivisionResults)
                msgtext += "\n" + equaldivisionteam;

            msgtext += "\nZwischenrunde generieren wird abgebrochen!";
            messageBoxWarning(msgtext);
            return;
        }
    }

    emit mainLog("INFO:: generate zwischenrunde");
    setZwischenrundeParams();

    if(!m_Zwischenrunde->generate())
    {
        emit mainLog("WARNING:: equal vorrunde over all divisions results");
        messageBoxWarning("Achtung! Vorrunde, Gruppengleichstände zwischen Mannschaften entdeckt!"
                          "\nBitte Punktestände überprüfen, Zwischenrunde generieren wird abgebrochen!");
        return;
    }

    initTableViewZwischenrunde(m_DataSettings.satzZw);
    messageBoxInformation("Zwischenrunde wurde generiert");
    on_pushButtonZwSave_clicked();
}

void MainWindow::on_pushButtonZwSave_clicked()
{
    emit mainLog("INFO:: saving zwischenrunde");

    if(m_Db->commitSqlTableModel(tmZw))
    {
        messageBoxInformation("Zwischenrunde wurde gespeichert");
        m_Zwischenrunde->calculateResult();
        zwChanged = false;
        return;
    }

    messageBoxCritical("Zwischenrunde speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonZwClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Zwischenrunde zurückzusetzen.", "Zwischenrunde"))
    {
        emit mainLog("INFO:: deleting zwischenrunde");
        m_Zwischenrunde->clear();
        on_pushButtonZwSave_clicked();
        initTableViewZwischenrunde(m_DataSettings.satzZw);
        emit mainLog("Zwischenrundenspielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit mainLog("INFO:: reset zwischenrunde aborted");
    messageBoxInformation("Zurücksetzen von Zwischenrundenspielplan und Ergebnissen abgebrochen!");
}

void MainWindow::on_pushButtonZwResult_clicked()
{
    m_ZwResults = new view_division_results(0);
    connect(m_ZwResults, SIGNAL(viewdivisionresultsLog(QString)), m_Log, SLOT(write(QString)));
    m_ZwResults->setAttribute(Qt::WA_DeleteOnClose);
    m_Zwischenrunde->calculateResult();

    m_ZwResults->init("zwischenrunde_erg_gr", grPrefix);

    m_ZwResults->show();
}

void MainWindow::on_pushButtonZwChangeGames_clicked()
{

}

void MainWindow::on_pushButtonZwPrint_clicked()
{

}

// ****************************************************************************************************
// functions KREUZSPIELE
// ****************************************************************************************************
void MainWindow::initTableViewKreuzspiele(int hideCol)
{
    emit mainLog("INFO:: init tableview kreuzspiele");
    QStringList columns;
    m_KrItemDelegate = new itemdelegate();

    columns << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr" << "Feldname" << "Mannschaft A"
        <<"Mannschaft B" << "Schiedsgericht" << "Satz 1 A" << "Satz 1 B" << "Satz 2 A"
        << "Satz 2 B" << "Satz 3 A" << "Satz 3 B";

    tmKr = m_Db->createSqlTableModel("kreuzspiele_spielplan", columns);

    connect(tmKr, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(krValueChanged()));

    ui->tableViewKreuzspiele->setModel(tmKr);
    ui->tableViewKreuzspiele->hideColumn(0);
    ui->tableViewKreuzspiele->setItemDelegate(m_KrItemDelegate);
    connect(m_KrItemDelegate, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyKrTableView()));
    connect(m_KrItemDelegate, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteKrTableView()));

    switch(hideCol)
    {
        case 1: ui->tableViewKreuzspiele->setColumnHidden(11,true);
                ui->tableViewKreuzspiele->setColumnHidden(12,true);
                ui->tableViewKreuzspiele->setColumnHidden(13,true);
                ui->tableViewKreuzspiele->setColumnHidden(14,true);
                break;
        case 2: ui->tableViewKreuzspiele->setColumnHidden(11,false);
                ui->tableViewKreuzspiele->setColumnHidden(12,false);
                ui->tableViewKreuzspiele->setColumnHidden(13,true);
                ui->tableViewKreuzspiele->setColumnHidden(14,true);
                break;
        case 3: ui->tableViewKreuzspiele->setColumnHidden(11,false);
                ui->tableViewKreuzspiele->setColumnHidden(12,false);
                ui->tableViewKreuzspiele->setColumnHidden(13,false);
                ui->tableViewKreuzspiele->setColumnHidden(14,false);
                break;
    }
}

void MainWindow::setKreuzspieleParams()
{
    QStringList zwParams = m_Db->read("SELECT runde, spiel, zeit FROM zwischenrunde_spielplan ORDER BY id DESC LIMIT 1").at(0);
    m_Kreuzspiele->setParams(zwParams.at(2), ((m_DataSettings.satzZw * m_DataSettings.minSatzZw) + m_DataSettings.pauseMinZw), m_DataSettings.pauseZwKr, m_DataSettings.satzKr, m_DataSettings.minSatzKr, m_DataSettings.pauseMinKr,
                                  m_DataSettings.anzFelder, m_Set->getTeamsCount(tmTeams), m_Set->getFieldNames(),
                               zwParams.at(0).toInt(), zwParams.at(1).toInt());
}

void MainWindow::copyKrTableView()
{
    copyEvent(ui->tableViewKreuzspiele);
}

void MainWindow::pasteKrTableView()
{
    pasteEvent(ui->tableViewKreuzspiele, tmKr);
}

void MainWindow::krValueChanged()
{
    if(!krChanged)
        emit mainLog("SETTINGS:: kreuzspiele changed");

    switch(ui->tableViewKreuzspiele->currentIndex().column())
    {
        case 3: emit mainLog("INFO:: recalculate time kreuzspiele");
                m_Kreuzspiele->recalculateTimeSchedule(ui->tableViewKreuzspiele, tmKr);
                break;
    }

    krChanged = true;
}

void MainWindow::krValueChangedFinishEdit()
{
    krValueChanged();
    ui->tableViewKreuzspiele->clearSelection();
}

void MainWindow::on_pushButtonKrGenerate_clicked()
{
    if(tmKr->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    QStringList equalDivisionResults = m_Vorrunde->checkEqualDivisionResults();

    if(equalDivisionResults.count() > 0)
    {
        if(equalDivisionResults.at(0) == "0")
        {
            equalDivisionResults.removeAt(0);
            emit mainLog("WARNING:: equal zwischenrunde division results");
            messageBoxWarning("Achtung! Zwischenrunde, Gleichstände zwischen den Mannschaften "
                              + equalDivisionResults.at(1) + " und " + equalDivisionResults.at(2) + " entdeckt!"
                              "\nDirektes Duell bei Spielnr. " +  equalDivisionResults.at(0) +
                              "\nKreuzspiele generieren wird abgebrochen!");
            return;
        }
        else if(equalDivisionResults.at(0) == "1")
        {
            equalDivisionResults.removeAt(0);
            emit mainLog("WARNING:: equal zwischenrunde division results");

            QString msgtext = "Achtung! Zwischenrunde, Gleichstände zwischen mehrere Mannschaften entdeckt!\n";
            msgtext += "Folgende Mannschaften sind betroffen:";

            foreach(QString equaldivisionteam, equalDivisionResults)
                msgtext += "\n" + equaldivisionteam;

            msgtext += "\nKreuzspiele generieren wird abgebrochen!";
            messageBoxWarning(msgtext);
            return;
        }
        return;
    }

    emit mainLog("INFO:: generate kreuzspiele");
    setKreuzspieleParams();
    m_Kreuzspiele->generate();
    initTableViewKreuzspiele(m_DataSettings.satzKr);
    messageBoxInformation("Kreuzspiele wurden generiert");
    on_pushButtonKrSave_clicked();
}

void MainWindow::on_pushButtonKrSave_clicked()
{
    emit mainLog("INFO:: saving kreuzspiele");

    if(m_Db->commitSqlTableModel(tmKr))
    {
        messageBoxInformation("Kreuzspiele wurden gespeichert");
        krChanged = false;
        return;
    }

    messageBoxCritical("Kreuzspiele speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonKrClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Kreuzspiele zurückzusetzen.", "Kreuzspiele"))
    {
        emit mainLog("INFO:: deleting kreuzspiele");
        m_Kreuzspiele->clear();
        on_pushButtonKrSave_clicked();
        initTableViewKreuzspiele(m_DataSettings.satzKr);
        emit mainLog("Kreuzspielespielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit mainLog("INFO:: reset kreuzspiele aborted");
    messageBoxInformation("Zurücksetzen von Kreuzspielespielplan abgebrochen!");
}

void MainWindow::on_pushButtonKrPrint_clicked()
{

}

// ****************************************************************************************************
// functions Platzspiele
// ****************************************************************************************************
void MainWindow::initTableViewPlatzspiele(int hideCol)
{
    emit mainLog("INFO:: init tableview platzspiele");
    QStringList columns;
    m_PlItemDelegate = new itemdelegate();

    columns << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr" << "Feldname" << "Mannschaft A"
        <<"Mannschaft B" << "Schiedsgericht" << "Satz 1 A" << "Satz 1 B" << "Satz 2 A"
        << "Satz 2 B" << "Satz 3 A" << "Satz 3 B";

    tmPl = m_Db->createSqlTableModel("platzspiele_spielplan", columns);

    connect(tmPl, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(plValueChanged()));

    ui->tableViewPlatzspiele->setModel(tmPl);
    ui->tableViewPlatzspiele->hideColumn(0);
    ui->tableViewPlatzspiele->setItemDelegate(m_PlItemDelegate);
    connect(m_PlItemDelegate, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyPlTableView()));
    connect(m_PlItemDelegate, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pastePLTableView()));

    switch(hideCol)
    {
        case 1: ui->tableViewPlatzspiele->setColumnHidden(11,true);
                ui->tableViewPlatzspiele->setColumnHidden(12,true);
                ui->tableViewPlatzspiele->setColumnHidden(13,true);
                ui->tableViewPlatzspiele->setColumnHidden(14,true);
                break;
        case 2: ui->tableViewPlatzspiele->setColumnHidden(11,false);
                ui->tableViewPlatzspiele->setColumnHidden(12,false);
                ui->tableViewPlatzspiele->setColumnHidden(13,true);
                ui->tableViewPlatzspiele->setColumnHidden(14,true);
                break;
        case 3: ui->tableViewPlatzspiele->setColumnHidden(11,false);
                ui->tableViewPlatzspiele->setColumnHidden(12,false);
                ui->tableViewPlatzspiele->setColumnHidden(13,false);
                ui->tableViewPlatzspiele->setColumnHidden(14,false);
                break;
    }
}

// set platzspiele params
void MainWindow::setPlatzspieleParams()
{
    QStringList krParams = m_Db->read("SELECT runde, spiel, zeit FROM kreuzspiele_spielplan ORDER BY id DESC LIMIT 1").at(0);
    m_Platzspiele->setParams(krParams.at(2), ((m_DataSettings.satzKr * m_DataSettings.minSatzKr) + m_DataSettings.pauseMinKr), m_DataSettings.pauseKrPl, m_DataSettings.satzPl, m_DataSettings.minSatzPl,
                                  m_DataSettings.anzFelder, m_Set->getTeamsCount(tmTeams), m_Set->getFieldNames(),
                               krParams.at(0).toInt(), krParams.at(1).toInt());
}

void MainWindow::copyPlTableView()
{
    copyEvent(ui->tableViewPlatzspiele);
}

void MainWindow::pastePLTableView()
{
    pasteEvent(ui->tableViewPlatzspiele, tmPl);
}

void MainWindow::plValueChanged()
{
    if(!plChanged)
        emit mainLog("SETTINGS:: platzspiele changed");

    switch(ui->tableViewPlatzspiele->currentIndex().column())
    {
        case 3: emit mainLog("INFO:: recalculate time platzspiele");
                m_Platzspiele->recalculateTimeSchedule(ui->tableViewPlatzspiele, tmPl);
                break;
    }

    plChanged = true;
}

void MainWindow::plValueChangedFinishEdit()
{
    plValueChanged();
    ui->tableViewPlatzspiele->clearSelection();
}

void MainWindow::on_pushButtonPlGenerate_clicked()
{
    emit mainLog("INFO:: generate platzspiele");

    if(tmPl->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    setPlatzspieleParams();
    m_Platzspiele->generate();
    initTableViewPlatzspiele(m_DataSettings.satzPl);
    setPlatzspieleParams();
    messageBoxInformation("Platzspiele wurden generiert");
    on_pushButtonPlSave_clicked();
}

void MainWindow::on_pushButtonPlSave_clicked()
{
    emit mainLog("INFO:: saving platzspiele");

    if(m_Db->commitSqlTableModel(tmPl))
    {
        messageBoxInformation("Platzspiele wurden gespeichert");
        plChanged = false;
        return;
    }

    messageBoxCritical("Platzspiele speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonPlClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Platzspiele zurückzusetzen.", "Platzspiele"))
    {
        emit mainLog("INFO:: deleting platzspiele");
        m_Platzspiele->clear();
        on_pushButtonPlSave_clicked();
        initTableViewPlatzspiele(m_DataSettings.satzPl);
        emit mainLog("Platzspielepielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit mainLog("INFO:: reset platzspiele aborted");
    messageBoxInformation("Zurücksetzen von Platzspielepielplan abgebrochen!");
}

void MainWindow::on_pushButtonPlPrint_clicked()
{

}

void MainWindow::on_pushButtonPlResult_clicked()
{
    m_Platzspiele->finalTournamentResults();
    m_VfR = new view_final_results(0, m_Db);
    m_VfR->show();
}
