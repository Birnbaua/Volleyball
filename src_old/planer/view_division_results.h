#ifndef VIEW_DIVISION_RESULTS_H
#define VIEW_DIVISION_RESULTS_H

#include <QWidget>
#include <QTableView>

#include "database_v1.3.h"

namespace Ui {
class view_division_results;
}

class view_division_results : public QWidget
{
    Q_OBJECT

public:
    explicit view_division_results(QWidget *parent = 0, database *m_Db = 0);
    ~view_division_results();

    // set table models to view results
    void init(QString tableName, QStringList grPrefix);

signals:
    // send log msg
    void viewdivisionresultsLog(QString);

private slots:

private:
    Ui::view_division_results *ui;

    QList<QTableView*> tableViews;
    database *m_Db;
    QStringList columnName;
};

#endif // VIEW_DIVISION_RESULTS_H
