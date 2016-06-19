#include "basegamehandling.h"

BaseGameHandling::BaseGameHandling(QObject *parent) : QObject(parent)
{

}

void BaseGameHandling::clearAllData(QStringList tables)
{
    QStringList querys;

    foreach(QString table, tables)
        querys << "DELETE FROM " + table;

    writeToDB(&querys);
}

// insert field numbers
QStringList BaseGameHandling::insertFieldNr(QString round, int gameCount, int fieldCount)
{
    QStringList querys;

    for (int i = 1, field = 1; i <= gameCount; i++)
    {
        for(int x = 1, fieldHelp = field; x <= fieldCount; x++, fieldHelp++, i++)
        {
            querys << "UPDATE " + round + " SET feldnummer = " + QString::number(fieldHelp) + " WHERE id = " + QString::number(i);
            if(fieldHelp >= fieldCount)
                fieldHelp = 0;
        }

        i--;

        if(field < fieldCount)
            field++;
        else
            field = 1;
    }

    return querys;
}

// insert field names
QStringList BaseGameHandling::insertFieldNames(QString round)
{
    QStringList querys;

    for(int i = 1; i <= fieldNames->count(); i++)
        querys << "UPDATE " + round + " SET feldname = '" + fieldNames->at(i-1) + "' WHERE feldnummer = " + QString::number(i);

    return querys;
}

// generate qualifying divisions result table
QStringList BaseGameHandling::generateResultTables(QString round, QList<QStringList> *divisionsList)
{
    QStringList querys;

    for(int i = 0, prefix = 0; i < divisionsList->size(); i++, prefix++)
    {
        QStringList division = divisionsList->at(i);
        QString group = grPrefix->at(prefix);

        for(int x = 0; x < division.size(); x++)
        {
            QString team = division.at(x);
            querys << "INSERT INTO " + round + group + " VALUES(" + QString::number(x) + ",'" + team + "',0,0,0,0)";
        }
    }

    return querys;
}

// write statements to database
void BaseGameHandling::writeToDB(QStringList *querys)
{
    for(int i = 0; i < querys->size(); i++)
        db->write(querys->at(i));
}
