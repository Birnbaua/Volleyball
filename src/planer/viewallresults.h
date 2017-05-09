#ifndef VIEWALLRESULTS_H
#define VIEWALLRESULTS_H

#include <QDialog>
#include <QTableView>
#include <QSqlTableModel>

namespace Ui {
class ViewAllResults;
}

class ViewAllResults : public QDialog
{
    Q_OBJECT

public:
    explicit ViewAllResults(QString windowTitle, QSqlTableModel *tm, QIcon appIcon, QWidget *parent = 0);
    ~ViewAllResults();

private:
    Ui::ViewAllResults *ui;
};

#endif // VIEWALLRESULTS_H
