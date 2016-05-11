#include "logging.h"

Logging::Logging(QString filename, QObject *parent) : QObject(parent)
{
    file.setFileName(filename);

    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        out.setDevice(&file);
    }
}

Logging::~Logging()
{
    file.close();
}

void Logging::write(QString message)
{
    if(file.isOpen())
    {
        out << dt.currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") + " " << message << "\n";
        out.flush();
    }
    else
    {
        emit log("log file was not opened, can not write log!");
    }
}
