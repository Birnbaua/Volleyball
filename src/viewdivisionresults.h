#ifndef VIEWDIVISIONRESULTS_H
#define VIEWDIVISIONRESULTS_H

#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>

namespace Ui {
class ViewDivisionResults;
}

class ViewDivisionResults : public QWidget
{
    Q_OBJECT

public:
    explicit ViewDivisionResults(QString name = 0, QList<QSqlTableModel *> *tmList = 0, QWidget *parent = 0);
    ~ViewDivisionResults();

private:
    Ui::ViewDivisionResults *ui;
    QList<QTableView*> tvList;
};

#endif // VIEWDIVISIONRESULTS_H
