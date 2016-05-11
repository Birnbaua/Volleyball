/********************************************************************************
** Form generated from reading UI file 'view_all_results.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_ALL_RESULTS_H
#define UI_VIEW_ALL_RESULTS_H

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

class Ui_view_all_results
{
public:
    QGridLayout *gridLayout_11;
    QGroupBox *groupBoxGames;
    QGridLayout *gridLayout;
    QTableView *tableViewNextGames;
    QGroupBox *groupBoxResults;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBoxA;
    QGridLayout *gridLayout_3;
    QTableView *tableViewA;
    QGroupBox *groupBoxB;
    QGridLayout *gridLayout_2;
    QTableView *tableViewB;
    QGroupBox *groupBoxC;
    QGridLayout *gridLayout_9;
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

    void setupUi(QWidget *view_all_results)
    {
        if (view_all_results->objectName().isEmpty())
            view_all_results->setObjectName(QStringLiteral("view_all_results"));
        view_all_results->resize(1136, 750);
        gridLayout_11 = new QGridLayout(view_all_results);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        groupBoxGames = new QGroupBox(view_all_results);
        groupBoxGames->setObjectName(QStringLiteral("groupBoxGames"));
        gridLayout = new QGridLayout(groupBoxGames);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableViewNextGames = new QTableView(groupBoxGames);
        tableViewNextGames->setObjectName(QStringLiteral("tableViewNextGames"));
        tableViewNextGames->horizontalHeader()->setStretchLastSection(true);
        tableViewNextGames->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableViewNextGames, 0, 0, 1, 1);


        gridLayout_11->addWidget(groupBoxGames, 0, 0, 1, 1);

        groupBoxResults = new QGroupBox(view_all_results);
        groupBoxResults->setObjectName(QStringLiteral("groupBoxResults"));
        gridLayout_10 = new QGridLayout(groupBoxResults);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBoxA = new QGroupBox(groupBoxResults);
        groupBoxA->setObjectName(QStringLiteral("groupBoxA"));
        gridLayout_3 = new QGridLayout(groupBoxA);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableViewA = new QTableView(groupBoxA);
        tableViewA->setObjectName(QStringLiteral("tableViewA"));
        tableViewA->horizontalHeader()->setStretchLastSection(false);
        tableViewA->verticalHeader()->setStretchLastSection(false);

        gridLayout_3->addWidget(tableViewA, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxA, 0, 0, 1, 1);

        groupBoxB = new QGroupBox(groupBoxResults);
        groupBoxB->setObjectName(QStringLiteral("groupBoxB"));
        gridLayout_2 = new QGridLayout(groupBoxB);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableViewB = new QTableView(groupBoxB);
        tableViewB->setObjectName(QStringLiteral("tableViewB"));

        gridLayout_2->addWidget(tableViewB, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxB, 0, 1, 1, 1);

        groupBoxC = new QGroupBox(groupBoxResults);
        groupBoxC->setObjectName(QStringLiteral("groupBoxC"));
        gridLayout_9 = new QGridLayout(groupBoxC);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        tableViewC = new QTableView(groupBoxC);
        tableViewC->setObjectName(QStringLiteral("tableViewC"));

        gridLayout_9->addWidget(tableViewC, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxC, 0, 2, 1, 1);

        groupBoxD = new QGroupBox(groupBoxResults);
        groupBoxD->setObjectName(QStringLiteral("groupBoxD"));
        gridLayout_4 = new QGridLayout(groupBoxD);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableViewD = new QTableView(groupBoxD);
        tableViewD->setObjectName(QStringLiteral("tableViewD"));

        gridLayout_4->addWidget(tableViewD, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxD, 0, 3, 1, 1);

        groupBoxE = new QGroupBox(groupBoxResults);
        groupBoxE->setObjectName(QStringLiteral("groupBoxE"));
        gridLayout_5 = new QGridLayout(groupBoxE);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tableViewE = new QTableView(groupBoxE);
        tableViewE->setObjectName(QStringLiteral("tableViewE"));

        gridLayout_5->addWidget(tableViewE, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxE, 1, 0, 1, 1);

        groupBoxF = new QGroupBox(groupBoxResults);
        groupBoxF->setObjectName(QStringLiteral("groupBoxF"));
        gridLayout_6 = new QGridLayout(groupBoxF);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        tableViewF = new QTableView(groupBoxF);
        tableViewF->setObjectName(QStringLiteral("tableViewF"));

        gridLayout_6->addWidget(tableViewF, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxF, 1, 1, 1, 1);

        groupBoxG = new QGroupBox(groupBoxResults);
        groupBoxG->setObjectName(QStringLiteral("groupBoxG"));
        gridLayout_7 = new QGridLayout(groupBoxG);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tableViewG = new QTableView(groupBoxG);
        tableViewG->setObjectName(QStringLiteral("tableViewG"));

        gridLayout_7->addWidget(tableViewG, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxG, 1, 2, 1, 1);

        groupBoxH = new QGroupBox(groupBoxResults);
        groupBoxH->setObjectName(QStringLiteral("groupBoxH"));
        gridLayout_8 = new QGridLayout(groupBoxH);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        tableViewH = new QTableView(groupBoxH);
        tableViewH->setObjectName(QStringLiteral("tableViewH"));

        gridLayout_8->addWidget(tableViewH, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBoxH, 1, 3, 1, 1);


        gridLayout_11->addWidget(groupBoxResults, 1, 0, 1, 1);


        retranslateUi(view_all_results);

        QMetaObject::connectSlotsByName(view_all_results);
    } // setupUi

    void retranslateUi(QWidget *view_all_results)
    {
        view_all_results->setWindowTitle(QApplication::translate("view_all_results", "Form", 0));
        groupBoxGames->setTitle(QApplication::translate("view_all_results", "n\303\244chste Spiele", 0));
        groupBoxResults->setTitle(QApplication::translate("view_all_results", "Ergebnisse", 0));
        groupBoxA->setTitle(QApplication::translate("view_all_results", "Gruppe A", 0));
        groupBoxB->setTitle(QApplication::translate("view_all_results", "Gruppe B", 0));
        groupBoxC->setTitle(QApplication::translate("view_all_results", "Gruppe C", 0));
        groupBoxD->setTitle(QApplication::translate("view_all_results", "Gruppe D", 0));
        groupBoxE->setTitle(QApplication::translate("view_all_results", "Gruppe E", 0));
        groupBoxF->setTitle(QApplication::translate("view_all_results", "Gruppe F", 0));
        groupBoxG->setTitle(QApplication::translate("view_all_results", "Gruppe G", 0));
        groupBoxH->setTitle(QApplication::translate("view_all_results", "Gruppe H", 0));
    } // retranslateUi

};

namespace Ui {
    class view_all_results: public Ui_view_all_results {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_ALL_RESULTS_H
