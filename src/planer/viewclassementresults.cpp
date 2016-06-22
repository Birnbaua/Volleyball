#include "viewclassementresults.h"
#include "ui_viewclassementresults.h"

ViewClassementResults::ViewClassementResults(QString name, QSqlTableModel *tm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewClassementResults)
{
    ui->setupUi(this);

    ui->tableViewFinalResults->setModel(tm);

    this->setWindowTitle(name);
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));
}

ViewClassementResults::~ViewClassementResults()
{
    delete ui;
}
