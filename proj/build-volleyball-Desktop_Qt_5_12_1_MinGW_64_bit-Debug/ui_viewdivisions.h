/********************************************************************************
** Form generated from reading UI file 'viewdivisions.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDIVISIONS_H
#define UI_VIEWDIVISIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ViewDivisions
{
public:
    QGridLayout *gridLayout_13;
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
    QGroupBox *groupBoxI;
    QGridLayout *gridLayout_9;
    QTableView *tableViewI;
    QGroupBox *groupBoxJ;
    QGridLayout *gridLayout_10;
    QTableView *tableViewJ;
    QGroupBox *groupBoxK;
    QGridLayout *gridLayout_11;
    QTableView *tableViewK;
    QGroupBox *groupBoxL;
    QGridLayout *gridLayout_12;
    QTableView *tableViewL;

    void setupUi(QDialog *ViewDivisions)
    {
        if (ViewDivisions->objectName().isEmpty())
            ViewDivisions->setObjectName(QString::fromUtf8("ViewDivisions"));
        ViewDivisions->setWindowModality(Qt::ApplicationModal);
        ViewDivisions->resize(1024, 640);
        gridLayout_13 = new QGridLayout(ViewDivisions);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        groupBoxA = new QGroupBox(ViewDivisions);
        groupBoxA->setObjectName(QString::fromUtf8("groupBoxA"));
        gridLayout = new QGridLayout(groupBoxA);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableViewA = new QTableView(groupBoxA);
        tableViewA->setObjectName(QString::fromUtf8("tableViewA"));
        tableViewA->horizontalHeader()->setStretchLastSection(false);
        tableViewA->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(tableViewA, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxA, 0, 0, 1, 1);

        groupBoxB = new QGroupBox(ViewDivisions);
        groupBoxB->setObjectName(QString::fromUtf8("groupBoxB"));
        gridLayout_2 = new QGridLayout(groupBoxB);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableViewB = new QTableView(groupBoxB);
        tableViewB->setObjectName(QString::fromUtf8("tableViewB"));

        gridLayout_2->addWidget(tableViewB, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxB, 0, 1, 1, 1);

        groupBoxC = new QGroupBox(ViewDivisions);
        groupBoxC->setObjectName(QString::fromUtf8("groupBoxC"));
        gridLayout_3 = new QGridLayout(groupBoxC);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableViewC = new QTableView(groupBoxC);
        tableViewC->setObjectName(QString::fromUtf8("tableViewC"));

        gridLayout_3->addWidget(tableViewC, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxC, 0, 2, 1, 1);

        groupBoxD = new QGroupBox(ViewDivisions);
        groupBoxD->setObjectName(QString::fromUtf8("groupBoxD"));
        gridLayout_4 = new QGridLayout(groupBoxD);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tableViewD = new QTableView(groupBoxD);
        tableViewD->setObjectName(QString::fromUtf8("tableViewD"));

        gridLayout_4->addWidget(tableViewD, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxD, 0, 4, 1, 1);

        groupBoxE = new QGroupBox(ViewDivisions);
        groupBoxE->setObjectName(QString::fromUtf8("groupBoxE"));
        gridLayout_5 = new QGridLayout(groupBoxE);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tableViewE = new QTableView(groupBoxE);
        tableViewE->setObjectName(QString::fromUtf8("tableViewE"));

        gridLayout_5->addWidget(tableViewE, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxE, 1, 0, 1, 1);

        groupBoxF = new QGroupBox(ViewDivisions);
        groupBoxF->setObjectName(QString::fromUtf8("groupBoxF"));
        gridLayout_6 = new QGridLayout(groupBoxF);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tableViewF = new QTableView(groupBoxF);
        tableViewF->setObjectName(QString::fromUtf8("tableViewF"));

        gridLayout_6->addWidget(tableViewF, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxF, 1, 1, 1, 1);

        groupBoxG = new QGroupBox(ViewDivisions);
        groupBoxG->setObjectName(QString::fromUtf8("groupBoxG"));
        gridLayout_7 = new QGridLayout(groupBoxG);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        tableViewG = new QTableView(groupBoxG);
        tableViewG->setObjectName(QString::fromUtf8("tableViewG"));

        gridLayout_7->addWidget(tableViewG, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxG, 1, 2, 1, 2);

        groupBoxH = new QGroupBox(ViewDivisions);
        groupBoxH->setObjectName(QString::fromUtf8("groupBoxH"));
        gridLayout_8 = new QGridLayout(groupBoxH);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        tableViewH = new QTableView(groupBoxH);
        tableViewH->setObjectName(QString::fromUtf8("tableViewH"));

        gridLayout_8->addWidget(tableViewH, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxH, 1, 4, 1, 1);

        groupBoxI = new QGroupBox(ViewDivisions);
        groupBoxI->setObjectName(QString::fromUtf8("groupBoxI"));
        gridLayout_9 = new QGridLayout(groupBoxI);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        tableViewI = new QTableView(groupBoxI);
        tableViewI->setObjectName(QString::fromUtf8("tableViewI"));

        gridLayout_9->addWidget(tableViewI, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxI, 2, 0, 1, 1);

        groupBoxJ = new QGroupBox(ViewDivisions);
        groupBoxJ->setObjectName(QString::fromUtf8("groupBoxJ"));
        gridLayout_10 = new QGridLayout(groupBoxJ);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        tableViewJ = new QTableView(groupBoxJ);
        tableViewJ->setObjectName(QString::fromUtf8("tableViewJ"));

        gridLayout_10->addWidget(tableViewJ, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxJ, 2, 1, 1, 1);

        groupBoxK = new QGroupBox(ViewDivisions);
        groupBoxK->setObjectName(QString::fromUtf8("groupBoxK"));
        gridLayout_11 = new QGridLayout(groupBoxK);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        tableViewK = new QTableView(groupBoxK);
        tableViewK->setObjectName(QString::fromUtf8("tableViewK"));

        gridLayout_11->addWidget(tableViewK, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxK, 2, 2, 1, 1);

        groupBoxL = new QGroupBox(ViewDivisions);
        groupBoxL->setObjectName(QString::fromUtf8("groupBoxL"));
        gridLayout_12 = new QGridLayout(groupBoxL);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        tableViewL = new QTableView(groupBoxL);
        tableViewL->setObjectName(QString::fromUtf8("tableViewL"));

        gridLayout_12->addWidget(tableViewL, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBoxL, 2, 3, 1, 2);


        retranslateUi(ViewDivisions);

        QMetaObject::connectSlotsByName(ViewDivisions);
    } // setupUi

    void retranslateUi(QDialog *ViewDivisions)
    {
        ViewDivisions->setWindowTitle(QApplication::translate("ViewDivisions", "Dialog", nullptr));
        groupBoxA->setTitle(QApplication::translate("ViewDivisions", "Gruppe A", nullptr));
        groupBoxB->setTitle(QApplication::translate("ViewDivisions", "Gruppe B", nullptr));
        groupBoxC->setTitle(QApplication::translate("ViewDivisions", "Gruppe C", nullptr));
        groupBoxD->setTitle(QApplication::translate("ViewDivisions", "Gruppe D", nullptr));
        groupBoxE->setTitle(QApplication::translate("ViewDivisions", "Gruppe E", nullptr));
        groupBoxF->setTitle(QApplication::translate("ViewDivisions", "Gruppe F", nullptr));
        groupBoxG->setTitle(QApplication::translate("ViewDivisions", "Gruppe G", nullptr));
        groupBoxH->setTitle(QApplication::translate("ViewDivisions", "Gruppe H", nullptr));
        groupBoxI->setTitle(QApplication::translate("ViewDivisions", "Gruppe I", nullptr));
        groupBoxJ->setTitle(QApplication::translate("ViewDivisions", "Gruppe J", nullptr));
        groupBoxK->setTitle(QApplication::translate("ViewDivisions", "Gruppe K", nullptr));
        groupBoxL->setTitle(QApplication::translate("ViewDivisions", "Gruppe L", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewDivisions: public Ui_ViewDivisions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDIVISIONS_H
