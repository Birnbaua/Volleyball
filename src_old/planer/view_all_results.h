#ifndef VIEW_ALL_RESULTS_H
#define VIEW_ALL_RESULTS_H

#include <QWidget>
#include <QTimer>
#include <QTableView>

#include "database_v1.3.h"
#include "itemdelegates_v1.2.h"
#include "view_division_results.h"

namespace Ui {
class view_all_results;
}

class view_all_results : public QWidget
{
    Q_OBJECT

public:
    explicit view_all_results(QWidget *parent = 0, database *m_Db = 0);
    ~view_all_results();

    void startUpdateUi(int seconds);
    void setgrPrefix(QStringList grPrefix);

private slots:
    void updateUi();

private:
    Ui::view_all_results *ui;

    int setCurrentRound();
    QSqlQueryModel* setTableView(int currentRound);

    QList<QTableView*> tableViews;
    database *m_Db;
    QTimer *refresh;
    QStringList grPrefix;
    int roundCount;
};

#endif // VIEW_ALL_RESULTS_H
