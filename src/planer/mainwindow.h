#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QClipboard>
#include <QTimer>

#include "worker.h"
#include "itemdelegates.h"
#include "viewdivisionresults.h"
#include "viewclassementresults.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updateWorker(Worker::dataUi*);
    void log(QString);

private slots:
    void messageBoxCritical(QString msg);
    void messageBoxInformation(QString msg);
    void messageBoxWarning(QString msg);
    bool userCheckButton(QString msg, QString head);

    void updateUiData(Worker::dataUi *data);
    void updateWorkerData();

    void updateTournamentTime();
    void fieldsValueChanged();
    void on_spinBoxAnzahlfelder_valueChanged(int arg1);
    void on_pushButtonConfigSave_clicked();
    void on_pushButtonConfigRollback_clicked();
    void on_pushButtonConfigReset_clicked();
    void on_checkBoxActivateFTPUpload_clicked(bool checked);

    void on_pushButtonSaveTeams_clicked();
    void on_pushButtonResetTeams_clicked();
    void on_pushButtonPrintTeams_clicked();
    void teamsValueChanged();

    void on_pushButtonVrGenerate_clicked();
    void on_pushButtonVrClear_clicked();
    void on_pushButtonVrSave_clicked();
    void on_pushButtonVrChangeGames_clicked();
    void on_pushButtonVrPrint_clicked();
    void on_pushButtonVrResult_clicked();
    void copyVrTableView();
    void pasteVrTableView();
    void vrValueChanged();
    void vrValueChangedFinishEdit();

    void on_pushButtonZwGenerate_clicked();
    void on_pushButtonZwSave_clicked();
    void on_pushButtonZwClear_clicked();
    void on_pushButtonZwChangeGames_clicked();
    void on_pushButtonZwPrint_clicked();
    void on_pushButtonZwResult_clicked();
    void copyZwTableView();
    void pasteZwTableView();
    void zwValueChanged();
    void zwValueChangedFinishEdit();

    void on_pushButtonKrGenerate_clicked();
    void on_pushButtonKrSave_clicked();
    void on_pushButtonKrClear_clicked();
    //void on_pushButtonKrChangeGames_clicked();
    void on_pushButtonKrPrint_clicked();
    void copyKrTableView();
    void pasteKrTableView();
    void krValueChanged();
    void krValueChangedFinishEdit();

    void on_pushButtonPlGenerate_clicked();
    void on_pushButtonPlSave_clicked();
    void on_pushButtonPlClear_clicked();
    //void on_pushButtonPlChangeGames_clicked();
    void on_pushButtonPlPrint_clicked();
    void on_pushButtonPlResult_clicked();
    void copyPlTableView();
    void pastePLTableView();
    void plValueChanged();
    void plValueChangedFinishEdit();

private:
    void init();
    QList<QVariant> returnTime();
    void initTableViewFields();
    void initTableViewTeams();
    void hideTableViewColumns(int hideCol, QTableView *qtv);
    void initTableViewVorrunde(int hideCol);
    void initTableViewZwischenrunde(int hideCol);
    void initTableViewKreuzspiele(int hideCol);
    void setKreuzspieleParams();
    void initTableViewPlatzspiele(int hideCol);
    void copyEvent(QTableView *tv);
    void pasteEvent(QTableView *tv, QSqlTableModel *model);

    Ui::MainWindow *ui;
    Worker *worker;
    Worker::dataUi *data;
    QClipboard *clipboard;
    ViewDivisionResults *qfView, *imView;
    ViewClassementResults *clView;
    QList<QSqlTableModel*> viewQualifyingModels, viewIntermModels;
    QSqlTableModel *tmFields, *tmTeams, *tmVr, *tmZw, *tmKr, *tmPl, *tmPlatz, *viewClassementResults;
    ItemDelegates *idQualifyingGames, *idInterimGames, *idCrossGames, *idClassement;
    QStringList colTableViewFields, colTableViewTeams, colTableViewQualifying, colTalbeViewDivisionResults, colTableViewClassement, *grPrefix, *headerPrefix;
    bool msChanged, configChanged, vrChanged, zwChanged, krChanged, plChanged;
    QIcon windowIcon;
    QTimer *timerUpdateTournamentTime;
};

#endif // MAINWINDOW_H
