/********************************************************************************
** Form generated from reading UI file 'view_final_results.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_FINAL_RESULTS_H
#define UI_VIEW_FINAL_RESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_view_final_results
{
public:
    QGridLayout *gridLayout;
    QTableView *tableViewFinalResults;

    void setupUi(QWidget *view_final_results)
    {
        if (view_final_results->objectName().isEmpty())
            view_final_results->setObjectName(QStringLiteral("view_final_results"));
        view_final_results->resize(480, 431);
        gridLayout = new QGridLayout(view_final_results);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableViewFinalResults = new QTableView(view_final_results);
        tableViewFinalResults->setObjectName(QStringLiteral("tableViewFinalResults"));
        tableViewFinalResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableViewFinalResults->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableViewFinalResults->horizontalHeader()->setVisible(true);
        tableViewFinalResults->verticalHeader()->setVisible(false);
        tableViewFinalResults->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableViewFinalResults, 0, 0, 1, 1);


        retranslateUi(view_final_results);

        QMetaObject::connectSlotsByName(view_final_results);
    } // setupUi

    void retranslateUi(QWidget *view_final_results)
    {
        view_final_results->setWindowTitle(QApplication::translate("view_final_results", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class view_final_results: public Ui_view_final_results {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_FINAL_RESULTS_H
