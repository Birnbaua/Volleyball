/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *labelTournamentEnd;
    QTabWidget *tabWidget;
    QWidget *tabMannschaftenZeitplanung;
    QGridLayout *gridLayout_22;
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
    QGridLayout *gridLayout_25;
    QGroupBox *groupBox_turnier_2;
    QGridLayout *gridLayout_26;
    QLabel *label_pause_vr_zw_2;
    QLabel *label_turnierstart_2;
    QLabel *label_pause_zw_kr_3;
    QSpinBox *spinBoxPauseZwKr;
    QLabel *label_pause_kr_pl_3;
    QSpinBox *spinBoxPauseVrZw;
    QSpinBox *spinBoxPauseKrPl;
    QTimeEdit *timeEditStartTurnier;
    QGroupBox *groupBox_konfiguration_2;
    QGridLayout *gridLayout_27;
    QTableView *tableViewFields;
    QGridLayout *gridLayout_28;
    QLabel *label_anzahl_felder_2;
    QSpinBox *spinBoxAnzahlfelder;
    QCheckBox *checkBoxKreuzspiele;
    QPushButton *pushButtonConfigSave;
    QPushButton *pushButtonConfigRollback;
    QPushButton *pushButtonConfigReset;
    QGroupBox *groupBox_mannschaften_2;
    QGridLayout *gridLayout_29;
    QPushButton *pushButtonResetTeams;
    QPushButton *pushButtonSaveTeams;
    QPushButton *pushButtonPrintTeams;
    QSpacerItem *horizontalSpacer_6;
    QTableView *tableViewTeams;
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
    QTableView *tableViewVorrunde;
    QWidget *tab_zwischenrunde_2;
    QGridLayout *gridLayout_35;
    QGridLayout *gridLayout_36;
    QPushButton *pushButtonZwResult;
    QPushButton *pushButtonZwGenerate;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButtonZwSave;
    QPushButton *pushButtonZwClear;
    QPushButton *pushButtonZwChangeGames;
    QPushButton *pushButtonZwPrint;
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
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonShowAllResultsWindow;
    QLabel *labelTournamentEnd_2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(762, 784);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelTournamentEnd = new QLabel(centralWidget);
        labelTournamentEnd->setObjectName(QStringLiteral("labelTournamentEnd"));

        gridLayout->addWidget(labelTournamentEnd, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabMannschaftenZeitplanung = new QWidget();
        tabMannschaftenZeitplanung->setObjectName(QStringLiteral("tabMannschaftenZeitplanung"));
        gridLayout_22 = new QGridLayout(tabMannschaftenZeitplanung);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_zwischenrunde_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_zwischenrunde_2->setObjectName(QStringLiteral("groupBox_zwischenrunde_2"));
        gridLayout_23 = new QGridLayout(groupBox_zwischenrunde_2);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        label_satz_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_satz_zw_2->setObjectName(QStringLiteral("label_satz_zw_2"));

        gridLayout_23->addWidget(label_satz_zw_2, 0, 0, 1, 1);

        spinBoxSatzZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxSatzZw->setObjectName(QStringLiteral("spinBoxSatzZw"));
        spinBoxSatzZw->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzZw->setMinimum(1);

        gridLayout_23->addWidget(spinBoxSatzZw, 0, 1, 1, 1);

        label_min_pro_satz_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_min_pro_satz_zw_2->setObjectName(QStringLiteral("label_min_pro_satz_zw_2"));

        gridLayout_23->addWidget(label_min_pro_satz_zw_2, 1, 0, 1, 1);

        spinBoxMinProSatzZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxMinProSatzZw->setObjectName(QStringLiteral("spinBoxMinProSatzZw"));
        spinBoxMinProSatzZw->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzZw->setMinimum(1);

        gridLayout_23->addWidget(spinBoxMinProSatzZw, 1, 1, 1, 1);

        label_pause_min_zw_2 = new QLabel(groupBox_zwischenrunde_2);
        label_pause_min_zw_2->setObjectName(QStringLiteral("label_pause_min_zw_2"));

        gridLayout_23->addWidget(label_pause_min_zw_2, 2, 0, 1, 1);

        spinBoxPauseMinZw = new QSpinBox(groupBox_zwischenrunde_2);
        spinBoxPauseMinZw->setObjectName(QStringLiteral("spinBoxPauseMinZw"));
        spinBoxPauseMinZw->setMaximumSize(QSize(50, 16777215));

        gridLayout_23->addWidget(spinBoxPauseMinZw, 2, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_zwischenrunde_2, 0, 1, 1, 1);

        groupBox_vorrunde_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_vorrunde_2->setObjectName(QStringLiteral("groupBox_vorrunde_2"));
        gridLayout_24 = new QGridLayout(groupBox_vorrunde_2);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        label_satz_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_satz_vr_2->setObjectName(QStringLiteral("label_satz_vr_2"));

        gridLayout_24->addWidget(label_satz_vr_2, 0, 0, 1, 1);

        spinBoxSatzVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxSatzVr->setObjectName(QStringLiteral("spinBoxSatzVr"));
        spinBoxSatzVr->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzVr->setMinimum(1);

        gridLayout_24->addWidget(spinBoxSatzVr, 0, 1, 1, 1);

        label_min_pro_satz_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_min_pro_satz_vr_2->setObjectName(QStringLiteral("label_min_pro_satz_vr_2"));

        gridLayout_24->addWidget(label_min_pro_satz_vr_2, 1, 0, 1, 1);

        spinBoxMinProSatzVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxMinProSatzVr->setObjectName(QStringLiteral("spinBoxMinProSatzVr"));
        spinBoxMinProSatzVr->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzVr->setMinimum(1);

        gridLayout_24->addWidget(spinBoxMinProSatzVr, 1, 1, 1, 1);

        label_pause_min_vr_2 = new QLabel(groupBox_vorrunde_2);
        label_pause_min_vr_2->setObjectName(QStringLiteral("label_pause_min_vr_2"));

        gridLayout_24->addWidget(label_pause_min_vr_2, 2, 0, 1, 1);

        spinBoxPauseMinVr = new QSpinBox(groupBox_vorrunde_2);
        spinBoxPauseMinVr->setObjectName(QStringLiteral("spinBoxPauseMinVr"));
        spinBoxPauseMinVr->setMaximumSize(QSize(50, 16777215));

        gridLayout_24->addWidget(spinBoxPauseMinVr, 2, 1, 1, 1);


        gridLayout_10->addWidget(groupBox_vorrunde_2, 0, 0, 1, 1);


        gridLayout_22->addLayout(gridLayout_10, 1, 0, 1, 1);

        gridLayout_25 = new QGridLayout();
        gridLayout_25->setSpacing(6);
        gridLayout_25->setObjectName(QStringLiteral("gridLayout_25"));
        groupBox_turnier_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_turnier_2->setObjectName(QStringLiteral("groupBox_turnier_2"));
        gridLayout_26 = new QGridLayout(groupBox_turnier_2);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QStringLiteral("gridLayout_26"));
        label_pause_vr_zw_2 = new QLabel(groupBox_turnier_2);
        label_pause_vr_zw_2->setObjectName(QStringLiteral("label_pause_vr_zw_2"));

        gridLayout_26->addWidget(label_pause_vr_zw_2, 1, 0, 1, 1);

        label_turnierstart_2 = new QLabel(groupBox_turnier_2);
        label_turnierstart_2->setObjectName(QStringLiteral("label_turnierstart_2"));

        gridLayout_26->addWidget(label_turnierstart_2, 0, 0, 1, 1);

        label_pause_zw_kr_3 = new QLabel(groupBox_turnier_2);
        label_pause_zw_kr_3->setObjectName(QStringLiteral("label_pause_zw_kr_3"));

        gridLayout_26->addWidget(label_pause_zw_kr_3, 2, 0, 1, 1);

        spinBoxPauseZwKr = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseZwKr->setObjectName(QStringLiteral("spinBoxPauseZwKr"));
        spinBoxPauseZwKr->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseZwKr, 2, 2, 1, 1);

        label_pause_kr_pl_3 = new QLabel(groupBox_turnier_2);
        label_pause_kr_pl_3->setObjectName(QStringLiteral("label_pause_kr_pl_3"));

        gridLayout_26->addWidget(label_pause_kr_pl_3, 3, 0, 1, 1);

        spinBoxPauseVrZw = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseVrZw->setObjectName(QStringLiteral("spinBoxPauseVrZw"));
        spinBoxPauseVrZw->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseVrZw, 1, 2, 1, 1);

        spinBoxPauseKrPl = new QSpinBox(groupBox_turnier_2);
        spinBoxPauseKrPl->setObjectName(QStringLiteral("spinBoxPauseKrPl"));
        spinBoxPauseKrPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_26->addWidget(spinBoxPauseKrPl, 3, 2, 1, 1);

        timeEditStartTurnier = new QTimeEdit(groupBox_turnier_2);
        timeEditStartTurnier->setObjectName(QStringLiteral("timeEditStartTurnier"));

        gridLayout_26->addWidget(timeEditStartTurnier, 0, 2, 1, 1);


        gridLayout_25->addWidget(groupBox_turnier_2, 0, 0, 1, 1);

        groupBox_konfiguration_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_konfiguration_2->setObjectName(QStringLiteral("groupBox_konfiguration_2"));
        gridLayout_27 = new QGridLayout(groupBox_konfiguration_2);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QStringLiteral("gridLayout_27"));
        tableViewFields = new QTableView(groupBox_konfiguration_2);
        tableViewFields->setObjectName(QStringLiteral("tableViewFields"));
        tableViewFields->setAlternatingRowColors(true);
        tableViewFields->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewFields->horizontalHeader()->setStretchLastSection(true);
        tableViewFields->verticalHeader()->setVisible(false);
        tableViewFields->verticalHeader()->setStretchLastSection(true);

        gridLayout_27->addWidget(tableViewFields, 0, 0, 5, 1);

        gridLayout_28 = new QGridLayout();
        gridLayout_28->setSpacing(6);
        gridLayout_28->setObjectName(QStringLiteral("gridLayout_28"));
        label_anzahl_felder_2 = new QLabel(groupBox_konfiguration_2);
        label_anzahl_felder_2->setObjectName(QStringLiteral("label_anzahl_felder_2"));

        gridLayout_28->addWidget(label_anzahl_felder_2, 0, 0, 1, 1);

        spinBoxAnzahlfelder = new QSpinBox(groupBox_konfiguration_2);
        spinBoxAnzahlfelder->setObjectName(QStringLiteral("spinBoxAnzahlfelder"));
        spinBoxAnzahlfelder->setMaximumSize(QSize(50, 16777215));
        spinBoxAnzahlfelder->setMinimum(1);

        gridLayout_28->addWidget(spinBoxAnzahlfelder, 0, 1, 1, 1);


        gridLayout_27->addLayout(gridLayout_28, 0, 1, 1, 1);

        checkBoxKreuzspiele = new QCheckBox(groupBox_konfiguration_2);
        checkBoxKreuzspiele->setObjectName(QStringLiteral("checkBoxKreuzspiele"));

        gridLayout_27->addWidget(checkBoxKreuzspiele, 1, 1, 1, 1);

        pushButtonConfigSave = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigSave->setObjectName(QStringLiteral("pushButtonConfigSave"));

        gridLayout_27->addWidget(pushButtonConfigSave, 2, 1, 1, 1);

        pushButtonConfigRollback = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigRollback->setObjectName(QStringLiteral("pushButtonConfigRollback"));

        gridLayout_27->addWidget(pushButtonConfigRollback, 3, 1, 1, 1);

        pushButtonConfigReset = new QPushButton(groupBox_konfiguration_2);
        pushButtonConfigReset->setObjectName(QStringLiteral("pushButtonConfigReset"));

        gridLayout_27->addWidget(pushButtonConfigReset, 4, 1, 1, 1);


        gridLayout_25->addWidget(groupBox_konfiguration_2, 0, 1, 1, 1);


        gridLayout_22->addLayout(gridLayout_25, 0, 0, 1, 1);

        groupBox_mannschaften_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_mannschaften_2->setObjectName(QStringLiteral("groupBox_mannschaften_2"));
        groupBox_mannschaften_2->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_29 = new QGridLayout(groupBox_mannschaften_2);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QStringLiteral("gridLayout_29"));
        pushButtonResetTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonResetTeams->setObjectName(QStringLiteral("pushButtonResetTeams"));

        gridLayout_29->addWidget(pushButtonResetTeams, 0, 1, 1, 1);

        pushButtonSaveTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonSaveTeams->setObjectName(QStringLiteral("pushButtonSaveTeams"));

        gridLayout_29->addWidget(pushButtonSaveTeams, 0, 0, 1, 1);

        pushButtonPrintTeams = new QPushButton(groupBox_mannschaften_2);
        pushButtonPrintTeams->setObjectName(QStringLiteral("pushButtonPrintTeams"));

        gridLayout_29->addWidget(pushButtonPrintTeams, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_29->addItem(horizontalSpacer_6, 0, 3, 1, 1);

        tableViewTeams = new QTableView(groupBox_mannschaften_2);
        tableViewTeams->setObjectName(QStringLiteral("tableViewTeams"));
        tableViewTeams->setMinimumSize(QSize(0, 0));
        tableViewTeams->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableViewTeams->setAlternatingRowColors(true);
        tableViewTeams->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewTeams->horizontalHeader()->setStretchLastSection(true);
        tableViewTeams->verticalHeader()->setVisible(false);
        tableViewTeams->verticalHeader()->setStretchLastSection(true);

        gridLayout_29->addWidget(tableViewTeams, 1, 0, 1, 4);


        gridLayout_22->addWidget(groupBox_mannschaften_2, 3, 0, 1, 1);

        gridLayout_30 = new QGridLayout();
        gridLayout_30->setSpacing(6);
        gridLayout_30->setObjectName(QStringLiteral("gridLayout_30"));
        groupBox_platzspiele_finale_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_platzspiele_finale_2->setObjectName(QStringLiteral("groupBox_platzspiele_finale_2"));
        gridLayout_31 = new QGridLayout(groupBox_platzspiele_finale_2);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QStringLiteral("gridLayout_31"));
        label_pause_zw_kr_4 = new QLabel(groupBox_platzspiele_finale_2);
        label_pause_zw_kr_4->setObjectName(QStringLiteral("label_pause_zw_kr_4"));

        gridLayout_31->addWidget(label_pause_zw_kr_4, 1, 0, 1, 1);

        spinBoxMinProSatzPl = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxMinProSatzPl->setObjectName(QStringLiteral("spinBoxMinProSatzPl"));
        spinBoxMinProSatzPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxMinProSatzPl, 1, 1, 1, 1);

        spinBoxSatzPl = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxSatzPl->setObjectName(QStringLiteral("spinBoxSatzPl"));
        spinBoxSatzPl->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxSatzPl, 0, 1, 1, 1);

        label_satz_pl_2 = new QLabel(groupBox_platzspiele_finale_2);
        label_satz_pl_2->setObjectName(QStringLiteral("label_satz_pl_2"));

        gridLayout_31->addWidget(label_satz_pl_2, 0, 0, 1, 1);

        spinBoxZeitFinale = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxZeitFinale->setObjectName(QStringLiteral("spinBoxZeitFinale"));
        spinBoxZeitFinale->setMaximumSize(QSize(50, 16777215));

        gridLayout_31->addWidget(spinBoxZeitFinale, 2, 1, 1, 1);

        label_pause_kr_pl_4 = new QLabel(groupBox_platzspiele_finale_2);
        label_pause_kr_pl_4->setObjectName(QStringLiteral("label_pause_kr_pl_4"));

        gridLayout_31->addWidget(label_pause_kr_pl_4, 2, 0, 1, 1);

        label_zeit_pause_nach_finale_siegerehrung_2 = new QLabel(groupBox_platzspiele_finale_2);
        label_zeit_pause_nach_finale_siegerehrung_2->setObjectName(QStringLiteral("label_zeit_pause_nach_finale_siegerehrung_2"));

        gridLayout_31->addWidget(label_zeit_pause_nach_finale_siegerehrung_2, 4, 0, 1, 1);

        spinBoxPausePlEhrung = new QSpinBox(groupBox_platzspiele_finale_2);
        spinBoxPausePlEhrung->setObjectName(QStringLiteral("spinBoxPausePlEhrung"));
        spinBoxPausePlEhrung->setMaximum(999);

        gridLayout_31->addWidget(spinBoxPausePlEhrung, 4, 1, 1, 1);


        gridLayout_30->addWidget(groupBox_platzspiele_finale_2, 0, 1, 1, 1);

        groupBox_kreuzspiele_2 = new QGroupBox(tabMannschaftenZeitplanung);
        groupBox_kreuzspiele_2->setObjectName(QStringLiteral("groupBox_kreuzspiele_2"));
        gridLayout_32 = new QGridLayout(groupBox_kreuzspiele_2);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QStringLiteral("gridLayout_32"));
        label_satz_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_satz_kr_2->setObjectName(QStringLiteral("label_satz_kr_2"));

        gridLayout_32->addWidget(label_satz_kr_2, 0, 0, 1, 1);

        label_min_pro_satz_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_min_pro_satz_kr_2->setObjectName(QStringLiteral("label_min_pro_satz_kr_2"));

        gridLayout_32->addWidget(label_min_pro_satz_kr_2, 1, 0, 1, 1);

        spinBoxMinProSatzKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxMinProSatzKr->setObjectName(QStringLiteral("spinBoxMinProSatzKr"));
        spinBoxMinProSatzKr->setMaximumSize(QSize(50, 16777215));
        spinBoxMinProSatzKr->setMinimum(1);

        gridLayout_32->addWidget(spinBoxMinProSatzKr, 1, 1, 1, 1);

        spinBoxPauseMinKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxPauseMinKr->setObjectName(QStringLiteral("spinBoxPauseMinKr"));
        spinBoxPauseMinKr->setMaximumSize(QSize(50, 16777215));

        gridLayout_32->addWidget(spinBoxPauseMinKr, 2, 1, 1, 1);

        spinBoxSatzKr = new QSpinBox(groupBox_kreuzspiele_2);
        spinBoxSatzKr->setObjectName(QStringLiteral("spinBoxSatzKr"));
        spinBoxSatzKr->setMaximumSize(QSize(50, 16777215));
        spinBoxSatzKr->setMinimum(1);

        gridLayout_32->addWidget(spinBoxSatzKr, 0, 1, 1, 1);

        label_pause_min_kr_2 = new QLabel(groupBox_kreuzspiele_2);
        label_pause_min_kr_2->setObjectName(QStringLiteral("label_pause_min_kr_2"));

        gridLayout_32->addWidget(label_pause_min_kr_2, 2, 0, 1, 1);


        gridLayout_30->addWidget(groupBox_kreuzspiele_2, 0, 0, 1, 1);


        gridLayout_22->addLayout(gridLayout_30, 2, 0, 1, 1);

        tabWidget->addTab(tabMannschaftenZeitplanung, QString());
        tab_vorrunde_2 = new QWidget();
        tab_vorrunde_2->setObjectName(QStringLiteral("tab_vorrunde_2"));
        gridLayout_33 = new QGridLayout(tab_vorrunde_2);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QStringLiteral("gridLayout_33"));
        gridLayout_34 = new QGridLayout();
        gridLayout_34->setSpacing(6);
        gridLayout_34->setObjectName(QStringLiteral("gridLayout_34"));
        pushButtonVrClear = new QPushButton(tab_vorrunde_2);
        pushButtonVrClear->setObjectName(QStringLiteral("pushButtonVrClear"));

        gridLayout_34->addWidget(pushButtonVrClear, 0, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_7, 0, 7, 1, 1);

        pushButtonVrGenerate = new QPushButton(tab_vorrunde_2);
        pushButtonVrGenerate->setObjectName(QStringLiteral("pushButtonVrGenerate"));

        gridLayout_34->addWidget(pushButtonVrGenerate, 0, 0, 1, 1);

        pushButtonVrChangeGames = new QPushButton(tab_vorrunde_2);
        pushButtonVrChangeGames->setObjectName(QStringLiteral("pushButtonVrChangeGames"));

        gridLayout_34->addWidget(pushButtonVrChangeGames, 0, 4, 1, 1);

        pushButtonVrResult = new QPushButton(tab_vorrunde_2);
        pushButtonVrResult->setObjectName(QStringLiteral("pushButtonVrResult"));

        gridLayout_34->addWidget(pushButtonVrResult, 0, 8, 1, 1);

        pushButtonVrPrint = new QPushButton(tab_vorrunde_2);
        pushButtonVrPrint->setObjectName(QStringLiteral("pushButtonVrPrint"));

        gridLayout_34->addWidget(pushButtonVrPrint, 0, 5, 1, 1);

        pushButtonVrSave = new QPushButton(tab_vorrunde_2);
        pushButtonVrSave->setObjectName(QStringLiteral("pushButtonVrSave"));

        gridLayout_34->addWidget(pushButtonVrSave, 0, 1, 1, 1);


        gridLayout_33->addLayout(gridLayout_34, 0, 0, 1, 1);

        tableViewVorrunde = new QTableView(tab_vorrunde_2);
        tableViewVorrunde->setObjectName(QStringLiteral("tableViewVorrunde"));
        tableViewVorrunde->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewVorrunde->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewVorrunde->horizontalHeader()->setStretchLastSection(true);
        tableViewVorrunde->verticalHeader()->setVisible(false);

        gridLayout_33->addWidget(tableViewVorrunde, 1, 0, 1, 1);

        tabWidget->addTab(tab_vorrunde_2, QString());
        tab_zwischenrunde_2 = new QWidget();
        tab_zwischenrunde_2->setObjectName(QStringLiteral("tab_zwischenrunde_2"));
        gridLayout_35 = new QGridLayout(tab_zwischenrunde_2);
        gridLayout_35->setSpacing(6);
        gridLayout_35->setContentsMargins(11, 11, 11, 11);
        gridLayout_35->setObjectName(QStringLiteral("gridLayout_35"));
        gridLayout_36 = new QGridLayout();
        gridLayout_36->setSpacing(6);
        gridLayout_36->setObjectName(QStringLiteral("gridLayout_36"));
        pushButtonZwResult = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwResult->setObjectName(QStringLiteral("pushButtonZwResult"));

        gridLayout_36->addWidget(pushButtonZwResult, 0, 6, 1, 1);

        pushButtonZwGenerate = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwGenerate->setObjectName(QStringLiteral("pushButtonZwGenerate"));

        gridLayout_36->addWidget(pushButtonZwGenerate, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_36->addItem(horizontalSpacer_8, 0, 5, 1, 1);

        pushButtonZwSave = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwSave->setObjectName(QStringLiteral("pushButtonZwSave"));

        gridLayout_36->addWidget(pushButtonZwSave, 0, 1, 1, 1);

        pushButtonZwClear = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwClear->setObjectName(QStringLiteral("pushButtonZwClear"));

        gridLayout_36->addWidget(pushButtonZwClear, 0, 2, 1, 1);

        pushButtonZwChangeGames = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwChangeGames->setObjectName(QStringLiteral("pushButtonZwChangeGames"));

        gridLayout_36->addWidget(pushButtonZwChangeGames, 0, 3, 1, 1);

        pushButtonZwPrint = new QPushButton(tab_zwischenrunde_2);
        pushButtonZwPrint->setObjectName(QStringLiteral("pushButtonZwPrint"));

        gridLayout_36->addWidget(pushButtonZwPrint, 0, 4, 1, 1);


        gridLayout_35->addLayout(gridLayout_36, 0, 0, 1, 1);

        tableViewZwischenrunde = new QTableView(tab_zwischenrunde_2);
        tableViewZwischenrunde->setObjectName(QStringLiteral("tableViewZwischenrunde"));
        tableViewZwischenrunde->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewZwischenrunde->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewZwischenrunde->horizontalHeader()->setStretchLastSection(true);
        tableViewZwischenrunde->verticalHeader()->setVisible(false);

        gridLayout_35->addWidget(tableViewZwischenrunde, 1, 0, 1, 1);

        tabWidget->addTab(tab_zwischenrunde_2, QString());
        tab_kreuzspiele_2 = new QWidget();
        tab_kreuzspiele_2->setObjectName(QStringLiteral("tab_kreuzspiele_2"));
        gridLayout_37 = new QGridLayout(tab_kreuzspiele_2);
        gridLayout_37->setSpacing(6);
        gridLayout_37->setContentsMargins(11, 11, 11, 11);
        gridLayout_37->setObjectName(QStringLiteral("gridLayout_37"));
        gridLayout_38 = new QGridLayout();
        gridLayout_38->setSpacing(6);
        gridLayout_38->setObjectName(QStringLiteral("gridLayout_38"));
        pushButtonKrClear = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrClear->setObjectName(QStringLiteral("pushButtonKrClear"));

        gridLayout_38->addWidget(pushButtonKrClear, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_38->addItem(horizontalSpacer_9, 0, 4, 1, 1);

        pushButtonKrSave = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrSave->setObjectName(QStringLiteral("pushButtonKrSave"));

        gridLayout_38->addWidget(pushButtonKrSave, 0, 1, 1, 1);

        pushButtonKrGenerate = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrGenerate->setObjectName(QStringLiteral("pushButtonKrGenerate"));

        gridLayout_38->addWidget(pushButtonKrGenerate, 0, 0, 1, 1);

        pushButtonKrPrint = new QPushButton(tab_kreuzspiele_2);
        pushButtonKrPrint->setObjectName(QStringLiteral("pushButtonKrPrint"));

        gridLayout_38->addWidget(pushButtonKrPrint, 0, 3, 1, 1);


        gridLayout_37->addLayout(gridLayout_38, 0, 0, 1, 1);

        tableViewKreuzspiele = new QTableView(tab_kreuzspiele_2);
        tableViewKreuzspiele->setObjectName(QStringLiteral("tableViewKreuzspiele"));
        tableViewKreuzspiele->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewKreuzspiele->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewKreuzspiele->horizontalHeader()->setStretchLastSection(true);
        tableViewKreuzspiele->verticalHeader()->setVisible(false);

        gridLayout_37->addWidget(tableViewKreuzspiele, 1, 0, 1, 1);

        tabWidget->addTab(tab_kreuzspiele_2, QString());
        tab_platzspiele_2 = new QWidget();
        tab_platzspiele_2->setObjectName(QStringLiteral("tab_platzspiele_2"));
        gridLayout_39 = new QGridLayout(tab_platzspiele_2);
        gridLayout_39->setSpacing(6);
        gridLayout_39->setContentsMargins(11, 11, 11, 11);
        gridLayout_39->setObjectName(QStringLiteral("gridLayout_39"));
        gridLayout_40 = new QGridLayout();
        gridLayout_40->setSpacing(6);
        gridLayout_40->setObjectName(QStringLiteral("gridLayout_40"));
        pushButtonPlClear = new QPushButton(tab_platzspiele_2);
        pushButtonPlClear->setObjectName(QStringLiteral("pushButtonPlClear"));

        gridLayout_40->addWidget(pushButtonPlClear, 0, 2, 1, 1);

        pushButtonPlResult = new QPushButton(tab_platzspiele_2);
        pushButtonPlResult->setObjectName(QStringLiteral("pushButtonPlResult"));

        gridLayout_40->addWidget(pushButtonPlResult, 0, 5, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_40->addItem(horizontalSpacer_10, 0, 4, 1, 1);

        pushButtonPlGenerate = new QPushButton(tab_platzspiele_2);
        pushButtonPlGenerate->setObjectName(QStringLiteral("pushButtonPlGenerate"));

        gridLayout_40->addWidget(pushButtonPlGenerate, 0, 0, 1, 1);

        pushButtonPlSave = new QPushButton(tab_platzspiele_2);
        pushButtonPlSave->setObjectName(QStringLiteral("pushButtonPlSave"));

        gridLayout_40->addWidget(pushButtonPlSave, 0, 1, 1, 1);

        pushButtonPlPrint = new QPushButton(tab_platzspiele_2);
        pushButtonPlPrint->setObjectName(QStringLiteral("pushButtonPlPrint"));

        gridLayout_40->addWidget(pushButtonPlPrint, 0, 3, 1, 1);


        gridLayout_39->addLayout(gridLayout_40, 0, 0, 1, 1);

        tableViewPlatzspiele = new QTableView(tab_platzspiele_2);
        tableViewPlatzspiele->setObjectName(QStringLiteral("tableViewPlatzspiele"));
        tableViewPlatzspiele->setEditTriggers(QAbstractItemView::AnyKeyPressed|QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tableViewPlatzspiele->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableViewPlatzspiele->horizontalHeader()->setStretchLastSection(true);
        tableViewPlatzspiele->verticalHeader()->setVisible(false);

        gridLayout_39->addWidget(tableViewPlatzspiele, 1, 0, 1, 1);

        tabWidget->addTab(tab_platzspiele_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(357, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        pushButtonShowAllResultsWindow = new QPushButton(centralWidget);
        pushButtonShowAllResultsWindow->setObjectName(QStringLiteral("pushButtonShowAllResultsWindow"));

        gridLayout->addWidget(pushButtonShowAllResultsWindow, 1, 3, 1, 1);

        labelTournamentEnd_2 = new QLabel(centralWidget);
        labelTournamentEnd_2->setObjectName(QStringLiteral("labelTournamentEnd_2"));
        labelTournamentEnd_2->setMinimumSize(QSize(100, 0));

        gridLayout->addWidget(labelTournamentEnd_2, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 762, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        labelTournamentEnd->setText(QApplication::translate("MainWindow", "vorausberechnetes Turnierende", 0));
        groupBox_zwischenrunde_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Zwischenrunde", 0));
        label_satz_zw_2->setText(QApplication::translate("MainWindow", "S\303\244tze", 0));
        label_min_pro_satz_zw_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", 0));
        label_pause_min_zw_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", 0));
        groupBox_vorrunde_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Vorrunde", 0));
        label_satz_vr_2->setText(QApplication::translate("MainWindow", "S\303\244tze", 0));
        label_min_pro_satz_vr_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", 0));
        label_pause_min_vr_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", 0));
        groupBox_turnier_2->setTitle(QApplication::translate("MainWindow", "Turnierstart und Pausenzeit", 0));
        label_pause_vr_zw_2->setText(QApplication::translate("MainWindow", "Pause zw. Vor- und Zwischenrunde", 0));
        label_turnierstart_2->setText(QApplication::translate("MainWindow", "Start Turnier (hh:mm)", 0));
        label_pause_zw_kr_3->setText(QApplication::translate("MainWindow", "Pause zw. Zwischenrunde und Kreuzspiele", 0));
        label_pause_kr_pl_3->setText(QApplication::translate("MainWindow", "Pause zw. Kreuz- und Platzierungsspiele", 0));
        timeEditStartTurnier->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm", 0));
        groupBox_konfiguration_2->setTitle(QApplication::translate("MainWindow", "erweiterte Konfiguration", 0));
        label_anzahl_felder_2->setText(QApplication::translate("MainWindow", "Anzahl Spielfelder", 0));
        checkBoxKreuzspiele->setText(QApplication::translate("MainWindow", "Kreuzspiele", 0));
        pushButtonConfigSave->setText(QApplication::translate("MainWindow", "\303\204nderungen speichern", 0));
        pushButtonConfigRollback->setText(QApplication::translate("MainWindow", "\303\204nderungen verwerfen", 0));
        pushButtonConfigReset->setText(QApplication::translate("MainWindow", "Konfiguration zur\303\274cksetzen", 0));
        groupBox_mannschaften_2->setTitle(QApplication::translate("MainWindow", "Mannschaften", 0));
        pushButtonResetTeams->setText(QApplication::translate("MainWindow", "Mannschaften l\303\266schen", 0));
        pushButtonSaveTeams->setText(QApplication::translate("MainWindow", "Mannschaften speichern", 0));
        pushButtonPrintTeams->setText(QApplication::translate("MainWindow", "Mannschaften drucken", 0));
        groupBox_platzspiele_finale_2->setTitle(QApplication::translate("MainWindow", "Zeitplan Platzierungsspiele und Finale", 0));
        label_pause_zw_kr_4->setText(QApplication::translate("MainWindow", "gesch\303\244tzte Platzierungsspielzeit pro Satz (min)", 0));
        label_satz_pl_2->setText(QApplication::translate("MainWindow", "S\303\244tze", 0));
        label_pause_kr_pl_4->setText(QApplication::translate("MainWindow", "gesch\303\244tzte Spielzeit Finale (min)", 0));
        label_zeit_pause_nach_finale_siegerehrung_2->setText(QApplication::translate("MainWindow", "Zeit f\303\274r Pause nach Finale + Siegerehrung", 0));
        groupBox_kreuzspiele_2->setTitle(QApplication::translate("MainWindow", "Zeitplanung Kreuzspiele", 0));
        label_satz_kr_2->setText(QApplication::translate("MainWindow", "S\303\244tze", 0));
        label_min_pro_satz_kr_2->setText(QApplication::translate("MainWindow", "Minuten pro Satz", 0));
        label_pause_min_kr_2->setText(QApplication::translate("MainWindow", "Pause (min) zw. den Runden", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabMannschaftenZeitplanung), QApplication::translate("MainWindow", "Mannschaften/Zeitplanung", 0));
        pushButtonVrClear->setText(QApplication::translate("MainWindow", "L\303\266schen", 0));
        pushButtonVrGenerate->setText(QApplication::translate("MainWindow", "Generieren", 0));
        pushButtonVrChangeGames->setText(QApplication::translate("MainWindow", "Spiele tauschen", 0));
        pushButtonVrResult->setText(QApplication::translate("MainWindow", "Ergebnisse", 0));
        pushButtonVrPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", 0));
        pushButtonVrSave->setText(QApplication::translate("MainWindow", "Speichern", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_vorrunde_2), QApplication::translate("MainWindow", "Vorrunde", 0));
        pushButtonZwResult->setText(QApplication::translate("MainWindow", "Ergebnisse", 0));
        pushButtonZwGenerate->setText(QApplication::translate("MainWindow", "Generieren", 0));
        pushButtonZwSave->setText(QApplication::translate("MainWindow", "Speichern", 0));
        pushButtonZwClear->setText(QApplication::translate("MainWindow", "L\303\266schen", 0));
        pushButtonZwChangeGames->setText(QApplication::translate("MainWindow", "Spiele tauschen", 0));
        pushButtonZwPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_zwischenrunde_2), QApplication::translate("MainWindow", "Zwischenrunde", 0));
        pushButtonKrClear->setText(QApplication::translate("MainWindow", "L\303\266schen", 0));
        pushButtonKrSave->setText(QApplication::translate("MainWindow", "Speichern", 0));
        pushButtonKrGenerate->setText(QApplication::translate("MainWindow", "Generieren", 0));
        pushButtonKrPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_kreuzspiele_2), QApplication::translate("MainWindow", "Kreuzspiele", 0));
        pushButtonPlClear->setText(QApplication::translate("MainWindow", "L\303\266schen", 0));
        pushButtonPlResult->setText(QApplication::translate("MainWindow", "Ergebnisse", 0));
        pushButtonPlGenerate->setText(QApplication::translate("MainWindow", "Generieren", 0));
        pushButtonPlSave->setText(QApplication::translate("MainWindow", "Speichern", 0));
        pushButtonPlPrint->setText(QApplication::translate("MainWindow", "Spielberichte drucken", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_platzspiele_2), QApplication::translate("MainWindow", "Platzierungsspiele", 0));
        pushButtonShowAllResultsWindow->setText(QApplication::translate("MainWindow", "Spiele und Ergebnisse", 0));
        labelTournamentEnd_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
