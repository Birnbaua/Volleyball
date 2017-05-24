#include "mainwindow.h"
#include "ui_mainwindow.h"

// ****************************************************************************************************
// static members
// ****************************************************************************************************
QStringList MainWindow::colTableViewFields = QStringList() << "Feldnummer" << "Feldname";

QStringList MainWindow::colTableViewTeams = QStringList() << "ID"
                                  << "Gruppe A" << "Gruppe B" << "Gruppe C" << "Gruppe D" << "Gruppe E"
                                  << "Gruppe F" << "Gruppe G" << "Gruppe H" << "Gruppe I" << "Gruppe J"
                                  << "Gruppe K" << "Gruppe L";

QStringList MainWindow::colTableViewQualifying = QStringList() << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr" << "Feldname"
                                       << "Mannschaft A" << "Mannschaft B" << "Schiedsgericht"
                                       << "Satz 1 A" << "Satz 1 B"
                                       << "Satz 2 A" << "Satz 2 B"
                                       << "Satz 3 A" << "Satz 3 B";

QStringList MainWindow::colTalbeViewDivisionResults = QStringList() << "ID" << "Mannschaft"
                                            << "Satzpunkte" << "Spielpunkte"
                                            << "int. W" << "ext. W";

QStringList MainWindow::colTableViewClassement = QStringList() << "Platz" << "Mannschaft";

QStringList MainWindow::colTableViewVrZwAllResults = QStringList() << "Mannschaft" << "Punkte" << "Spielpunkte" << "Intern" << "Extern";

QStringList MainWindow::qfTablesToClear = QStringList() << "vorrunde_spielplan"
                                                    << "vorrunde_erg_gra" << "vorrunde_erg_grb"
                                                    << "vorrunde_erg_grc" << "vorrunde_erg_grd"
                                                    << "vorrunde_erg_gre" << "vorrunde_erg_grf"
                                                    << "vorrunde_erg_grg" << "vorrunde_erg_grh"
                                                    << "vorrunde_erg_gri" << "vorrunde_erg_grj"
                                                    << "vorrunde_erg_grk" << "vorrunde_erg_grl";

QStringList MainWindow::itTablesToClear = QStringList() << "zwischenrunde_spielplan"
                                                    << "zwischenrunde_erg_gra" << "zwischenrunde_erg_grb"
                                                    << "zwischenrunde_erg_grc" << "zwischenrunde_erg_grd"
                                                    << "zwischenrunde_erg_gre" << "zwischenrunde_erg_grf"
                                                    << "zwischenrunde_erg_grg" << "zwischenrunde_erg_grh"
                                                    << "zwischenrunde_erg_gri" << "zwischenrunde_erg_grj"
                                                    << "zwischenrunde_erg_grk" << "zwischenrunde_erg_grl";

QStringList MainWindow::crTablesToClear = QStringList() << "kreuzspiele_spielplan";

QStringList MainWindow::clTablesToClear = QStringList() << "platzspiele_spielplan" << "platzierungen";

QStringList MainWindow::insertRows = QStringList() << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j,k,l) VALUES(0,'','','','','','','','','','','','')"
                                                   << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j,k,l) VALUES(1,'','','','','','','','','','','','')"
                                                   << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j,k,l) VALUES(2,'','','','','','','','','','','','')"
                                                   << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j,k,l) VALUES(3,'','','','','','','','','','','','')"
                                                   << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j,k,l) VALUES(4,'','','','','','','','','','','','')";

QStringList MainWindow::grPrefix = QStringList() << "a"<< "b"<< "c"<< "d"<< "e"<< "f" << "g" << "h" << "i" << "j" << "k" << "l";

QStringList MainWindow::headerPrefix = QStringList() << "A"<< "B"<< "C"<< "D"<< "E"<< "F" << "G" << "H" << "I" << "J" << "K" << "L";

QString MainWindow::dbFile = QString("./resources/data.db");
QString MainWindow::logFile = QString("./resources/volleyball.log");
QString MainWindow::settingsFile = QString("./resources/config.ini");
QString MainWindow::versionFileName = "./resources/version.txt";
QString MainWindow::windowTitleVersion = "Volleyball Tournament Organizer v";

// ****************************************************************************************************
// mainwindow
// ****************************************************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init members
    init();

    // get settings to ui
    worker->updateUiData();

    // get data for tableview fields
    initTableViewFields();

    // get data for tableview teams
    initTableViewTeams();

    // get data for tableview vorrunde
    initTableViewQualifying(data->satzVr);
    if(worker->getQualifyingGamesCount() > 0)
        worker->setParametersQualifyingGames();

    // get data for tableview zwischenrunde
    initTableViewInterim(data->satzZw);
    if(worker->getInterimGamesCount() > 0)
        worker->setParametersInterimGames();

    // get data for tableview kreuzspiele
    initTableViewCrossGames(data->satzKr);
    if(worker->getCrossGamesCount() > 0)
        worker->setParametersCrossGames();

    // get data for tableview platzspiele
    initTableViewClassement(data->satzPl);
    if(worker->getClassementGamesCount() > 0)
        worker->setParametersClassementGames();

    // set about dialog window
    abView = new About(versionFileName, windowTitleVersion);

    // set window title and icon
    this->setWindowTitle(windowTitleVersion + abView->getVersionNr());
    this->setWindowIcon(appIcon);

    // set updater
    timerUpdateTournamentTime->start(15 * 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    // create container for data exchange between gui and worker
    data = new Worker::dataUi;

    // preset that at startup nothing in gui was changed
    configChanged = false;
    msChanged = false;
    vrChanged = false;
    zwChanged = false;
    krChanged = false;
    plChanged = false;

    // create worker
    worker = new Worker(&settingsFile, &dbFile, &logFile,
                        &qfTablesToClear, &itTablesToClear, &crTablesToClear, &clTablesToClear,
                        &insertRows, &grPrefix, &headerPrefix);
    connect(worker, SIGNAL(criticalMessage(QString)), this, SLOT(messageBoxCritical(QString)));
    connect(worker, SIGNAL(warningMessage(QString)), this, SLOT(messageBoxWarning(QString)));
    connect(worker,SIGNAL(infoMessage(QString)), this, SLOT(messageBoxInformation(QString)));
    connect(worker, SIGNAL(updateUi(Worker::dataUi*)), this, SLOT(updateUiData(Worker::dataUi*)));
    connect(this, SIGNAL(log(QString)), worker, SLOT(logging(QString)), Qt::DirectConnection);
    connect(this, SIGNAL(updateWorker(Worker::dataUi*)), worker, SLOT(updateWorkerData(Worker::dataUi*)));

    // create timer to update tournament time calculation
    timerUpdateTournamentTime = new QTimer(this);
    connect(timerUpdateTournamentTime, SIGNAL(timeout()), SLOT(updateTournamentTime()));

    // item delegates for models
    idQualifyingGames = new ItemDelegates();
    connect(idQualifyingGames, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyVrTableView()));
    connect(idQualifyingGames, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteVrTableView()));
    connect(idQualifyingGames, SIGNAL(enterKeyEvent()), this, SLOT(vrValueChanged()));

    // item delegates for models
    idInterimGames = new ItemDelegates();
    connect(idInterimGames, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyVrTableView()));
    connect(idInterimGames, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteVrTableView()));
    connect(idInterimGames, SIGNAL(enterKeyEvent()), this, SLOT(vrValueChanged()));

    // item delegates for models
    idCrossGames = new ItemDelegates();
    connect(idCrossGames, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyKrTableView()));
    connect(idCrossGames, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pasteKrTableView()));

    // item delegates for models
    idClassement = new ItemDelegates();
    connect(idClassement, SIGNAL(ctrlCopyKeyEvent()), this, SLOT(copyPlTableView()));
    connect(idClassement, SIGNAL(ctrlPasteKeyEvent()), this, SLOT(pastePLTableView()));

    // create clipboard management
    clipboard = QApplication::clipboard();

    // init pointers
    tmFields = NULL;
    tmTeams = NULL;
    tmVr = NULL;
    qfView = NULL;
    tmZw = NULL;
    imView = NULL;
    tmKr = NULL;
    tmPl = NULL;
    clView = NULL;
    allVrView = NULL;
    allZwView = NULL;

    // set app icon
    appIcon = QIcon("./resources/mikasa.jpg");
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

// check if user wants to continue action
bool MainWindow::userCheckButton(QString msg, QString head)
{
    QMessageBox qmb(this);
    qmb.setText(msg);
    qmb.setWindowTitle(head);
    qmb.addButton(QMessageBox::Yes);
    qmb.addButton(QMessageBox::No);
    qmb.exec();

    if(qmb.result() == QMessageBox::Yes)
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

// exit programm
void MainWindow::on_actionBeenden_triggered()
{
    exit(0);
}

// show about info dialog
void MainWindow::on_actionAbout_triggered()
{
    abView->show();
}

// show log file
void MainWindow::on_actionShowlogfile_triggered()
{
    dir = QFileInfo("./resources/volleyball.log").absoluteDir();
    QDesktopServices::openUrl(QUrl(dir.absolutePath() + "/volleyball.log"));
}

// ****************************************************************************************************
// functions settings and checks
// ****************************************************************************************************

// get configuration and set ui controls
void MainWindow::updateUiData(Worker::dataUi *data)
{
    this->data = data;

    ui->spinBoxAnzahlfelder->setValue(this->data->anzFelder);
    if(this->data->krSpiele == 1)
    {
        ui->checkBoxKreuzspiele->setChecked(true);
    }
    else
    {
        ui->checkBoxKreuzspiele->setChecked(false);
    }
    ui->timeEditStartTurnier->setTime(QTime::fromString(this->data->startTurnier));
    ui->spinBoxPauseVrZw->setValue(this->data->pauseVrZw);
    ui->spinBoxPauseZwKr->setValue(this->data->pauseZwKr);
    ui->spinBoxPauseKrPl->setValue(this->data->pauseKrPl);
    ui->spinBoxSatzVr->setValue(this->data->satzVr);
    ui->spinBoxMinProSatzVr->setValue(this->data->minSatzVr);
    ui->spinBoxPauseMinVr->setValue(this->data->pauseMinVr);
    ui->spinBoxSatzZw->setValue(this->data->satzZw);
    ui->spinBoxMinProSatzZw->setValue(this->data->minSatzZw);
    ui->spinBoxPauseMinZw->setValue(this->data->pauseMinZw);
    ui->spinBoxSatzKr->setValue(this->data->satzKr);
    ui->spinBoxMinProSatzKr->setValue(this->data->minSatzKr);
    ui->spinBoxPauseMinKr->setValue(this->data->pauseMinKr);
    ui->spinBoxSatzPl->setValue(this->data->satzPl);
    ui->spinBoxMinProSatzPl->setValue(this->data->minSatzPl);
    ui->spinBoxZeitFinale->setValue(this->data->zeitFinale);
    ui->spinBoxPausePlEhrung->setValue(this->data->pausePlEhrung);
}

// set configuration from ui controls
void MainWindow::updateWorkerData()
{
    data->startTurnier = ui->timeEditStartTurnier->time().toString("hh:mm");

    if(ui->checkBoxKreuzspiele->isChecked())
        data->krSpiele = 1;
    else
        data->krSpiele = 0;

    data->pauseVrZw = ui->spinBoxPauseVrZw->value();
    data->pauseZwKr = ui->spinBoxPauseZwKr->value();
    data->pauseKrPl = ui->spinBoxPauseKrPl->value();
    data->satzVr = ui->spinBoxSatzVr->value();
    data->minSatzVr = ui->spinBoxMinProSatzVr->value();
    data->pauseMinVr = ui->spinBoxPauseMinVr->value();
    data->satzZw = ui->spinBoxSatzZw->value();
    data->minSatzZw = ui->spinBoxMinProSatzZw->value();
    data->pauseMinZw = ui->spinBoxPauseMinZw->value();
    data->satzKr = ui->spinBoxSatzKr->value();
    data->minSatzKr = ui->spinBoxMinProSatzKr->value();
    data->pauseMinKr = ui->spinBoxPauseMinKr->value();
    data->satzPl = ui->spinBoxSatzPl->value();
    data->minSatzPl = ui->spinBoxMinProSatzPl->value();
    data->zeitFinale = ui->spinBoxZeitFinale->value();
    data->pausePlEhrung = ui->spinBoxPausePlEhrung->value();
    data->anzFelder = ui->spinBoxAnzahlfelder->value();

    emit updateWorker(data);
}

//  init table view felder
void MainWindow::initTableViewFields()
{
    emit log("INFO:: init tableview fields");

    if(tmFields != NULL)
        tmFields->clear();

    tmFields = worker->createSqlTableModel("felder", &colTableViewFields);
    ui->tableViewFields->setModel(tmFields);
    connect(tmFields, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(fieldsValueChanged()));
}

// table view felder value changed
void MainWindow::fieldsValueChanged()
{
    if(!configChanged)
        emit log("SETTINGS:: configuration changed");

    configChanged = true;
}

//  init table view felder
void MainWindow::initTableViewTeams()
{
    emit log("INFO:: init tableview teams");

    if(tmTeams != NULL)
        tmTeams->clear();

    tmTeams = worker->createSqlTableModel("mannschaften", &colTableViewTeams);
    ui->tableViewTeams->setModel(tmTeams);
    ui->tableViewTeams->hideColumn(0);
    connect(tmTeams, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(teamsValueChanged()));
}

// table view teams value changed
void MainWindow::teamsValueChanged()
{
    if(!msChanged)
        emit log("SETTINGS:: teams changed");

    msChanged = true;
}

// set table field row count
void MainWindow::on_spinBoxAnzahlfelder_valueChanged(int arg1)
{
    emit log("INFO:: field count changed to" + QString::number(arg1));
    worker->setFieldsTableRows(arg1);
    initTableViewFields();
    configChanged = true;
}

// button save configuration
void MainWindow::on_pushButtonConfigSave_clicked()
{
    if(userCheckButton("Bitte bestätigen um die Turniereinstellungen zu speichern.","Turniereinstellungen"))
    {
        emit log("SETTINGS:: saving configuration");
        if(worker->commitSqlTableModel(tmFields))
        {
            // commit changes to db
            updateWorkerData();
            configChanged = false;
            messageBoxInformation("Turniereinstellungen gespeichert");
            return;
        }

        emit log("ERROR:: saving configuration failed");
        messageBoxCritical("Turniereinstellungen speichern fehlgeschlagen!");
        return;
    }
    emit log("INFO:: SETTINGS config aborted");
    messageBoxInformation("Turniereinstellungen speichern abgebrochen!");
}

// button rollback changes
void MainWindow::on_pushButtonConfigRollback_clicked()
{
    if(!configChanged)
    {
        emit log("SETTINGS:: no configuration changed, discarding configuration aborted");
        messageBoxInformation("Keine Änderungen in der Konfiguration festgestellt, verwerfen abgebrochen!");
        return;
    }

    if(userCheckButton("Bitte bestätigen um die Änderungen in der Konfiguration zu verwerfen.","Konfiguration"))
    {
        // do db rollback
        emit log("SETTINGS:: rollback configuration");
        tmFields->database().rollback();

        // read vars and set gui controls
        worker->updateUiData();
        initTableViewFields();

        configChanged = false;
        messageBoxInformation("Änderungen in der Konfiguration wurden verworfen");
        return;
    }

    emit log("SETTINGS:: rollback configuration aborted");
    messageBoxInformation("Verwerfen der Änderungen in der Konfiguration abgebrochen");
}

// button reset config
void MainWindow::on_pushButtonConfigReset_clicked()
{
    if(userCheckButton("Bitte bestätigen um die getätigten Turniereinstellungen zu verwerfen.","Turniereinstellungen"))
    {
        // reset config
        emit log("INFO:: reset configuration");
        worker->resetConfig();
        worker->updateUiData();

        messageBoxInformation("Turniereinstellungen wurden verworfen");
        configChanged = false;
        return;
    }
    emit log("SETTINGS:: discard saving config aborted");
    messageBoxInformation("Turniereinstellungen verwerfen abgebrochen!");
}

void MainWindow::on_pushButtonSaveTeams_clicked()
{
    if(!msChanged)
    {
        emit log("INFO:: no team value changed, abort save");
        messageBoxInformation("Keine Mannschaftsänderung durchgeführt, speichern abgebrochen!");
        return;
    }

    if(worker->checkDoubleTeamNames(tmTeams))
    {
        emit log("INFO:: no double team names");
        if(userCheckButton("Bitte bestätigen um die Mannschaften zu speichern.","Mannschaften"))
        {
            emit log("INFO:: saving teams");
            if(worker->commitSqlTableModel(tmTeams))
            {
                msChanged = false;
                messageBoxInformation("Mannschaften wurden gespeichert");
                return;
            }

            emit log("ERROR:: saving teams failed");
            messageBoxCritical("Mannschaften speichern fehlgeschlagen!");
        }
        return;
    }

    emit log("ERROR:: double team names");
    messageBoxCritical("Doppelte Mannschaftsnamen vorhanden, speichern abgebrochen!");
}

void MainWindow::on_pushButtonResetTeams_clicked()
{
    if(userCheckButton("Bitte bestätigen um die Mannschaften zu löschen.","Mannschaften"))
    {
        emit log("INFO:: deleting teams");
        worker->resetTeams();
        initTableViewTeams();
        messageBoxInformation("Mannschaften wurden zurückgesetzt");
        msChanged = false;
        return;
    }

    emit log("INFO:: deleting teams aborted");
    messageBoxInformation("Mannschaften speichern abgebrochen!");
}

void MainWindow::on_pushButtonPrintTeams_clicked()
{
    if(userCheckButton("Bitte bestätigen um Mannschaften zu drucken.","Mannschaften"))
    {
        // todo namen in pdfdatei schreiben
    }
}

// hide colums from tableview
void MainWindow::hideTableViewColumns(int hideCol, QTableView *qtv)
{
    switch(hideCol)
    {
        case 1: qtv->setColumnHidden(11,true);
                qtv->setColumnHidden(12,true);
                qtv->setColumnHidden(13,true);
                qtv->setColumnHidden(14,true);
                break;
        case 2: qtv->setColumnHidden(11,false);
                qtv->setColumnHidden(12,false);
                qtv->setColumnHidden(13,true);
                qtv->setColumnHidden(14,true);
                break;
        case 3: qtv->setColumnHidden(11,false);
                qtv->setColumnHidden(12,false);
                qtv->setColumnHidden(13,false);
                qtv->setColumnHidden(14,false);
                break;
    }
}

// update tournament time label
void MainWindow::updateTournamentTime()
{
    QList<QVariant> var = returnTime();
    QTime time = QTime::fromString(var.at(0).toString(), "hh:mm");
    int rC = var.at(1).toInt();
    int addT = 0, addTZw = 0, addTKr = 0, addTPl = 0;
    int tC = worker->getTeamsCount();

    // add zwischenrunde
    addTZw += data->pauseVrZw * 60;
    addTZw += (tmVr->rowCount()) * (((data->satzZw * data->minSatzZw) + data->pauseMinZw) * 60)
            / data->anzFelder;

    // add kreuzsspiele
    switch(tC)
    {
        case 20:
            addTKr += (((data->satzKr * data->minSatzKr) + data->pauseMinKr) * 60) * 8 / data->anzFelder;
            break;
        case 25:
            addTKr += (((data->satzKr * data->minSatzKr) + data->pauseMinKr) * 60) * 10 / data->anzFelder;
            break;
        case 28:
        case 30:
        case 35:
        case 40:
        case 45:
            addTKr += (((data->satzKr * data->minSatzKr) + data->pauseMinKr) * 60) * 12 / data->anzFelder;
            break;
    }
    addTKr += data->pauseZwKr * 60;

    // add platzspiele
    addTPl += data->pauseKrPl * 60;
    addTPl += (((tC / 2)-1) * (((data->satzPl * data->minSatzPl)) * 60) / data->anzFelder)
                + (data->zeitFinale * 60)
                + (data->pausePlEhrung * 60);

    switch(rC)
    {
        case 1:
            // add time from last vorrunde game
            addT = ((data->satzVr * data->minSatzVr) + data->pauseMinVr) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTZw);
            time = time.addSecs(addTKr);
            time = time.addSecs(addTPl);
            break;
        case 2:
            // add time from last zwischenrunde game
            addT = ((data->satzZw * data->minSatzZw) + data->pauseMinZw) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTKr);
            time = time.addSecs(addTPl);
            break;
        case 3:
            // add time from last kreuzspiel game
            addT = ((data->satzKr * data->minSatzKr) + data->pauseMinKr) * 60;
            time = time.addSecs(addT);
            time = time.addSecs(addTPl);
            break;
        case 4:
            addT = (data->zeitFinale * 60) + (data->pausePlEhrung * 60);
            time = time.addSecs(addT);
            break;
        default:
            break;
    }

    ui->labelTournamentEndValue->setText(time.toString("hh:mm"));
}

// return last time from round
QList<QVariant> MainWindow::returnTime()
{
    if(worker->getClassementGamesCount() > 0)
        return QList<QVariant>() << worker->getClassementGamesMaxTime() << 4;

    if(worker->getCrossGamesCount() > 0)
        return QList<QVariant>() << worker->getCrossGamesMaxTime() << 3;

    if(worker->getInterimGamesCount() > 0)
        return QList<QVariant>() << worker->getInterimGamesMaxTime() << 2;

    if(worker->getQualifyingGamesCount() > 0)
        return QList<QVariant>() << worker->getQualifyingGamesMaxTime() << 1;

    return QList<QVariant>() << "00:00" << 0;
}

// ****************************************************************************************************
// functions qualifying games
// ****************************************************************************************************
void MainWindow::initTableViewQualifying(int hideCol)
{
    emit log("INFO:: init tableview vorrunde");

    if(tmVr != NULL)
        tmVr->clear();

    tmVr = worker->createSqlTableModel("vorrunde_spielplan", &colTableViewQualifying);
    connect(tmVr, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(vrValueChanged()));

    ui->tableViewVorrunde->setModel(tmVr);
    ui->tableViewVorrunde->hideColumn(0);
    ui->tableViewVorrunde->setItemDelegate(idQualifyingGames);

    hideTableViewColumns(hideCol, ui->tableViewVorrunde);
}

void MainWindow::initTableViewQualifyingResults()
{
    if(viewQualifyingModels.size() > 0)
        viewQualifyingModels.clear();

    for(int i = 0; i < grPrefix.size(); i++)
    {
        QSqlTableModel *tm = worker->createSqlTableModel("vorrunde_erg_gr" + grPrefix.at(i), &colTalbeViewDivisionResults);
        tm->setEditStrategy(QSqlTableModel::OnFieldChange);
        tm->setFilter("1 ORDER BY punkte DESC, satz DESC, intern ASC");
        tm->select();
        viewQualifyingModels << tm;
    }

    qfView = NULL;
    qfView = new ViewDivisions("Ergebnisse Vorrunde",  &viewQualifyingModels, appIcon);
    qfView->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::initTableViewQualifyingAllResults()
{
    viewAllVrResults = NULL;
    viewAllVrResults = worker->createSqlTableModel("vorrunde_all_view", &colTableViewVrZwAllResults);

    allVrView = NULL;
    allVrView = new ViewAllResults("Vorrunde Ergebnisse alle Mannschaften", viewAllVrResults, appIcon);
    allVrView->setAttribute(Qt::WA_DeleteOnClose);
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
        emit log("SETTINGS:: vorrunde changed");

    if(ui->tableViewVorrunde->currentIndex().column() == 3)
    {
        emit log("INFO:: recalculate time vorrunde");
        worker->recalculateQualifyingGamesTimeSchedule(ui->tableViewVorrunde, tmVr);
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
    emit log("INFO:: generate vorrunde");

    if(tmVr->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    worker->setParametersQualifyingGames();
    worker->generateQualifyingGames();

    initTableViewQualifying(data->satzVr);
    messageBoxInformation("Vorrunde wurde generiert");
    on_pushButtonVrSave_clicked();
}

void MainWindow::on_pushButtonVrClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Vorrunde zurückzusetzen.", "Vorrunde"))
    {
        emit log("INFO:: deleting vorrunde");
        worker->clearQualifyingGames();
        on_pushButtonVrSave_clicked();
        initTableViewQualifying(data->satzVr);
        emit log("Vorrundespielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit log("INFO:: reset vorrunde aborted");
    messageBoxInformation("Zurücksetzen von Vorrundespielplan und Ergebnissen abgebrochen!");
}

void MainWindow::on_pushButtonVrSave_clicked()
{
    emit log("INFO:: saving vorrunde");

    if(worker->commitSqlTableModel(tmVr))
    {
        messageBoxInformation("Vorrunde wurde gespeichert");
        worker->calculateQualifyingGames();
        worker->uploadFile();
        vrChanged = false;
        return;
    }

    messageBoxCritical("Vorrunde speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonVrChangeGames_clicked()
{
    // todo
}

void MainWindow::on_pushButtonVrPrint_clicked()
{
    // todo
}

void MainWindow::on_pushButtonVrResult_clicked()
{
    initTableViewQualifyingResults();
    qfView->show();
}

void MainWindow::on_pushButtonVrAllResults_clicked()
{
    initTableViewQualifyingAllResults();
    allVrView->show();
}

// ****************************************************************************************************
// functions ZWISCHENRUNDE
// ****************************************************************************************************
void MainWindow::initTableViewInterim(int hideCol)
{
    emit log("INFO:: init tableview zwischenrunde");

    if(tmZw != NULL)
        tmZw->clear();

    tmZw = worker->createSqlTableModel("zwischenrunde_spielplan", &colTableViewQualifying);
    connect(tmZw, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(zwValueChanged()));

    ui->tableViewZwischenrunde->setModel(tmZw);
    ui->tableViewZwischenrunde->hideColumn(0);
    ui->tableViewZwischenrunde->setItemDelegate(idInterimGames);

    hideTableViewColumns(hideCol, ui->tableViewZwischenrunde);
}

void MainWindow::initTableViewInterimResults()
{
    if(viewIntermModels.size() > 0)
        viewIntermModels.clear();

    for(int i = 0; i < grPrefix.size(); i++)
    {
        QSqlTableModel *tm = worker->createSqlTableModel("zwischenrunde_erg_gr" + grPrefix.at(i), &colTalbeViewDivisionResults);
        tm->setEditStrategy(QSqlTableModel::OnFieldChange);
        tm->setFilter("1 ORDER BY punkte DESC, satz DESC, intern ASC");
        tm->select();
        viewIntermModels << tm;
    }

    imView = NULL;
    imView = new ViewDivisions("Ergebnisse Zwischenrunde", &viewIntermModels, appIcon);
    imView->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::initTableViewInterimAllResults()
{
    viewAllZwResults = NULL;
    viewAllZwResults = worker->createSqlTableModel("zwischenrunde_all_view", &colTableViewVrZwAllResults);

    allZwView = NULL;
    allZwView = new ViewAllResults("Zwischenrunde Ergebnisse alle Mannschaften", viewAllZwResults, appIcon);
    allZwView->setAttribute(Qt::WA_DeleteOnClose);
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
        emit log("SETTINGS:: zwischenrunde changed");

    if(ui->tableViewZwischenrunde->currentIndex().column() == 3)
    {
        log("INFO:: recalculate time zwischenrunde");
        worker->recalculateInterimGamesTimeSchedule(ui->tableViewZwischenrunde, tmZw);
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

    QStringList equalDivisionResults = worker->checkEqualDivisionResults();

    if(equalDivisionResults.count() > 0)
    {
        if(equalDivisionResults.at(0) == "0")
        {
            equalDivisionResults.removeAt(0);
            emit log("WARNING:: equal vorrunde division results");
            messageBoxWarning("Achtung! Vorrunde, Gleichstände zwischen den Mannschaften "
                              + equalDivisionResults.at(1) + " und " + equalDivisionResults.at(2) + " entdeckt!"
                              "\nDirektes Duell bei Spielnr. " +  equalDivisionResults.at(0) +
                              "\nZwischenrunde generieren wird abgebrochen!");
            return;
        }
        else if(equalDivisionResults.at(0) == "1")
        {
            equalDivisionResults.removeAt(0);
            emit log("WARNING:: equal vorrunde division results");

            QString msgtext = "Achtung! Vorrunde, Gleichstände zwischen mehrere Mannschaften entdeckt!\n";
            msgtext += "Folgende Mannschaften sind betroffen:";

            foreach(QString equaldivisionteam, equalDivisionResults)
                msgtext += "\n" + equaldivisionteam;

            msgtext += "\nZwischenrunde generieren wird abgebrochen!";
            messageBoxWarning(msgtext);
            return;
        }
    }


    emit log("INFO:: generate zwischenrunde");
    worker->setParametersInterimGames();

    if(!worker->generateInterimGames())
    {
        emit log("WARNING:: equal vorrunde over all divisions results");
        messageBoxWarning("Achtung! Vorrunde, Gruppengleichstände zwischen Mannschaften entdeckt!"
                          "\nBitte Punktestände überprüfen, Zwischenrunde generieren wird abgebrochen!");
        return;
    }

    initTableViewInterim(data->satzZw);
    messageBoxInformation("Zwischenrunde wurde generiert");
    on_pushButtonZwSave_clicked();
}

void MainWindow::on_pushButtonZwSave_clicked()
{
    emit log("INFO:: saving zwischenrunde");

    if(worker->commitSqlTableModel(tmZw))
    {
        messageBoxInformation("Zwischenrunde wurde gespeichert");
        worker->calculateInterimGames();
        worker->uploadFile();
        zwChanged = false;
        return;
    }

    messageBoxCritical("Zwischenrunde speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonZwClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Zwischenrunde zurückzusetzen.", "Zwischenrunde"))
    {
        emit log("INFO:: deleting zwischenrunde");
        worker->clearInterimGames();
        on_pushButtonZwSave_clicked();
        initTableViewInterim(data->satzZw);
        emit log("Zwischenrundenspielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit log("INFO:: reset zwischenrunde aborted");
    messageBoxInformation("Zurücksetzen von Zwischenrundenspielplan und Ergebnissen abgebrochen!");
}

void MainWindow::on_pushButtonZwChangeGames_clicked()
{

}

void MainWindow::on_pushButtonZwPrint_clicked()
{

}

void MainWindow::on_pushButtonZwResult_clicked()
{
    initTableViewInterimResults();
    imView->show();
}

void MainWindow::on_pushButtonZwAllResults_clicked()
{
    allZwView->show();
}

// ****************************************************************************************************
// functions KREUZSPIELE
// ****************************************************************************************************
void MainWindow::initTableViewCrossGames(int hideCol)
{
    emit log("INFO:: init tableview kreuzspiele");

    if(tmKr != NULL)
        tmKr->clear();

    tmKr = worker->createSqlTableModel("kreuzspiele_spielplan", &colTableViewQualifying);
    connect(tmKr, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(krValueChanged()));

    ui->tableViewKreuzspiele->setModel(tmKr);
    ui->tableViewKreuzspiele->hideColumn(0);
    ui->tableViewKreuzspiele->setItemDelegate(idCrossGames);

    hideTableViewColumns(hideCol, ui->tableViewKreuzspiele);
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
        emit log("SETTINGS:: kreuzspiele changed");

    switch(ui->tableViewKreuzspiele->currentIndex().column())
    {
        case 3: emit log("INFO:: recalculate time kreuzspiele");
                worker->recalculateCrossGamesTimeSchedule(ui->tableViewKreuzspiele, tmKr);
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

    QStringList equalDivisionResults = worker->checkEqualDivisionResults();

    if(equalDivisionResults.count() > 0)
    {
        if(equalDivisionResults.at(0) == "0")
        {
            equalDivisionResults.removeAt(0);
            emit log("WARNING:: equal zwischenrunde division results");
            messageBoxWarning("Achtung! Zwischenrunde, Gleichstände zwischen den Mannschaften "
                              + equalDivisionResults.at(1) + " und " + equalDivisionResults.at(2) + " entdeckt!"
                              "\nDirektes Duell bei Spielnr. " +  equalDivisionResults.at(0) +
                              "\nKreuzspiele generieren wird abgebrochen!");
            return;
        }
        else if(equalDivisionResults.at(0) == "1")
        {
            equalDivisionResults.removeAt(0);
            emit log("WARNING:: equal zwischenrunde division results");

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

    emit log("INFO:: generate kreuzspiele");
    worker->setParametersCrossGames();
    worker->generateCrossGames();
    initTableViewCrossGames(data->satzKr);
    messageBoxInformation("Kreuzspiele wurden generiert");
    on_pushButtonKrSave_clicked();
}

void MainWindow::on_pushButtonKrSave_clicked()
{
    emit log("INFO:: saving kreuzspiele");

    if(worker->commitSqlTableModel(tmKr))
    {
        messageBoxInformation("Kreuzspiele wurden gespeichert");
        worker->uploadFile();
        krChanged = false;
        return;
    }

    messageBoxCritical("Kreuzspiele speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonKrClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Kreuzspiele zurückzusetzen.", "Kreuzspiele"))
    {
        emit log("INFO:: deleting kreuzspiele");
        worker->clearCrossGames();
        on_pushButtonKrSave_clicked();
        initTableViewCrossGames(data->satzKr);
        emit log("Kreuzspielespielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit log("INFO:: reset kreuzspiele aborted");
    messageBoxInformation("Zurücksetzen von Kreuzspielespielplan abgebrochen!");
}

void MainWindow::on_pushButtonKrPrint_clicked()
{

}

// ****************************************************************************************************
// functions Platzspiele
// ****************************************************************************************************
void MainWindow::initTableViewClassement(int hideCol)
{
    emit log("INFO:: init tableview platzspiele");
    tmPl = worker->createSqlTableModel("platzspiele_spielplan", &colTableViewQualifying);
    connect(tmPl, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(plValueChanged()));

    ui->tableViewPlatzspiele->setModel(tmPl);
    ui->tableViewPlatzspiele->hideColumn(0);
    ui->tableViewPlatzspiele->setItemDelegate(idClassement);

    hideTableViewColumns(hideCol, ui->tableViewPlatzspiele);
}

void MainWindow::initTableViewClassementResults()
{
    viewClassementResults = NULL;
    viewClassementResults = worker->createSqlTableModel("platzierungen_view", &colTableViewClassement);

    clView = NULL;
    clView = new ViewClassement("Platzierung", viewClassementResults, appIcon);
    clView->setAttribute(Qt::WA_DeleteOnClose);
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
        emit log("SETTINGS:: platzspiele changed");

    switch(ui->tableViewPlatzspiele->currentIndex().column())
    {
        case 3: emit log("INFO:: recalculate time platzspiele");
                worker->recalculateClassementGamesTimeSchedule(ui->tableViewPlatzspiele, tmPl);
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
    emit log("INFO:: generate platzspiele");

    if(tmPl->rowCount() > 0)
    {
        messageBoxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
        return;
    }

    worker->setParametersClassementGames();
    worker->generateClassementGames();
    initTableViewClassement(data->satzPl);
    messageBoxInformation("Platzspiele wurden generiert");
    on_pushButtonPlSave_clicked();
}

void MainWindow::on_pushButtonPlSave_clicked()
{
    emit log("INFO:: saving platzspiele");

    if(worker->commitSqlTableModel(tmPl))
    {
        messageBoxInformation("Platzspiele wurden gespeichert");
        worker->uploadFile();
        plChanged = false;
        return;
    }

    messageBoxCritical("Platzspiele speichern fehlgeschlagen!");
}

void MainWindow::on_pushButtonPlClear_clicked()
{
    if(userCheckButton("Bitte bestätigen um Platzspiele zurückzusetzen.", "Platzspiele"))
    {
        emit log("INFO:: deleting platzspiele");
        worker->clearClassementGames();
        on_pushButtonPlSave_clicked();
        initTableViewClassement(data->satzPl);
        emit log("Platzspielepielplan und Ergebnisse wurden gelöscht");
        return;
    }

    emit log("INFO:: reset platzspiele aborted");
    messageBoxInformation("Zurücksetzen von Platzspielepielplan abgebrochen!");
}

void MainWindow::on_pushButtonPlPrint_clicked()
{
    // todo
}

// show result window
void MainWindow::on_pushButtonPlResult_clicked()
{
    worker->getFinalClassement();
    initTableViewClassementResults();
    clView->show();
}
