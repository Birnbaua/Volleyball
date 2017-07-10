#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QString fileName, QString windowTitle, QWidget *parent = 0);
    ~About();

    QString getVersionNr();

private:
    Ui::About *ui;

    QString vnr;
};

#endif // ABOUT_H
