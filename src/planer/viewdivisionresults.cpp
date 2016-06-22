#include "viewdivisionresults.h"
#include "ui_viewdivisionresults.h"

ViewDivisionResults::ViewDivisionResults(QString name, QList<QSqlTableModel*> *tmList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewDivisionResults)
{
    ui->setupUi(this);

    tvList << ui->tableViewA;
    tvList << ui->tableViewB;
    tvList << ui->tableViewC;
    tvList << ui->tableViewD;
    tvList << ui->tableViewE;
    tvList << ui->tableViewF;
    tvList << ui->tableViewG;
    tvList << ui->tableViewH;
    tvList << ui->tableViewI;

    for(int i = 0; i < tmList->size(); i++)
    {
        QSqlTableModel *tm = tmList->at(i);

        tvList.at(i)->setModel(tm);
        tvList.at(i)->hideColumn(0);
    }

    this->setWindowTitle(name);
    this->setWindowIcon(QIcon("./resources/mikasa.jpg"));

    tmList->clear();
}

ViewDivisionResults::~ViewDivisionResults()
{
    //tvList.clear();
    delete ui;
}
