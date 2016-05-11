#ifndef CALCULATERESULTS_H
#define CALCULATERESULTS_H

#include <QObject>

class CalculateResults : public QObject
{
    Q_OBJECT
public:
    typedef struct
    {
        QString teamName;
        int sets;
        int points;
    } teamResult;

    explicit CalculateResults(QObject *parent = 0);
    ~CalculateResults();

    static QList<teamResult> calculateResults(QList<QStringList> *toCalculate);
    static QList<teamResult> addResultsVrZw(QList<teamResult> teamResults);
    static QStringList getResultsKrPl(QStringList rowToCalculate);

signals:

public slots:
};

#endif // CALCULATERESULTS_H
