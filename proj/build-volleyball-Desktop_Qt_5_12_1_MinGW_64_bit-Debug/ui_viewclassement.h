/********************************************************************************
** Form generated from reading UI file 'viewclassement.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWCLASSEMENT_H
#define UI_VIEWCLASSEMENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ViewClassement
{
public:
    QGridLayout *gridLayout;
    QTableView *tableViewClassement;

    void setupUi(QDialog *ViewClassement)
    {
        if (ViewClassement->objectName().isEmpty())
            ViewClassement->setObjectName(QString::fromUtf8("ViewClassement"));
        ViewClassement->setWindowModality(Qt::ApplicationModal);
        ViewClassement->resize(390, 448);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/mikasa.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        ViewClassement->setWindowIcon(icon);
        gridLayout = new QGridLayout(ViewClassement);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableViewClassement = new QTableView(ViewClassement);
        tableViewClassement->setObjectName(QString::fromUtf8("tableViewClassement"));
        tableViewClassement->horizontalHeader()->setVisible(true);
        tableViewClassement->horizontalHeader()->setStretchLastSection(true);
        tableViewClassement->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableViewClassement, 0, 0, 1, 1);


        retranslateUi(ViewClassement);

        QMetaObject::connectSlotsByName(ViewClassement);
    } // setupUi

    void retranslateUi(QDialog *ViewClassement)
    {
        ViewClassement->setWindowTitle(QApplication::translate("ViewClassement", "Platzierungen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewClassement: public Ui_ViewClassement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWCLASSEMENT_H
