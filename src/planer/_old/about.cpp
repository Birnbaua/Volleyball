#include "about.h"
#include "ui_about.h"

About::About(QString fileName, QString windowTitle, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextCursor txtcursor;
        QTextStream in(&file);
        QString text = "";

        while(!in.atEnd())
            text += in.readLine() + "\n";

        file.close();

        txtcursor.setPosition(0);
        ui->plainTextEditVersioninfo->appendPlainText(text);
        ui->plainTextEditVersioninfo->setTextCursor(txtcursor);
        ui->plainTextEditVersioninfo->setReadOnly(true);

        QStringList lineList = text.split("\n");
        foreach(QString line , lineList)
        {
            if(line.contains("###Version "))
            {
                vnr = line.right(2);
                break;
            }
        }

        this->setWindowTitle(windowTitle + vnr);
    }
}

About::~About()
{
    delete ui;
}

QString About::getVersionNr()
{
    return vnr;
}
