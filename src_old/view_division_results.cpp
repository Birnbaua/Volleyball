#include "view_division_results.h"
#include "ui_view_division_results.h"

view_division_results::view_division_results(QWidget *parent, database *m_Db) :
    QWidget(parent),
    ui(new Ui::view_division_results)
{
    ui->setupUi(this);
    this->m_Db = m_Db;

    this->setWindowTitle("Ergebnisse");
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));
}

view_division_results::~view_division_results()
{
    delete ui;
}

void view_division_results::init(QString tableName, QStringList grPrefix)
{
    QStringList columnName;
    int i = 0;
    columnName << "ID" << "Mannschaft" << "Satzpunkte" << "Spielpunkte" << "int. W" << "ext. W";

    tableViews.append(ui->tableViewA);
    tableViews.append(ui->tableViewB);
    tableViews.append(ui->tableViewC);
    tableViews.append(ui->tableViewD);
    tableViews.append(ui->tableViewE);
    tableViews.append(ui->tableViewF);
    tableViews.append(ui->tableViewG);
    tableViews.append(ui->tableViewH);

    foreach(QString prefix, grPrefix)
    {
        QSqlTableModel *tm = m_Db->createSqlTableModel(tableName + prefix, columnName);
        tm->setEditStrategy(QSqlTableModel::OnFieldChange);
        tm->setFilter("1 ORDER BY punkte DESC, satz DESC, intern ASC");
        tm->select();
        tableViews.at(i)->setModel(tm);
        tableViews.at(i)->hideColumn(0);
        i++;
    }
}
