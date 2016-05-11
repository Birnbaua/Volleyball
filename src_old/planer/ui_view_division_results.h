/********************************************************************************
** Form generated from reading UI file 'view_division_results.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_DIVISION_RESULTS_H
#define UI_VIEW_DIVISION_RESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_view_division_results
{
public:
    QGridLayout *gridLayout_9;
    QGroupBox *groupBoxA;
    QGridLayout *gridLayout;
    QTableView *tableViewA;
    QGroupBox *groupBoxB;
    QGridLayout *gridLayout_2;
    QTableView *tableViewB;
    QGroupBox *groupBoxC;
    QGridLayout *gridLayout_3;
    QTableView *tableViewC;
    QGroupBox *groupBoxD;
    QGridLayout *gridLayout_4;
    QTableView *tableViewD;
    QGroupBox *groupBoxE;
    QGridLayout *gridLayout_5;
    QTableView *tableViewE;
    QGroupBox *groupBoxF;
    QGridLayout *gridLayout_6;
    QTableView *tableViewF;
    QGroupBox *groupBoxG;
    QGridLayout *gridLayout_7;
    QTableView *tableViewG;
    QGroupBox *groupBoxH;
    QGridLayout *gridLayout_8;
    QTableView *tableViewH;

    void setupUi(QWidget *view_division_results)
    {
        if (view_division_results->objectName().isEmpty())
            view_division_results->setObjectName(QStringLiteral("view_division_results"));
        view_division_results->resize(835, 593);
        gridLayout_9 = new QGridLayout(view_division_results);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBoxA = new QGroupBox(view_division_results);
        groupBoxA->setObjectName(QStringLiteral("groupBoxA"));
        gridLayout = new QGridLayout(groupBoxA);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableViewA = new QTableView(groupBoxA);
        tableViewA->setObjectName(QStringLiteral("tableViewA"));
        tableViewA->horizontalHeader()->setStretchLastSection(false);
        tableViewA->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableViewA, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxA, 0, 0, 1, 1);

        groupBoxB = new QGroupBox(view_division_results);
        groupBoxB->setObjectName(QStringLiteral("groupBoxB"));
        gridLayout_2 = new QGridLayout(groupBoxB);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableViewB = new QTableView(groupBoxB);
        tableViewB->setObjectName(QStringLiteral("tableViewB"));

        gridLayout_2->addWidget(tableViewB, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxB, 0, 1, 1, 1);

        groupBoxC = new QGroupBox(view_division_results);
        groupBoxC->setObjectName(QStringLiteral("groupBoxC"));
        gridLayout_3 = new QGridLayout(groupBoxC);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableViewC = new QTableView(groupBoxC);
        tableViewC->setObjectName(QStringLiteral("tableViewC"));

        gridLayout_3->addWidget(tableViewC, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxC, 0, 2, 1, 1);

        groupBoxD = new QGroupBox(view_division_results);
        groupBoxD->setObjectName(QStringLiteral("groupBoxD"));
        gridLayout_4 = new QGridLayout(groupBoxD);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableViewD = new QTableView(groupBoxD);
        tableViewD->setObjectName(QStringLiteral("tableViewD"));

        gridLayout_4->addWidget(tableViewD, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxD, 1, 0, 1, 1);

        groupBoxE = new QGroupBox(view_division_results);
        groupBoxE->setObjectName(QStringLiteral("groupBoxE"));
        gridLayout_5 = new QGridLayout(groupBoxE);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tableViewE = new QTableView(groupBoxE);
        tableViewE->setObjectName(QStringLiteral("tableViewE"));

        gridLayout_5->addWidget(tableViewE, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxE, 1, 1, 1, 1);

        groupBoxF = new QGroupBox(view_division_results);
        groupBoxF->setObjectName(QStringLiteral("groupBoxF"));
        gridLayout_6 = new QGridLayout(groupBoxF);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tableViewF = new QTableView(groupBoxF);
        tableViewF->setObjectName(QStringLiteral("tableViewF"));

        gridLayout_6->addWidget(tableViewF, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxF, 1, 2, 1, 1);

        groupBoxG = new QGroupBox(view_division_results);
        groupBoxG->setObjectName(QStringLiteral("groupBoxG"));
        gridLayout_7 = new QGridLayout(groupBoxG);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tableViewG = new QTableView(groupBoxG);
        tableViewG->setObjectName(QStringLiteral("tableViewG"));

        gridLayout_7->addWidget(tableViewG, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxG, 2, 0, 1, 1);

        groupBoxH = new QGroupBox(view_division_results);
        groupBoxH->setObjectName(QStringLiteral("groupBoxH"));
        gridLayout_8 = new QGridLayout(groupBoxH);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        tableViewH = new QTableView(groupBoxH);
        tableViewH->setObjectName(QStringLiteral("tableViewH"));

        gridLayout_8->addWidget(tableViewH, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBoxH, 2, 1, 1, 1);


        retranslateUi(view_division_results);

        QMetaObject::connectSlotsByName(view_division_results);
    } // setupUi

    void retranslateUi(QWidget *view_division_results)
    {
        view_division_results->setWindowTitle(QApplication::translate("view_division_results", "Widget", 0));
        groupBoxA->setTitle(QApplication::translate("view_division_results", "Gruppe A", 0));
        groupBoxB->setTitle(QApplication::translate("view_division_results", "Gruppe B", 0));
        groupBoxC->setTitle(QApplication::translate("view_division_results", "Gruppe C", 0));
        groupBoxD->setTitle(QApplication::translate("view_division_results", "Gruppe D", 0));
        groupBoxE->setTitle(QApplication::translate("view_division_results", "Gruppe E", 0));
        groupBoxF->setTitle(QApplication::translate("view_division_results", "Gruppe F", 0));
        groupBoxG->setTitle(QApplication::translate("view_division_results", "Gruppe G", 0));
        groupBoxH->setTitle(QApplication::translate("view_division_results", "Gruppe H", 0));
    } // retranslateUi

};

namespace Ui {
    class view_division_results: public Ui_view_division_results {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_DIVISION_RESULTS_H
