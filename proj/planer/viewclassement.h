#ifndef VIEWCLASSEMENT_H
#define VIEWCLASSEMENT_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ViewClassement;
}

class ViewClassement : public QDialog
{
    Q_OBJECT

public:
    explicit ViewClassement(QString windowTitle, QSqlTableModel *tm, QIcon appIcon, QWidget *parent = 0);
    ~ViewClassement();

private:
    Ui::ViewClassement *ui;
};

#endif // VIEWCLASSEMENT_H
