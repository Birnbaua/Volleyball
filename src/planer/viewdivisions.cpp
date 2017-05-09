#include "viewdivisions.h"
#include "ui_viewdivisions.h"

ViewDivisions::ViewDivisions(QString windowTitle, QList<QSqlTableModel*> *tmList, QIcon appIcon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDivisions)
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
    tvList << ui->tableViewJ;

    for(int i = 0; i < tmList->size(); i++)
    {
        QSqlTableModel *tm = tmList->at(i);

        tvList.at(i)->setModel(tm);
        tvList.at(i)->hideColumn(0);
    }

    this->setWindowTitle(windowTitle);
    this->setWindowIcon(appIcon);
}

ViewDivisions::~ViewDivisions()
{
    delete ui;
}
