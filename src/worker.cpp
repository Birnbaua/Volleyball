#include "worker.h"

QStringList Worker::qfTablesToClear = QStringList() << "vorrunde_spielplan"
                                                    << "vorrunde_erg_gra"
                                                    << "vorrunde_erg_grb"
                                                    << "vorrunde_erg_grc"
                                                    << "vorrunde_erg_grd"
                                                    << "vorrunde_erg_gre"
                                                    << "vorrunde_erg_grf"
                                                    << "vorrunde_erg_grg"
                                                    << "vorrunde_erg_grh"
                                                    << "vorrunde_erg_gri";

QStringList Worker::itTablesToClear = QStringList() << "zwischenrunde_spielplan"
                                                    << "zwischenrunde_erg_gra"
                                                    << "zwischenrunde_erg_grb"
                                                    << "zwischenrunde_erg_grc"
                                                    << "zwischenrunde_erg_grd"
                                                    << "zwischenrunde_erg_gre"
                                                    << "zwischenrunde_erg_grf"
                                                    << "zwischenrunde_erg_grg"
                                                    << "zwischenrunde_erg_grh"
                                                    << "zwischenrunde_erg_gri";

QStringList Worker::crTablesToClear = QStringList() << "kreuzspiele_spielplan";

QStringList Worker::clTablesToClear = QStringList() << "platzspiele_spielplan"
                                                    << "platzierungen";

QStringList Worker::insertRows = QStringList() << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i) VALUES(0,'','','','','','','')"
                                               << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i) VALUES(1,'','','','','','','')"
                                               << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i) VALUES(2,'','','','','','','')"
                                               << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i) VALUES(3,'','','','','','','')"
                                               << "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i) VALUES(4,'','','','','','','')";

QStringList Worker::grPrefix = QStringList() << "a"<< "b"<< "c"<< "d"<< "e"<< "f" << "g" << "h" << "i";

QStringList Worker::headerPrefix = QStringList() << "A"<< "B"<< "C"<< "D"<< "E"<< "F" << "G" << "H" << "I";

QString Worker::dbFile = QString("./resources/data.db");
QString Worker::logFile = QString("./resources/volleyball.log");
QString Worker::settingsFile = QString("./resources/config.ini");

Worker::Worker(QObject *parent) : QObject(parent)
{
    // create logging
    logs = new Logging(logFile);
    connect(this, SIGNAL(log(QString)), logs, SLOT(write(QString)));

    // check database file
    QFile dbF(dbFile);
    if(dbF.size() > 0)
    {
        // create database
        db = new Database(dbFile);
        connect(db, SIGNAL(log(QString)), logs, SLOT(write(QString)));

        // open database
        if(db->open())
        {
			logging("start init ...");
            init();
        }
        else
        {
            logging("could not open database!");
            emit criticalMessage("could not open database!");
            exit(-1);
        }
    }
    else
    {
        logging("Die Datei '" + dbF.fileName() + "' ist fehlerhaft, bitte überprüfen Sie die Datei!");
        emit criticalMessage("Die Datei '" + dbF.fileName() + "' ist fehlerhaft, bitte überprüfen Sie die Datei!");
        exit(-1);
    }
}

void Worker::init()
{
    // create container to exchange data between gui and worker
    data = new dataUi;

    // set teamscount
    teamsCount = 0;

    // read settings for ftp login
    QSettings settings(settingsFile, QSettings::IniFormat);
    emit logging("ftp config " + settings.value("ftpurl", "").toString() + ", "
                 + settings.value("ftpuser", "").toString() + ", "
                 + settings.value("ftppw", "").toString());

	// create ftploader thread
	logging("create ftp module");
    ftpload = new FTPLoader(dbFile,
                            settings.value("ftpurl", "").toString(),
                            settings.value("ftpuser", "").toString(),
                            settings.value("ftppw", "").toString());
	connect(ftpload, SIGNAL(logMessages(QString)), this, SLOT(logging(QString)));

	// create timer for ftp upload
    uploader = new QTimer(this);
    uploader->setInterval(30 * 1000);
	connect(uploader, SIGNAL(timeout()), ftpload, SLOT(startUpload()));

    // create calculate results
	logging("create calculateresults module");
    cr = new CalculateResults();

    // create qualifying games
	logging("create qualifying module");
    qf = new QualifyingGames(db, &grPrefix);
    connect(qf, SIGNAL(logMessages(QString)), this, SLOT(logging(QString)));

    // create interim games
	logging("create interim module");
    im = new InterimGames(db, &grPrefix);
    connect(im, SIGNAL(logMessages(QString)), this, SLOT(logging(QString)));

    // create cross games
	logging("create crossgame module");
    cg = new CrossGames(db, &grPrefix);
    connect(cg, SIGNAL(logMessages(QString)), this, SLOT(logging(QString)));

    // create classement games
	logging("create classement module");
    clg = new ClassementGames(db, &grPrefix);
    connect(clg, SIGNAL(logMessages(QString)), this, SLOT(logging(QString)));
}

void Worker::logging(QString message)
{
    logs->write(message);
}

// activate ftp upload
void Worker::startUploadTimer()
{
    uploader->start();
}

// deactivate ftp upload
void Worker::stopUploadTimer()
{
    uploader->stop();
}

// check double team names
bool Worker::checkDoubleTeamNames(QSqlTableModel *model)
{
    int count = 0;
    bool twoteams = false;
    QString team = "";

    for(int row = 0, col = 1; col < model->columnCount();)
    {
        team = model->index(row,col).data().toString();
        for(int i = 0; i < model->rowCount(); i++)
        {
            for(int j = 1; j < model->columnCount(); j++)
            {
                if(team == model->index(i,j).data().toString() && team != "" )
                {
                    count++;
                }
                if(count > 1)
                {
                    twoteams = true;
                    break;
                }
            }
        }
        count = 0;
        row++;
        if(row == model->rowCount())
        {
            col++;
            row = 0;
        }
    }

    if(!twoteams)
    {
        return true;
    }

    return false;
}

// get field names
QStringList Worker::getFieldNames()
{
    QList<QStringList> fieldNameList = db->read("SELECT feldname FROM felder ORDER BY id ASC");
    QStringList fieldNames;

    foreach(QStringList fieldName, fieldNameList)
        fieldNames << fieldName.at(0);

    return fieldNames;
}

// get teams count
int Worker::getTeamsCount()
{
    int teamsCount = 0;
    QList<QStringList> table = db->read("SELECT a, b, c, d, e, f, g, h, i FROM mannschaften");

    foreach(QStringList row, table)
    {
        foreach(QString col, row)
        {
            if(col != "")
                teamsCount++;
        }
    }

    return teamsCount;
}

// set fields table rows
void Worker::setFieldsTableRows(int spinBoxCount)
{
    int rowCount = db->read("SELECT id FROM felder").count();

    if (rowCount < spinBoxCount)
    {
        for (int i = rowCount + 1; i <= spinBoxCount; i++)
            db->write("INSERT INTO felder VALUES(" + QString::number(i) + ",'')");
    }
    else if(rowCount > spinBoxCount)
    {
        db->write("DELETE FROM felder WHERE id > " + QString::number(spinBoxCount));
    }
}

// reset teams table
void Worker::resetTeams()
{
    db->write("DELETE FROM mannschaften");

    foreach(QString insertRow, insertRows)
        db->write(insertRow);
}

// set ui controls with values from vars
void Worker::updateUiData()
{
    // read config from database
    readConfig();
    emit updateUi(data);
}

// reset configuration
void Worker::resetConfig()
{
    // reset config with default parameters
    writeConfig(4, 1, "10:00", 0, 0, 0, 1, 10, 0, 1, 10, 0, 1, 10, 0, 1, 10, 15, 30);
}

QStringList* Worker::getPrefix()
{
    return &(this->grPrefix);
}

QStringList* Worker::getHeaderPrefix()
{
    return &(this->headerPrefix);
}

QSqlTableModel* Worker::createSqlTableModel(QString tableName, QStringList columnName)
{
    return db->createSqlTableModel(tableName, columnName);
}

bool Worker::commitSqlTableModel(QSqlTableModel *model)
{
    return db->commitSqlTableModel(model);
}

void Worker::updateWorkerData(Worker::dataUi *data)
{
    this->data = data;

    // write config to database
    writeConfig(this->data->anzFelder, this->data->krSpiele, this->data->startTurnier, this->data->pauseVrZw,
        this->data->pauseZwKr, this->data->pauseKrPl, this->data->satzVr, this->data->minSatzVr,
        this->data->pauseMinVr, this->data->satzZw, this->data->minSatzZw, this->data->pauseMinZw,
        this->data->satzKr, this->data->minSatzKr, this->data->pauseMinKr, this->data->satzPl,
                this->data->minSatzPl, this->data->zeitFinale, this->data->pausePlEhrung);
}

void Worker::readConfig()
{
    QSqlQueryModel *config = db->createSqlQueryModel("select * from configuration");

    data->sysFilePath = config->record(0).value("sysfilepath").toString();
    data->pdfPath = config->record(0).value("pdfpath").toString();
    data->anzFelder = config->record(0).value("anzfelder").toInt();
    data->krSpiele = config->record(0).value("kreuzspiele").toInt();
    data->startTurnier = config->record(0).value("startturnier").toString();
    data->pauseVrZw = config->record(0).value("pausevrzw").toInt();
    data->pauseZwKr = config->record(0).value("pausezwkr").toInt();
    data->pauseKrPl = config->record(0).value("pausekrpl").toInt();
    data->satzVr = config->record(0).value("satzvr").toInt();
    data->minSatzVr = config->record(0).value("minsatzvr").toInt();
    data->pauseMinVr = config->record(0).value("pauseminvr").toInt();
    data->satzZw = config->record(0).value("satzzw").toInt();
    data->minSatzZw = config->record(0).value("minsatzzw").toInt();
    data->pauseMinZw = config->record(0).value("pauseminzw").toInt();
    data->satzKr = config->record(0).value("satzkr").toInt();
    data->minSatzKr = config->record(0).value("minsatzkr").toInt();
    data->pauseMinKr = config->record(0).value("pauseminkr").toInt();
    data->satzPl = config->record(0).value("satzpl").toInt();
    data->minSatzPl = config->record(0).value("minsatzpl").toInt();
    data->zeitFinale = config->record(0).value("zeitfinale").toInt();
    data->pausePlEhrung = config->record(0).value("pauseplehrung").toInt();
}

// write configuration to database
void Worker::writeConfig(int anzfelder, int kreuzspiele, QString startturnier, int pausevrzw, int pausezwkr, int pausekrpl,
                         int satzvr, int minsatzvr, int pauseminvr, int satzzw, int minsatzzw, int pauseminzw, int satzkr,
                         int minsatzkr, int pauseminkr, int satzpl, int minsatzpl, int zeitfinale, int pauseplehrung)
{
    db->write("UPDATE configuration SET anzfelder = " + QString::number(anzfelder)
        + ", kreuzspiele = " + QString::number(kreuzspiele) + ", startturnier = '" + startturnier
        + "', pausevrzw = " + QString::number(pausevrzw) + ", pausezwkr = " + QString::number(pausezwkr)
        + ", pausekrpl = " + QString::number(pausekrpl) + ", satzvr = " + QString::number(satzvr)
        + ", minsatzvr = " + QString::number(minsatzvr) + ", pauseminvr = " + QString::number(pauseminvr)
        + ", satzzw = " + QString::number(satzzw) + ", minsatzzw = " + QString::number(minsatzzw)
        + ", pauseminzw = " + QString::number(pauseminzw) + ", satzkr = " + QString::number(satzkr)
        + ", minsatzkr = " + QString::number(minsatzkr) + ", pauseminkr = " + QString::number(pauseminkr)
        + ", satzpl = " + QString::number(satzpl) + ", minsatzpl = " + QString::number(minsatzpl)
        + ", zeitfinale = " + QString::number(zeitfinale) + ", pauseplehrung = " + QString::number(pauseplehrung) + " WHERE id = 1");
}

// ****************************************************************************************************
// functions qualifying games
// ****************************************************************************************************

void Worker::setParametersQualifyingGames()
{
    this->fieldNames = getFieldNames();
    this->teamsCount = getTeamsCount();
    qf->setParameters(data->startTurnier, data->satzVr, data->minSatzVr, data->pauseMinVr, data->anzFelder, this->teamsCount, &(this->fieldNames));
}

void Worker::generateQualifyingGames()
{
    qf->generateGames();
}

void Worker::clearQualifyingGames()
{
    qf->clearAllData(Worker::qfTablesToClear);
}

void Worker::calculateQualifyingGames()
{
    qf->calculateResult("vorrunde_spielplan", "vorrunde_erg_gr");
}

void Worker::recalculateQualifyingGamesTimeSchedule(QTableView *qtv, QSqlTableModel *tm)
{
    qf->recalculateTimeSchedule(qtv, tm);
}

int Worker::getQualifyingGamesCount()
{
    return db->read("SELECT * FROM vorrunde_spielplan").count();
}

QStringList Worker::checkEqualDivisionResults()
{
    return qf->checkEqualDivisionResults("vorrunde_spielplan", "vorrunde_erg_gr");
}

QString Worker::getQualifyingGamesMaxTime()
{
    return db->read("SELECT MAX(zeit) FROM platzspiele_spielplan ORDER BY id").at(0).at(0);
}

// ****************************************************************************************************
// functions interim games
// ****************************************************************************************************

void Worker::setParametersInterimGames()
{
    QStringList params = db->read("SELECT runde, spiel, zeit FROM vorrunde_spielplan ORDER BY id DESC LIMIT 1").at(0);
    im->setParameters(params.at(2), data->pauseVrZw, data->satzZw, data->minSatzZw, data->pauseMinZw,
                      data->anzFelder, this->teamsCount, &(this->fieldNames), params.at(0).toInt(), params.at(1).toInt());
}

bool Worker::generateInterimGames()
{
    return im->generateGames();
}

void Worker::clearInterimGames()
{
    im->clearAllData();
}

void Worker::calculateInterimGames()
{
    im->calculateResult();
}

void Worker::recalculateInterimGamesTimeSchedule(QTableView *qtv, QSqlTableModel *tm)
{
    im->recalculateTimeSchedule(qtv, tm);
}

int Worker::getInterimGamesCount()
{
    return db->read("SELECT * FROM zwischenrunde_spielplan").count();
}

QString Worker::getInterimGamesMaxTime()
{
    return db->read("SELECT MAX(zeit) FROM kreuzspiele_spielplan ORDER BY id").at(0).at(0);
}

// ****************************************************************************************************
// functions cross games
// ****************************************************************************************************

void Worker::setParametersCrossGames()
{
    QStringList params = db->read("SELECT runde, spiel, zeit FROM zwischenrunde_spielplan ORDER BY id DESC LIMIT 1").at(0);
    cg->setParameters(params.at(2), ((data->satzZw * data->minSatzZw) + data->pauseMinZw), data->pauseZwKr, data->satzKr,
                      data->minSatzKr, data->pauseMinKr, data->anzFelder, this->teamsCount, &(this->fieldNames),
                      params.at(0).toInt(), params.at(1).toInt());
}

void Worker::generateCrossGames()
{
    cg->generateCrossGames();
}

void Worker::clearCrossGames()
{
    cg->clearAllData();
}

void Worker::recalculateCrossGamesTimeSchedule(QTableView *qtv, QSqlTableModel *tm)
{
    cg->recalculateTimeSchedule(qtv, tm);
}

int Worker::getCrossGamesCount()
{
    return db->read("SELECT * FROM kreuzspiele_spielplan").count();
}

QString Worker::getCrossGamesMaxTime()
{
    return db->read("SELECT MAX(zeit) FROM zwischenrunde_spielplan ORDER BY id").at(0).at(0);
}

// ****************************************************************************************************
// functions classement games
// ****************************************************************************************************

void Worker::setParametersClassementGames()
{
    QStringList params = db->read("SELECT runde, spiel, zeit FROM kreuzspiele_spielplan ORDER BY id DESC LIMIT 1").at(0);
    clg->setParameters(params.at(2), ((data->satzKr * data->minSatzKr) + data->pauseMinKr), data->pauseKrPl, data->satzPl,
                      data->minSatzPl, data->anzFelder, this->teamsCount, &(this->fieldNames),
                      params.at(0).toInt(), params.at(1).toInt());
}

void Worker::generateClassementGames()
{
    clg->generateClassementGames();
}

void Worker::clearClassementGames()
{
    clg->clearAllData();
}

void Worker::recalculateClassementGamesTimeSchedule(QTableView *qtv, QSqlTableModel *tm)
{
    clg->recalculateTimeSchedule(qtv, tm);
}

int Worker::getClassementGamesCount()
{
    return db->read("SELECT * FROM platzspiele_spielplan").count();
}

void Worker::getFinalClassement()
{
    clg->finalTournamentResults();
}

QString Worker::getClassementGamesMaxTime()
{
    return db->read("SELECT MAX(zeit) FROM vorrunde_spielplan ORDER BY id").at(0).at(0);
}

