/********************************************************************************
** Form generated from reading UI file 'viewallresults.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWALLRESULTS_H
#define UI_VIEWALLRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ViewAllResults
{
public:
    QGridLayout *gridLayout;
    QTableView *tableViewAllResults;

    void setupUi(QDialog *ViewAllResults)
    {
        if (ViewAllResults->objectName().isEmpty())
            ViewAllResults->setObjectName(QString::fromUtf8("ViewAllResults"));
        ViewAllResults->resize(480, 640);
        gridLayout = new QGridLayout(ViewAllResults);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableViewAllResults = new QTableView(ViewAllResults);
        tableViewAllResults->setObjectName(QString::fromUtf8("tableViewAllResults"));
        tableViewAllResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableViewAllResults->setAlternatingRowColors(false);
        tableViewAllResults->setSelectionMode(QAbstractItemView::NoSelection);
        tableViewAllResults->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableViewAllResults, 0, 0, 1, 1);


        retranslateUi(ViewAllResults);

        QMetaObject::connectSlotsByName(ViewAllResults);
    } // setupUi

    void retranslateUi(QDialog *ViewAllResults)
    {
        ViewAllResults->setWindowTitle(QApplication::translate("ViewAllResults", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewAllResults: public Ui_ViewAllResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWALLRESULTS_H
