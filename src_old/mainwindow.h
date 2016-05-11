#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QClipboard>
#include <QTimer>

#include "database_v1.3.h"
#include "logging_v1.3.h"
#include "itemdelegates_v1.2.h"

#include "settings.h"
#include "vorrunde.h"
#include "zwischenrunde.h"
#include "kreuzspiele.h"
#include "platzspiele.h"
#include "view_division_results.h"
#include "view_all_results.h"
#include "view_final_results.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef struct
    {
        QString sysFilePath;
        QString pdfPath;
        int anzFelder;
        int krSpiele;
        QString startTurnier;
        int pauseVrZw;
        int pauseZwKr;
        int pauseKrPl;
        int satzVr;
        int minSatzVr;
        int pauseMinVr;
        int satzZw;
        int minSatzZw;
        int pauseMinZw;
        int satzKr;
        int minSatzKr;
        int pauseMinKr;
        int satzPl;
        int minSatzPl;
        int zeitFinale;
        int pausePlEhrung;
    } dataUi;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    // send settings data
    void updateSettings(dataUi);

    // send log msg
    void mainLog(QString);

private slots:
    void messageBoxCritical(QString msg);
    void messageBoxInformation(QString msg);
    void messageBoxWarning(QString msg);
    void updateTournamentTime();

    void copyVrTableView();
    void pasteVrTableView();
    void copyZwTableView();
    void pasteZwTableView();
    void copyKrTableView();
    void pasteKrTableView();
    void copyPlTableView();
    void pastePLTableView();

    void updateSettingsToUi(dataUi settings);
    void fieldsValueChanged();
    void teamsValueChanged();
    void vrValueChanged();
    void vrValueChangedFinishEdit();
    void zwValueChanged();
    void zwValueChangedFinishEdit();
    void krValueChanged();
    void krValueChangedFinishEdit();
    void plValueChanged();
    void plValueChangedFinishEdit();

    void on_spinBoxAnzahlfelder_valueChanged(int arg1);

    void on_pushButtonConfigSave_clicked();
    void on_pushButtonConfigRollback_clicked();
    void on_pushButtonConfigReset_clicked();

    void on_pushButtonSaveTeams_clicked();
    void on_pushButtonResetTeams_clicked();
    void on_pushButtonPrintTeams_clicked();

    void on_pushButtonVrGenerate_clicked();
    void on_pushButtonVrClear_clicked();
    void on_pushButtonVrSave_clicked();
    void on_pushButtonVrChangeGames_clicked();
    void on_pushButtonVrPrint_clicked();
    void on_pushButtonVrResult_clicked();

    void on_pushButtonZwGenerate_clicked();
    void on_pushButtonZwSave_clicked();
    void on_pushButtonZwClear_clicked();
    void on_pushButtonZwChangeGames_clicked();
    void on_pushButtonZwPrint_clicked();
    void on_pushButtonZwResult_clicked();

    void on_pushButtonKrGenerate_clicked();
    void on_pushButtonKrSave_clicked();
    void on_pushButtonKrClear_clicked();
    //void on_pushButtonKrChangeGames_clicked();
    void on_pushButtonKrPrint_clicked();

    void on_pushButtonPlGenerate_clicked();
    void on_pushButtonPlSave_clicked();
    void on_pushButtonPlClear_clicked();
    //void on_pushButtonPlChangeGames_clicked();
    void on_pushButtonPlPrint_clicked();
    void on_pushButtonPlResult_clicked();

    void on_pushButtonShowAllResultsWindow_clicked();

private:
    void endProgram();
    QList<QVariant> returnTime();
    void updateUiToSettings();
    void initTableViewFields();
    void initTableViewTeams();
    void initTableViewVorrunde(int hideCol);
    void setVorrundeParams();
    void initTableViewZwischenrunde(int hideCol);
    void setZwischenrundeParams();
    void initTableViewKreuzspiele(int hideCol);
    void setKreuzspieleParams();
    void initTableViewPlatzspiele(int hideCol);
    void setPlatzspieleParams();
    bool userCheckButton(QString msg, QString head);
    void copyEvent(QTableView *tv);
    void pasteEvent(QTableView *tv, QSqlTableModel *model);

    Ui::MainWindow *ui;
    QIcon windowIcon;

    database *m_Db;
    logging *m_Log;
    settings *m_Set;
    vorrunde *m_Vorrunde;
    zwischenrunde *m_Zwischenrunde;
    kreuzspiele *m_Kreuzspiele;
    platzspiele *m_Platzspiele;
    calculate *m_Calculate;
    view_division_results *m_VrResults, *m_ZwResults;
    view_all_results *m_VaR;
    view_final_results *m_VfR;
    itemdelegate *m_VrItemDelegate, *m_ZwItemDelegate, *m_KrItemDelegate, *m_PlItemDelegate;

    QClipboard *clipboard;
    QTimer *timerUpdateTournamentTime;
    dataUi m_DataSettings;
    QSqlTableModel *tmFields, *tmTeams, *tmVr, *tmZw, *tmKr, *tmPl, *tmPlatz;
    QStringList grPrefix, headerPrefix;
    QString sysFilePath, pdfPath, startTurnier;
    int fieldCount, msCount, spiel, runde;
    bool msChanged, configChanged, vrChanged, zwChanged, krChanged, plChanged;
};

#endif // MAINWINDOW_H
