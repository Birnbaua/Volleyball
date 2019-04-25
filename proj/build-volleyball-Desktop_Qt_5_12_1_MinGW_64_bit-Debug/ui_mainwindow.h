/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionBeenden;
    QAction *actionShowlogfile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tabMannschaftenZeitplanung;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_turnier_2;
    QGridLayout *gridLayout_26;
    QSpinBox *spinBoxPauseZwKr;
    QLabel *label_pause_kr_pl_3;
    QSpinBox *spinBoxPauseVrZw;
    QLabel *label_pause_zw_kr_3;
    QSpinBox *spinBoxPauseKrPl;
    QTimeEdit *timeEditStartTurnier;
    QLabel *label_pause_vr_zw_2;
    QLabel *label_turnierstart_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_zwischenrunde_2;
    QGridLayout *gridLayout_23;
    QLabel *label_satz_zw_2;
    QSpinBox *spinBoxSatzZw;
    QLabel *label_min_pro_satz_zw_2;
    QSpinBox *spinBoxMinProSatzZw;
    QLabel *label_pause_min_zw_2;
    QSpinBox *spinBoxPauseMinZw;
    QGroupBox *groupBox_vorrunde_2;
    QGridLayout *gridLayout_24;
    QLabel *label_satz_vr_2;
    QSpinBox *spinBoxSatzVr;
    QLabel *label_min_pro_satz_vr_2;
    QSpinBox *spinBoxMinProSatzVr;
    QLabel *label_pause_min_vr_2;
    QSpinBox *spinBoxPauseMinVr;
    QGridLayout *gridLayout_30;
    QGroupBox *groupBox_platzspiele_finale_2;
    QGridLayout *gridLayout_31;
    QLabel *label_pause_zw_kr_4;
    QSpinBox *spinBoxMinProSatzPl;
    QSpinBox *spinBoxSatzPl;
    QLabel *label_satz_pl_2;
    QSpinBox *spinBoxZeitFinale;
    QLabel *label_pause_kr_pl_4;
    QLabel *label_zeit_pause_nach_finale_siegerehrung_2;
    QSpinBox *spinBoxPausePlEhrung;
    QGroupBox *groupBox_kreuzspiele_2;
    QGridLayout *gridLayout_32;
    QLabel *label_satz_kr_2;
    QLabel *label_min_pro_satz_kr_2;
    QSpinBox *spinBoxMinProSatzKr;
    QSpinBox *spinBoxPauseMinKr;
    QSpinBox *spinBoxSatzKr;
    QLabel *label_pause_min_kr_2;
    QGroupBox *groupBox_konfiguration_2;
    QGridLayout *gridLayout_6;
    QTableView *tableViewFields;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QPushButton *pushButtonConfigReset;
    QPushButton *pushButtonConfigRollback;
    QPushButton *pushButtonConfigSave;
    QSpinBox *spinBoxAnzahlfelder;
    QLabel *label_anzahl_felder_2;
    QCheckBox *checkBoxKreuzspiele;
    QCheckBox *checkBoxBettysPlan;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_mannschaften_2;
    QGridLayout *gridLayout_29;
    QPushButton *pushButtonResetTeams;
    QPushButton *pushButtonSaveTeams;
    QPushButton *pushButtonPrintTeams;
    QSpacerItem *horizontalSpacer_6;
    QTableView *tableViewTeams;
    QWidget *tab_vorrunde_2;
    QGridLayout *gridLayout_33;
    QGridLayout *gridLayout_34;
    QPushButton *pushButtonVrClear;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonVrGenerate;
    QPushButton *pushButtonVrChangeGames;
    QPushButton *pushButtonVrResult;
    QPushButton *pushButtonVrPrint;
    QPushButton *pushButtonVrSave;
    QPushButton *pushButtonVrAllResults;
    QTableView *tableViewVorrunde;
    QWidget *tab_zwischenrunde_2;
    QGridLayout *gridLayout_35;
    QGridLayout *gridLayout_36;
    QPushButton *pushButtonZwClear;
    QPushButton *pushButtonZwSave;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButtonZwChangeGames;
    QPushButton *pushButtonZwGenerate;
    QPushButton *pushButtonZwPrint;
    QPushButton *pushButtonZwResult;
    QTableView *tableViewZwischenrunde;
    QWidget *tab_kreuzspiele_2;
    QGridLayout *gridLayout_37;
    QGridLayout *gridLayout_38;
    QPushButton *pushButtonKrClear;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButtonKrSave;
    QPushButton *pushButtonKrGenerate;
    QPushButton *pushButtonKrPrint;
    QTableView *tableViewKreuzspiele;
    QWidget *tab_platzspiele_2;
    QGridLayout *gridLayout_39;
    QGridLayout *gridLayout_40;
    QPushButton *pushButtonPlClear;
    QPushButton *pushButtonPlResult;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButtonPlGenerate;
    QPushButton *pushButtonPlSave;
    QPushButton *pushButtonPlPrint;
    QTableView *tableViewPlatzspiele;
    QLabel *labelTournamentEnd;
    QLabel *labelTournamentEndValue;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuHilfe;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionBeenden = new QAction(MainWindow);
        actionBeenden->setObjectName(QString::fromUtf8("actionBeenden"));
        actionShowlogfile = new QAction(MainWindow);
        actionShowlogfile->setObjectName(QString::fromUtf8("actionShowlogfile"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabMannschaftenZeitplanung = new QWidget();
        tabMannschaftenZeitplanung->setObjectName(QString::fromUtf8("tabMannschaftenZeitplanung"));
        gridLayout_3 = new QGridLayout(tabMannschaftenZeitplanung);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_turnier_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_turnier_2->setObjectName(QString::fromUtf8("groupBox_turnier_2"));
        gridLayout_26 = new QGridLayout(groupBox_turnier_2);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        spinBoxPauseZwKr = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseZwKr->setObjectName(QString::fromUtf8("spinBoxPauseZwKr"));
        spinBoxPauseZwKr->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseZwKr, 2, 2, 1, 1);

        label_pause_kr_pl_3 = new QLabel(groupBox_turnier_2);
        label_pause_kr_pl_3->setObjectName(QString::fromUtf8("label_pause_kr_pl_3"));

        gridLayout_26->addWidget(label_pause_kr_pl_3, 3, 0, 1, 1);

        spinBoxPauseVrZw = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseVrZw->setObjectName(QString::fromUtf8("spinBoxPauseVrZw"));
        spinBoxPauseVrZw->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseVrZw, 1, 2, 1, 1);

        label_pause_zw_kr_3 = new QLabel(groupBox_turnier_2);
        label_pause_zw_kr_3->setObjectName(QString::fromUtf8("label_pause_zw_kr_3"));

        gridLayout_26->addWidget(label_pause_zw_kr_3, 2, 0, 1, 1);

        spinBoxPauseKrPl = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseKrPl->setObjectName(QString::fromUtf8("spinBoxPauseKrPl"));
        spinBoxPauseKrPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseKrPl, 3, 2, 1, 1);

        timeEditStartTurnier = new QTimeEdit(groupBox_turnier_2);
        timeEditStartTurnier->setObjectName(QString::fromUtf8("timeEditStartTurnier"));

        gridLayout_26->addWidget(timeEditStartTurnier, 0, 2, 1, 1);

        label_pause_vr_zw_2 = new QLabel(groupBox_turnier_2);
        label_pause_vr_zw_2->setObjectName(QString::fromUtf8("label_pause_vr_zw_2"));

        gridLayout_26->addWidget(label_pause_vr_zw_2, 1, 0, 1, 1);

        label_turnierstart_2 = new QLabel(groupBox_turnier_2);
        label_turnierstart_2->setObjectName(QString::fromUtf8("label_turnierstart_2"));

        gridLayout_26->addWidget(label_turnierstart_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_26->addItem(horizontalSpacer_2, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_turnier_2, 0, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        groupBox_zwischenrunde_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_zwischenrunde_2->setObjectName(QString::fromUtf8("groupBox_zwischenrunde_2"));
        gridLayout_23 = new QGridLayout(groupBox_zwischenrunde_2);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        label_satz_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_satz_zw_2->setObjectName(QString::fromUtf8("label_satz_zw_2"));

        gridLayout_23->addWidget(label_satz_zw_2, 0, 0, 1, 1);

        spinBoxSatzZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxSatzZw->setObjectName(QString::fromUtf8("spinBoxSatzZw"));
        spinBoxSatzZw->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzZw->setMinimum(1);

        gridLayout_23->addWidget(spinBoxSatzZw, 0, 1, 1, 1);

        label_min_pro_satz_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_min_pro_satz_zw_2->setObjectName(QString::fromUtf8("label_min_pro_satz_zw_2"));

        gridLayout_23->addWidget(label_min_pro_satz_zw_2, 1, 0, 1, 1);

        spinBoxMinProSatzZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxMinProSatzZw->setObjectName(QString::fromUtf8("spinBoxMinProSatzZw"));
        spinBoxMinProSatzZw->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzZw->setMinimum(1);

        gridLayout_23->addWidget(spinBoxMinProSatzZw, 1, 1, 1, 1);

        label_pause_min_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_pause_min_zw_2->setObjectName(QString::fromUtf8("label_pause_min_zw_2"));

        gridLayout_23->addWidget(label_pause_min_zw_2, 2, 0, 1, 1);

        spinBoxPauseMinZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxPauseMinZw->setObjectName(QString::fromUtf8("spinBoxPauseMinZw"));
        spinBoxPauseMinZw->setMaximumSize(QSize(50, 16777215));

        gridLayout_23->addWidget(spinBoxPauseMinZw, 2, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_zwischenrunde_2, 0, 1, 1, 1);

        groupBox_vorrunde_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_vorrunde_2->setObjectName(QString::fromUtf8("groupBox_vorrunde_2"));
        gridLayout_24 = new QGridLayout(groupBox_vorrunde_2);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        label_satz_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_satz_vr_2->setObjectName(QString::fromUtf8("label_satz_vr_2"));

        gridLayout_24->addWidget(label_satz_vr_2, 0, 0, 1, 1);

        spinBoxSatzVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxSatzVr->setObjectName(QString::fromUtf8("spinBoxSatzVr"));
        spinBoxSatzVr->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzVr->setMinimum(1);

        gridLayout_24->addWidget(spinBoxSatzVr, 0, 1, 1, 1);

        label_min_pro_satz_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_min_pro_satz_vr_2->setObjectName(QString::fromUtf8("label_min_pro_satz_vr_2"));

        gridLayout_24->addWidget(label_min_pro_satz_vr_2, 1, 0, 1, 1);

        spinBoxMinProSatzVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxMinProSatzVr->setObjectName(QString::fromUtf8("spinBoxMinProSatzVr"));
        spinBoxMinProSatzVr->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzVr->setMinimum(1);

        gridLayout_24->addWidget(spinBoxMinProSatzVr, 1, 1, 1, 1);

        label_pause_min_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_pause_min_vr_2->setObjectName(QString::fromUtf8("label_pause_min_vr_2"));

        gridLayout_24->addWidget(label_pause_min_vr_2, 2, 0, 1, 1);

        spinBoxPauseMinVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxPauseMinVr->setObjectName(QString::fromUtf8("spinBoxPauseMinVr"));
        spinBoxPauseMinVr->setMaximumSize(QSize(50, 16777215));

        gridLayout_24->addWidget(spinBoxPauseMinVr, 2, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_vorrunde_2, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_10, 1, 0, 1, 1);

        gridLayout_30 = new QGridLayout();
        gridLayout_30->setSpacing(6);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        groupBox_platzspiele_finale_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_platzspiele_finale_2->setObjectName(QString::fromUtf8("groupBox_platzspiele_finale_2"));
        gridLayout_31 = new QGridLayout(groupBox_platzspiele_finale_2);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        label_pause_zw_kr_4 = new QLabel(groupBox_platzspiele_finale_2);
        label_pause_zw_kr_4->setObjectName(QString::fromUtf8("label_pause_zw_kr_4"));

        gridLayout_31->addWidget(label_pause_zw_kr_4, 1, 0, 1, 1);

        spinBoxMinProSatzPl = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxMinProSatzPl->setObjectName(QString::fromUtf8("spinBoxMinProSatzPl"));
        spinBoxMinProSatzPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxMinProSatzPl, 1, 1, 1, 1);

        spinBoxSatzPl = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxSatzPl->setObjectName(QString::fromUtf8("spinBoxSatzPl"));
        spinBoxSatzPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxSatzPl, 0, 1, 1, 1);

        label_satz_pl_2 = new QLabel(groupBox_platzspiele_finale_2);
        label_satz_pl_2->setObjectName(QString::fromUtf8("label_satz_pl_2"));

        gridLayout_31->addWidget(label_satz_pl_2, 0, 0, 1, 1);

        spinBoxZeitFinale = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxZeitFinale->setObjectName(QString::fromUtf8("spinBoxZeitFinale"));
        spinBoxZeitFinale->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxZeitFinale, 2, 1, 1, 1);

        label_pause_kr_pl_4 = new QLabel(groupBox_platzspiele_finale_2);
        label_pause_kr_pl_4->setObjectName(QString::fromUtf8("label_pause_kr_pl_4"));

        gridLayout_31->addWidget(label_pause_kr_pl_4, 2, 0, 1, 1);

        label_zeit_pause_nach_finale_siegerehrung_2 = new QLabel(groupBox_platzspiele_finale_2);
        label_zeit_pause_nach_finale_siegerehrung_2->setObjectName(QString::fromUtf8("label_zeit_pause_nach_finale_siegerehrung_2"));

        gridLayout_31->addWidget(label_zeit_pause_nach_finale_siegerehrung_2, 4, 0, 1, 1);

        spinBoxPausePlEhrung = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxPausePlEhrung->setObjectName(QString::fromUtf8("spinBoxPausePlEhrung"));
        spinBoxPausePlEhrung->setMaximum(999);

        gridLayout_31->addWidget(spinBoxPausePlEhrung, 4, 1, 1, 1);


        gridLayout_30->addWidget(groupBox_platzspiele_finale_2, 0, 1, 1, 1);

        groupBox_kreuzspiele_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_kreuzspiele_2->setObjectName(QString::fromUtf8("groupBox_kreuzspiele_2"));
        gridLayout_32 = new QGridLayout(groupBox_kreuzspiele_2);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        label_satz_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_satz_kr_2->setObjectName(QString::fromUtf8("label_satz_kr_2"));

        gridLayout_32->addWidget(label_satz_kr_2, 0, 0, 1, 1);

        label_min_pro_satz_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_min_pro_satz_kr_2->setObjectName(QString::fromUtf8("label_min_pro_satz_kr_2"));

        gridLayout_32->addWidget(label_min_pro_satz_kr_2, 1, 0, 1, 1);

        spinBoxMinProSatzKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxMinProSatzKr->setObjectName(QString::fromUtf8("spinBoxMinProSatzKr"));
        spinBoxMinProSatzKr->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzKr->setMinimum(1);

        gridLayout_32->addWidget(spinBoxMinProSatzKr, 1, 1, 1, 1);

        spinBoxPauseMinKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxPauseMinKr->setObjectName(QString::fromUtf8("spinBoxPauseMinKr"));
        spinBoxPauseMinKr->setMaximumSize(QSize(50, 16777215));

        gridLayout_32->addWidget(spinBoxPauseMinKr, 2, 1, 1, 1);

        spinBoxSatzKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxSatzKr->setObjectName(QString::fromUtf8("spinBoxSatzKr"));
        spinBoxSatzKr->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzKr->setMinimum(1);

        gridLayout_32->addWidget(spinBoxSatzKr, 0, 1, 1, 1);

        label_pause_min_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_pause_min_kr_2->setObjectName(QString::fromUtf8("label_pause_min_kr_2"));

        gridLayout_32->addWidget(label_pause_min_kr_2, 2, 0, 1, 1);


        gridLayout_30->addWidget(groupBox_kreuzspiele_2, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_30, 2, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        groupBox_konfiguration_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_konfiguration_2->setObjectName(QString::fromUtf8("groupBox_konfiguration_2"));
        gridLayout_6 = new QGridLayout(groupBox_konfiguration_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        tableViewFields = new QTableView(groupBox_konfiguration_2);
        tableViewFields->setObjectName(QString::fromUtf8("tableViewFields"));
        tableViewFields->setAlternatingRowColors(true);
        tableViewFields->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewFields->horizontalHeader()->setStretchLastSection(true);
        tableViewFields->verticalHeader()->setVisible(false);
        tableViewFields->verticalHeader()->setStretchLastSection(true);

        gridLayout_6->addWidget(tableViewFields, 0, 0, 1, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButtonConfigReset = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigReset->setObjectName(QString::fromUtf8("pushButtonConfigReset"));

        gridLayout_4->addWidget(pushButtonConfigReset, 5, 0, 1, 2);

        pushButtonConfigRollback = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigRollback->setObjectName(QString::fromUtf8("pushButtonConfigRollback"));

        gridLayout_4->addWidget(pushButtonConfigRollback, 4, 0, 1, 2);

        pushButtonConfigSave = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigSave->setObjectName(QString::fromUtf8("pushButtonConfigSave"));

        gridLayout_4->addWidget(pushButtonConfigSave, 3, 0, 1, 2);

        spinBoxAnzahlfelder = new QSpinBox(groupBox_konfiguration_2);
        spinBoxAnzahlfelder->setObjectName(QString::fromUtf8("spinBoxAnzahlfelder"));
        spinBoxAnzahlfelder->setMaximumSize(QSize(50, 16777215));
        spinBoxAnzahlfelder->setMinimum(1);

        gridLayout_4->addWidget(spinBoxAnzahlfelder, 0, 1, 1, 1);

        label_anzahl_felder_2 = new QLabel(groupBox_konfiguration_2);
        label_anzahl_felder_2->setObjectName(QString::fromUtf8("label_anzahl_felder_2"));

        gridLayout_4->addWidget(label_anzahl_felder_2, 0, 0, 1, 1);

        checkBoxKreuzspiele = new QCheckBox(groupBox_konfiguration_2);
        checkBoxKreuzspiele->setObjectName(QString::fromUtf8("checkBoxKreuzspiele"));

        gridLayout_4->addWidget(checkBoxKreuzspiele, 1, 0, 1, 2);

        checkBoxBettysPlan = new QCheckBox(groupBox_konfiguration_2);
        checkBoxBettysPlan->setObjectName(QString::fromUtf8("checkBoxBettysPlan"));

        gridLayout_4->addWidget(checkBoxBettysPlan, 2, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_konfiguration_2, 0, 1, 1, 1);

        groupBox_mannschaften_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_mannschaften_2->setObjectName(QString::fromUtf8("groupBox_mannschaften_2"));
        groupBox_mannschaften_2->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_29 = new QGridLayout(groupBox_mannschaften_2);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        pushButtonResetTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonResetTeams->setObjectName(QString::fromUtf8("pushButtonResetTeams"));

        gridLayout_29->addWidget(pushButtonResetTeams, 0, 1, 1, 1);

        pushButtonSaveTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonSaveTeams->setObjectName(QString::fromUtf8("pushButtonSaveTeams"));

        gridLayout_29->addWidget(pushButtonSaveTeams, 0, 0, 1, 1);

        pushButtonPrintTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonPrintTeams->setObjectName(QString::fromUtf8("pushButtonPrintTeams"));

        gridLayout_29->addWidget(pushButtonPrintTeams, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_29->addItem(horizontalSpacer_6, 0, 3, 1, 1);

        tableViewTeams = new QTableView(groupBox_mannschaften_2);
        tableViewTeams->setObjectName(QString::fromUtf8("tableViewTeams"));
        tableViewTeams->setMinimumSize(QSize(0, 0));
        tableViewTeams->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableViewTeams->setAlternatingRowColors(true);
        tableViewTeams->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewTeams->horizontalHeader()->setStretchLastSection(true);
        tableViewTeams->verticalHeader()->setVisible(false);
        tableViewTeams->verticalHeader()->setStretchLastSection(true);

        gridLayout_29->addWidget(tableViewTeams, 1, 0, 1, 4);


        gridLayout_3->addWidget(groupBox_mannschaften_2, 1, 0, 1, 2);

        tabWidget->addTab(tabMannschaftenZeitplanung, QString());
        tab_vorrunde_2 = new QWidget();
        tab_vorrunde_2->setObjectName(QString::fromUtf8("tab_vorrunde_2"));
        gridLayout_33 = new QGridLayout(tab_vorrunde_2);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        gridLayout_34 = new QGridLayout();
        gridLayout_34->setSpacing(6);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        pushButtonVrClear = new QPushButton(tab_vorrunde_2);
        pushButtonVrClear->setObjectName(QString::fromUtf8("pushButtonVrClear"));

        gridLayout_34->addWidget(pushButtonVrClear, 0, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_7, 0, 7, 1, 1);

        pushButtonVrGenerate = new QPushButton(tab_vorrunde_2);
        pushButtonVrGenerate->setObjectName(QString::fromUtf8("pushButtonVrGenerate"));

        gridLayout_34->addWidget(pushButtonVrGenerate, 0, 0, 1, 1);

        pushButtonVrChangeGames = new QPushButton(tab_vorrunde_2);
        pushButtonVrChangeGames->setObjectName(QString::fromUtf8("pushButtonVrChangeGames"));

        gridLayout_34->addWidget(pushButtonVrChangeGames, 0, 4, 1, 1);

        pushButtonVrResult = new QPushButton(tab_vorrunde_2);
        pushButtonVrResult->setObjectName(QString::fromUtf8("pushButtonVrResult"));

        gridLayout_34->addWidget(pushButtonVrResult, 0, 8, 1, 1);

        pushButtonVrPrint = new QPushButton(tab_vorrunde_2);
        pushButtonVrPrint->setObjectName(QString::fromUtf8("pushButtonVrPrint"));

        gridLayout_34->addWidget(pushButtonVrPrint, 0, 5, 1, 1);

        pushButtonVrSave = new QPushButton(tab_vorrunde_2);
        pushButtonVrSave->setObjectName(QString::fromUtf8("pushButtonVrSave"));

        gridLayout_34->addWidget(pushButtonVrSave, 0, 1, 1, 1);

        pushButtonVrAllResults = new QPushButton(tab_vorrunde_2);
        pushButtonVrAllResults->setObjectName(QString::fromUtf8("pushButtonVrAllResults"));

        gridLayout_34->addWidget(pushButtonVrAllResults, 0, 9, 1, 1);


        gridLayout_33->addLayout(gridLayout_34, 0, 0, 1, 1);

        tableViewVorrunde = new QTableView(tab_vorrunde_2);
        tableViewVorrunde->setObjectName(QString::fromUtf8("tableViewVorrunde"));
        tableViewVorrunde->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewVorrunde->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewVorrunde->horizontalHeader()->setStretchLastSection(true);
        tableViewVorrunde->verticalHeader()->setVisible(false);

        gridLayout_33->addWidget(tableViewVorrunde, 1, 0, 1, 1);

        tabWidget->addTab(tab_vorrunde_2, QString());
        tab_zwischenrunde_2 = new QWidget();
        tab_zwischenrunde_2->setObjectName(QString::fromUtf8("tab_zwischenrunde_2"));
        gridLayout_35 = new QGridLayout(tab_zwischenrunde_2);
        gridLayout_35->setSpacing(6);
        gridLayout_35->setContentsMargins(11, 11, 11, 11);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        gridLayout_36 = new QGridLayout();
        gridLayout_36->setSpacing(6);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        pushButtonZwClear = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwClear->setObjectName(QString::fromUtf8("pushButtonZwClear"));

        gridLayout_36->addWidget(pushButtonZwClear, 0, 2, 1, 1);

        pushButtonZwSave = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwSave->setObjectName(QString::fromUtf8("pushButtonZwSave"));

        gridLayout_36->addWidget(pushButtonZwSave, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_36->addItem(horizontalSpacer_8, 0, 5, 1, 1);

        pushButtonZwChangeGames = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwChangeGames->setObjectName(QString::fromUtf8("pushButtonZwChangeGames"));

        gridLayout_36->addWidget(pushButtonZwChangeGames, 0, 3, 1, 1);

        pushButtonZwGenerate = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwGenerate->setObjectName(QString::fromUtf8("pushButtonZwGenerate"));

        gridLayout_36->addWidget(pushButtonZwGenerate, 0, 0, 1, 1);

        pushButtonZwPrint = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwPrint->setObjectName(QString::fromUtf8("pushButtonZwPrint"));

        gridLayout_36->addWidget(pushButtonZwPrint, 0, 4, 1, 1);

        pushButtonZwResult = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwResult->setObjectName(QString::fromUtf8("pushButtonZwResult"));

        gridLayout_36->addWidget(pushButtonZwResult, 0, 6, 1, 1);


        gridLayout_35->addLayout(gridLayout_36, 0, 0, 1, 1);

        tableViewZwischenrunde = new QTableView(tab_zwischenrunde_2);
        tableViewZwischenrunde->setObjectName(QString::fromUtf8("tableViewZwischenrunde"));
        tableViewZwischenrunde->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewZwischenrunde->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewZwischenrunde->horizontalHeader()->setStretchLastSection(true);
        tableViewZwischenrunde->verticalHeader()->setVisible(false);

        gridLayout_35->addWidget(tableViewZwischenrunde, 1, 0, 1, 1);

        tabWidget->addTab(tab_zwischenrunde_2, QString());
        tab_kreuzspiele_2 = new QWidget();
        tab_kreuzspiele_2->setObjectName(QString::fromUtf8("tab_kreuzspiele_2"));
        gridLayout_37 = new QGridLayout(tab_kreuzspiele_2);
        gridLayout_37->setSpacing(6);
        gridLayout_37->setContentsMargins(11, 11, 11, 11);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        gridLayout_38 = new QGridLayout();
        gridLayout_38->setSpacing(6);
        gridLayout_38->setObjectName(QString::fromUtf8("gridLayout_38"));
        pushButtonKrClear = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrClear->setObjectName(QString::fromUtf8("pushButtonKrClear"));

        gridLayout_38->addWidget(pushButtonKrClear, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_38->addItem(horizontalSpacer_9, 0, 4, 1, 1);

        pushButtonKrSave = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrSave->setObjectName(QString::fromUtf8("pushButtonKrSave"));

        gridLayout_38->addWidget(pushButtonKrSave, 0, 1, 1, 1);

        pushButtonKrGenerate = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrGenerate->setObjectName(QString::fromUtf8("pushButtonKrGenerate"));

        gridLayout_38->addWidget(pushButtonKrGenerate, 0, 0, 1, 1);

        pushButtonKrPrint = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrPrint->setObjectName(QString::fromUtf8("pushButtonKrPrint"));

        gridLayout_38->addWidget(pushButtonKrPrint, 0, 3, 1, 1);


        gridLayout_37->addLayout(gridLayout_38, 0, 0, 1, 1);

        tableViewKreuzspiele = new QTableView(tab_kreuzspiele_2);
        tableViewKreuzspiele->setObjectName(QString::fromUtf8("tableViewKreuzspiele"));
        tableViewKreuzspiele->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewKreuzspiele->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewKreuzspiele->horizontalHeader()->setStretchLastSection(true);
        tableViewKreuzspiele->verticalHeader()->setVisible(false);

        gridLayout_37->addWidget(tableViewKreuzspiele, 1, 0, 1, 1);

        tabWidget->addTab(tab_kreuzspiele_2, QString());
        tab_platzspiele_2 = new QWidget();
        tab_platzspiele_2->setObjectName(QString::fromUtf8("tab_platzspiele_2"));
        gridLayout_39 = new QGridLayout(tab_platzspiele_2);
        gridLayout_39->setSpacing(6);
        gridLayout_39->setContentsMargins(11, 11, 11, 11);
        gridLayout_39->setObjectName(QString::fromUtf8("gridLayout_39"));
        gridLayout_40 = new QGridLayout();
        gridLayout_40->setSpacing(6);
        gridLayout_40->setObjectName(QString::fromUtf8("gridLayout_40"));
        pushButtonPlClear = new QPushButton(tab_platzspiele_2);
        pushButtonPlClear->setObjectName(QString::fromUtf8("pushButtonPlClear"));

        gridLayout_40->addWidget(pushButtonPlClear, 0, 2, 1, 1);

        pushButtonPlResult = new QPushButton(tab_platzspiele_2);
        pushButtonPlResult->setObjectName(QString::fromUtf8("pushButtonPlResult"));

        gridLayout_40->addWidget(pushButtonPlResult, 0, 5, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_40->addItem(horizontalSpacer_10, 0, 4, 1, 1);

        pushButtonPlGenerate = new QPushButton(tab_platzspiele_2);
        pushButtonPlGenerate->setObjectName(QString::fromUtf8("pushButtonPlGenerate"));

        gridLayout_40->addWidget(pushButtonPlGenerate, 0, 0, 1, 1);

        pushButtonPlSave = new QPushButton(tab_platzspiele_2);
        pushButtonPlSave->setObjectName(QString::fromUtf8("pushButtonPlSave"));

        gridLayout_40->addWidget(pushButtonPlSave, 0, 1, 1, 1);

        pushButtonPlPrint = new QPushButton(tab_platzspiele_2);
        pushButtonPlPrint->setObjectName(QString::fromUtf8("pushButtonPlPrint"));

        gridLayout_40->addWidget(pushButtonPlPrint, 0, 3, 1, 1);


        gridLayout_39->addLayout(gridLayout_40, 0, 0, 1, 1);

        tableViewPlatzspiele = new QTableView(tab_platzspiele_2);
        tableViewPlatzspiele->setObjectName(QString::fromUtf8("tableViewPlatzspiele"));
        tableViewPlatzspiele->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewPlatzspiele->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewPlatzspiele->horizontalHeader()->setStretchLastSection(true);
        tableViewPlatzspiele->verticalHeader()->setVisible(false);

        gridLayout_39->addWidget(tableViewPlatzspiele, 1, 0, 1, 1);

        tabWidget->addTab(tab_platzspiele_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 4);

        labelTournamentEnd = new QLabel(centralWidget);
        labelTournamentEnd->setObjectName(QString::fromUtf8("labelTournamentEnd"));

        gridLayout->addWidget(labelTournamentEnd, 1, 0, 1, 1);

        labelTournamentEndValue = new QLabel(centralWidget);
        labelTournamentEndValue->setObjectName(QString::fromUtf8("labelTournamentEndValue"));
        labelTournamentEndValue->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(labelTournamentEndValue, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(357, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 18));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuHilfe = new QMenu(menuBar);
        menuHilfe->setObjectName(QString::fromUtf8("menuHilfe"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionBeenden);
        menuHilfe->addAction(actionShowlogfile);
        menuHilfe->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionAbout->setText(QApplication::translate("MainWindow", "Info", nullptr));
        actionBeenden->setText(QApplication::translate("MainWindow", "Beenden", nullptr));
        actionShowlogfile->setText(QApplication::translate("MainWindow", "zeige Logfile", nullptr));
        groupBox_turnier_2->setTitle(QApplication::translate("MainWindow", "Turnierstart und Pausenzeit", nullptr));
        label_pause_kr_pl_3->setText(QApplication::translate("MainWindow", "Pause zw. Kreuz- und Platzierungsspiele", nullptr));
        label_pause_zw_kr_3->setText(QApplication::translate("MainWindow", "Pause zw. Zwischenrunde und Kreuzspiele", nullptr));
        timeEditStartTurnier->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm", nullptr));
        label_pause_vr_zw_2->setText(QApplication::translate("MainWindow", "Pause zw. Vor- und Zwischenrunde", nullptr));
        label_turnierstart_2->setText(QApplication::translate("MainWindow", "Start Turnier (hh:mm)", nullptr));
        groupBox_zwischenrunde_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Zwischenrunde", nullptr));
        label_satz_zw_2->setText(QApplication::translate("MainWindow", "S\303\244tze", nullptr));
        label_min_pro_satz_zw_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", nullptr));
        label_pause_min_zw_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", nullptr));
        groupBox_vorrunde_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Vorrunde", nullptr));
        label_satz_vr_2->setText(QApplication::translate("MainWindow", "S\303\244tze", nullptr));
        label_min_pro_satz_vr_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", nullptr));
        label_pause_min_vr_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", nullptr));
        groupBox_platzspiele_finale_2->setTitle(QApplication::translate("MainWindow", "Zeitplan Platzierungsspiele und Finale", nullptr));
        label_pause_zw_kr_4->setText(QApplication::translate("MainWindow", "gesch\303\244tzte Platzierungsspielzeit pro Satz (min)", nullptr));
        label_satz_pl_2->setText(QApplication::translate("MainWindow", "S\303\244tze", nullptr));
        label_pause_kr_pl_4->setText(QApplication::translate("MainWindow", "gesch\303\244tzte Spielzeit Finale (min)", nullptr));
        label_zeit_pause_nach_finale_siegerehrung_2->setText(QApplication::translate("MainWindow", "Dauer Pause inkl. Siegerehrung nach Finale", nullptr));
        groupBox_kreuzspiele_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Kreuzspiele", nullptr));
        label_satz_kr_2->setText(QApplication::translate("MainWindow", "S\303\244tze", nullptr));
        label_min_pro_satz_kr_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", nullptr));
        label_pause_min_kr_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", nullptr));
        groupBox_konfiguration_2->setTitle(QApplication::translate("MainWindow", "erweiterte Konfiguration", nullptr));
        pushButtonConfigReset->setText(QApplication::translate("MainWindow", "Konfiguration zur\303\274cksetzen", nullptr));
        pushButtonConfigRollback->setText(QApplication::translate("MainWindow", "\303\204nderungen verwerfen", nullptr));
        pushButtonConfigSave->setText(QApplication::translate("MainWindow", "\303\204nderungen speichern", nullptr));
        label_anzahl_felder_2->setText(QApplication::translate("MainWindow", "Anzahl Spielfelder", nullptr));
        checkBoxKreuzspiele->setText(QApplication::translate("MainWindow", "Kreuzspiele", nullptr));
        checkBoxBettysPlan->setText(QApplication::translate("MainWindow", "Bettys Plan (50, 55 u. 60 teams)", nullptr));
        groupBox_mannschaften_2->setTitle(QApplication::translate("MainWindow", "Mannschaften", nullptr));
        pushButtonResetTeams->setText(QApplication::translate("MainWindow", "Mannschaften l\303\266schen", nullptr));
        pushButtonSaveTeams->setText(QApplication::translate("MainWindow", "Mannschaften speichern", nullptr));
        pushButtonPrintTeams->setText(QApplication::translate("MainWindow", "Mannschaften drucken", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabMannschaftenZeitplanung), QApplication::translate("MainWindow", "Mannschaften/Zeitplanung", nullptr));
        pushButtonVrClear->setText(QApplication::translate("MainWindow", "L\303\266schen", nullptr));
        pushButtonVrGenerate->setText(QApplication::translate("MainWindow", "Generieren", nullptr));
        pushButtonVrChangeGames->setText(QApplication::translate("MainWindow", "Spiele tauschen", nullptr));
        pushButtonVrResult->setText(QApplication::translate("MainWindow", "Ergebnisse", nullptr));
        pushButtonVrPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", nullptr));
        pushButtonVrSave->setText(QApplication::translate("MainWindow", "Speichern", nullptr));
        pushButtonVrAllResults->setText(QApplication::translate("MainWindow", "Gesamtreihung", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_vorrunde_2), QApplication::translate("MainWindow", "Vorrunde", nullptr));
        pushButtonZwClear->setText(QApplication::translate("MainWindow", "L\303\266schen", nullptr));
        pushButtonZwSave->setText(QApplication::translate("MainWindow", "Speichern", nullptr));
        pushButtonZwChangeGames->setText(QApplication::translate("MainWindow", "Spiele tauschen", nullptr));
        pushButtonZwGenerate->setText(QApplication::translate("MainWindow", "Generieren", nullptr));
        pushButtonZwPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", nullptr));
        pushButtonZwResult->setText(QApplication::translate("MainWindow", "Ergebnisse", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_zwischenrunde_2), QApplication::translate("MainWindow", "Zwischenrunde", nullptr));
        pushButtonKrClear->setText(QApplication::translate("MainWindow", "L\303\266schen", nullptr));
        pushButtonKrSave->setText(QApplication::translate("MainWindow", "Speichern", nullptr));
        pushButtonKrGenerate->setText(QApplication::translate("MainWindow", "Generieren", nullptr));
        pushButtonKrPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_kreuzspiele_2), QApplication::translate("MainWindow", "Kreuzspiele", nullptr));
        pushButtonPlClear->setText(QApplication::translate("MainWindow", "L\303\266schen", nullptr));
        pushButtonPlResult->setText(QApplication::translate("MainWindow", "Ergebnisse", nullptr));
        pushButtonPlGenerate->setText(QApplication::translate("MainWindow", "Generieren", nullptr));
        pushButtonPlSave->setText(QApplication::translate("MainWindow", "Speichern", nullptr));
        pushButtonPlPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_platzspiele_2), QApplication::translate("MainWindow", "Platzierungsspiele", nullptr));
        labelTournamentEnd->setText(QApplication::translate("MainWindow", "voraussichtliches Turnierende", nullptr));
        labelTournamentEndValue->setText(QString());
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", nullptr));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "Hilfe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
