#include "view_all_results.h"
#include "ui_view_all_results.h"

view_all_results::view_all_results(QWidget *parent, database *m_Db) :
    QWidget(parent),
    ui(new Ui::view_all_results)
{
    ui->setupUi(this);
    this->m_Db = m_Db;
    refresh = new QTimer();
    connect(refresh, SIGNAL(timeout()), this, SLOT(updateUi()));

    tableViews.append(ui->tableViewA);
    tableViews.append(ui->tableViewB);
    tableViews.append(ui->tableViewC);
    tableViews.append(ui->tableViewD);
    tableViews.append(ui->tableViewE);
    tableViews.append(ui->tableViewF);
    tableViews.append(ui->tableViewG);
    tableViews.append(ui->tableViewH);

    this->setWindowTitle("Spiele und Ergebnisse");
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));
}

view_all_results::~view_all_results()
{
    delete ui;
}

// start update ui
void view_all_results::startUpdateUi(int seconds)
{
    refresh->start(seconds * 1000);
}

// set group prefix
void view_all_results::setgrPrefix(QStringList grPrefix)
{
    this->grPrefix = grPrefix;
}

// update ui
void view_all_results::updateUi()
{
    QStringList columnName;
    int i = 0, x = 0;
    columnName << "Mannschaft" << "Satzpunkte" << "Spielpunkte";

    int cR = setCurrentRound();
    QSqlQueryModel *qmD = setTableView(cR);

    ui->tableViewNextGames->setModel(qmD);
    ui->tableViewNextGames->hideColumn(0);
    ui->tableViewNextGames->setItemDelegate(new itemdelegate());

    switch(cR)
    {
        case 1:
                foreach(QString prefix, grPrefix)
                {
                    QSqlQueryModel *tm = m_Db->createSqlQueryModel("Select * FROM vorrunde_gr" + prefix + "_view");

                    foreach(QString column, columnName)
                    {
                        tm->setHeaderData(x, Qt::Horizontal, column);
                        x++;
                    }

                    tableViews.at(i)->setModel(tm);
                    i++; x = 0;
                }
                ui->groupBoxResults->show();
                break;

        case 2:
                foreach(QString prefix, grPrefix)
                {
                    QSqlQueryModel *tm = m_Db->createSqlQueryModel("Select * FROM zwischenrunde_gr" + prefix + "_view");

                    foreach(QString column, columnName)
                    {
                        tm->setHeaderData(x, Qt::Horizontal, column);
                        x++;
                    }

                    tableViews.at(i)->setModel(tm);
                    i++;
                }
                ui->groupBoxResults->show();
                break;

        default:
                ui->groupBoxResults->hide();
                break;
    }
}

// set round
int view_all_results::setCurrentRound()
{
    if(m_Db->read("SELECT * FROM platzspiele_spielplan").count() > 0)
        return 4;

    if(m_Db->read("SELECT * FROM kreuzspiele_spielplan").count() > 0)
        return 3;

    if(m_Db->read("SELECT * FROM zwischenrunde_spielplan").count() > 0)
        return 2;

    if(m_Db->read("SELECT * FROM vorrunde_spielplan").count() > 0)
        return 1;

    return 0;
}

// fill table view with data
QSqlQueryModel* view_all_results::setTableView(int currentRound)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    int x = 0;
    QStringList columnName;
    columnName << "ID" << "Runde" << "Spiel" << "Zeit" << "Feldnr"
               << "Feldname" << "Mannschaft A" <<"Mannschaft B"
               << "Schiedsgericht";

    switch(currentRound)
    {
        case 1:
                model = m_Db->createSqlQueryModel("SELECT id, runde, spiel, zeit, feldnummer, feldname, ms_a, ms_b, sr, '' AS ' ' FROM vorrunde_spielplan WHERE satz1a = 0 AND satz1b = 0 AND satz2a = 0 AND satz2b = 0 AND satz3a = 0 AND satz3b = 0 ORDER BY id ASC");
                break;
        case 2:
                model = m_Db->createSqlQueryModel("SELECT id, runde, spiel, zeit, feldnummer, feldname, ms_a, ms_b, sr, '' AS ' ' FROM zwischenrunde_spielplan WHERE satz1a = 0 AND satz1b = 0 AND satz2a = 0 AND satz2b = 0 AND satz3a = 0 AND satz3b = 0 ORDER BY id ASC");
                break;
        case 3:
                model = m_Db->createSqlQueryModel("SELECT id, runde, spiel, zeit, feldnummer, feldname, ms_a, ms_b, sr, '' AS ' ' FROM kreuzspiele_spielplan WHERE satz1a = 0 AND satz1b = 0 AND satz2a = 0 AND satz2b = 0 AND satz3a = 0 AND satz3b = 0 ORDER BY id ASC");
                break;
        case 4:
                model = m_Db->createSqlQueryModel("SELECT id, runde, spiel, zeit, feldnummer, feldname, ms_a, ms_b, sr, '' AS ' ' FROM platzspiele_spielplan WHERE satz1a = 0 AND satz1b = 0 AND satz2a = 0 AND satz2b = 0 AND satz3a = 0 AND satz3b = 0 ORDER BY id ASC");
                break;
    }

    // set column header names
    foreach(QString column, columnName)
    {
        model->setHeaderData(x, Qt::Horizontal, column);
        x++;
    }

    return model;
}
