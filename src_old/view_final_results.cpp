#include "view_final_results.h"
#include "ui_view_final_results.h"

view_final_results::view_final_results(QWidget *parent, database *m_Db) :
    QWidget(parent),
    ui(new Ui::view_final_results)
{
    ui->setupUi(this);
    this->m_Db = m_Db;

    init();

    this->setWindowTitle("Platzierungen");
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));
}

view_final_results::~view_final_results()
{
    delete ui;
}

void view_final_results::init()
{
    QStringList columns;
    columns << "Platz" << "Mannschaft";
    data = m_Db->createSqlTableModel("platzierungen_view", columns);
    ui->tableViewFinalResults->setModel(data);
}
