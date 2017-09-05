#ifndef VIEWDIVISIONS_H
#define VIEWDIVISIONS_H

#include <QDialog>
#include <QTableView>
#include <QSqlTableModel>

namespace Ui {
class ViewDivisions;
}

class ViewDivisions : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDivisions(QString windowTitle, QList<QSqlTableModel *> *tmList, QIcon appIcon, QWidget *parent = 0);
    ~ViewDivisions();

private:
    Ui::ViewDivisions *ui;

    QList<QTableView*> tvList;
};

#endif // VIEWDIVISIONS_H
