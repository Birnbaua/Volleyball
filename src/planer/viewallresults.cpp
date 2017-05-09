#include "viewallresults.h"
#include "ui_viewallresults.h"

ViewAllResults::ViewAllResults(QString windowTitle, QSqlTableModel *tm, QIcon appIcon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewAllResults)
{
    ui->setupUi(this);

    ui->tableViewAllResults->setModel(tm);

    this->setWindowTitle(windowTitle);
    this->setWindowIcon(appIcon);
}

ViewAllResults::~ViewAllResults()
{
    delete ui;
}
