#ifndef VIEWCLASSEMENTRESULTS_H
#define VIEWCLASSEMENTRESULTS_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class ViewClassementResults;
}

class ViewClassementResults : public QWidget
{
    Q_OBJECT

public:
    explicit ViewClassementResults(QString name = 0, QSqlTableModel *tm = 0, QWidget *parent = 0);
    ~ViewClassementResults();

private:
    Ui::ViewClassementResults *ui;
};

#endif // VIEWCLASSEMENTRESULTS_H
