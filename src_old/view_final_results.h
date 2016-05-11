#ifndef VIEW_FINAL_RESULTS_H
#define VIEW_FINAL_RESULTS_H

#include <QWidget>
#include <database_v1.3.h>

namespace Ui {
class view_final_results;
}

class view_final_results : public QWidget
{
    Q_OBJECT

public:
    explicit view_final_results(QWidget *parent = 0, database *m_Db = 0);
    ~view_final_results();

private:
    void init();

    Ui::view_final_results *ui;
    QSqlQueryModel *data;
    database *m_Db;
};

#endif // VIEW_FINAL_RESULTS_H
