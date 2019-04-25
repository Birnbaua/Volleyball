#ifndef CALCULATERESULTS_H
#define CALCULATERESULTS_H

#include <QObject>
#include <QStringList>

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

    explicit CalculateResults(QObject *parent = nullptr);
    ~CalculateResults();
    static QList<teamResult> calculateResults(QList<QStringList> *toCalculate);
    static QList<teamResult> addResultsVrZw(QList<teamResult> teamResults);
    static QStringList getResultsKrPl(QStringList rowToCalculate);

signals:

public slots:

private:
    static QList<CalculateResults::teamResult> calculateSetResult(int team1Setpoints, int team2Setpoints);
};

#endif // CALCULATERESULTS_H
