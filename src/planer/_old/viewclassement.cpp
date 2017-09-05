#include "viewclassement.h"
#include "ui_viewclassement.h"

ViewClassement::ViewClassement(QString windowTitle, QSqlTableModel *tm, QIcon appIcon, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewClassement)
{
    ui->setupUi(this);

    ui->tableViewClassement->setModel(tm);

    this->setWindowTitle(windowTitle);
    this->setWindowIcon(appIcon);
}

ViewClassement::~ViewClassement()
{
    delete ui;
}
