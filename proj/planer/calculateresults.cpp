#include "calculateresults.h"

CalculateResults::CalculateResults(QObject *parent) : QObject(parent)
{

}

CalculateResults::~CalculateResults()
{

}

QList<CalculateResults::teamResult> CalculateResults::calculateSetResult(int team1Setpoints, int team2Setpoints)
{
    teamResult team1, team2;

    team1.sets = 0;
    team1.points = 0;
    team2.sets = 0;
    team2.points = 0;

    if(team1Setpoints > team2Setpoints) // first team wins
    {
        team1.sets = 2;
        team1.points = team1Setpoints - team2Setpoints;
        team2.points = team2Setpoints - team1Setpoints;
    }
    else if(team1Setpoints < team2Setpoints) // second team wins
    {
        team2.sets = 2;
        team2.points = team2Setpoints - team1Setpoints;
        team1.points = team1Setpoints - team2Setpoints;
    }
    else // draw game
    {
        team1.sets = 1;
        team2.sets = 1;
    }

    return QList<teamResult>() << team1 << team2;
}


QList<CalculateResults::teamResult> CalculateResults::calculateResults(QList<QStringList> *toCalculate)
{
    QList<teamResult> resultList;

    for(int i = 0; i < toCalculate->size(); i++)
    {
        QStringList rowToCalculate = toCalculate->at(i);
        teamResult m1, m2;

        m1.teamName = rowToCalculate.at(1);
        m1.sets = 0;
        m1.points = 0;

        m2.teamName = rowToCalculate.at(2);
        m2.sets = 0;
        m2.points = 0;

        for(int ii = 0, ix = 3; ii < 3; ii++)
        {
            if(rowToCalculate.at(ix).toInt() > 0 && rowToCalculate.at(ix + 1).toInt() > 0)
            {
                QList<teamResult> teamResultsSet = calculateSetResult(rowToCalculate.at(ix).toInt(), rowToCalculate.at(ix + 1).toInt());
                m1.sets += teamResultsSet.at(0).sets;
                m1.points += teamResultsSet.at(0).points;
                m2.sets += teamResultsSet.at(1).sets;
                m2.points += teamResultsSet.at(1).points;
            }

            ix += 2;
        }

        resultList << m1 << m2;
    }

    return resultList;
}

QList<CalculateResults::teamResult> CalculateResults::addResultsVrZw(QList<CalculateResults::teamResult> teamResults)
{
    QList<teamResult> calcTeamResults;

    while(teamResults.count() > 0)
    {
        teamResult result;
        result.teamName = teamResults.at(0).teamName;
        result.sets = 0;
        result.points = 0;

        for(int i = 0; i < teamResults.count();)
        {
            if(teamResults.at(i).teamName == result.teamName)
            {
                result.sets += teamResults.at(i).sets;
                result.points += teamResults.at(i).points;

                teamResults.removeAt(i);
            }
            else
            {
                i++;
            }
        }

        calcTeamResults << result;
    }

    return calcTeamResults;
}

QStringList CalculateResults::getResultsKrPl(QStringList rowToCalculate)
{
    teamResult m1, m2;
    QString spiel = rowToCalculate.at(0);

    m1.teamName = rowToCalculate.at(1);
    m1.sets = 0;
    m1.points = 0;

    m2.teamName = rowToCalculate.at(2);
    m2.sets = 0;
    m2.points = 0;

    for(int ii = 0, ix = 3; ii < 3; ii++)
    {
        if(rowToCalculate.at(ix).toInt() > 0 && rowToCalculate.at(ix + 1).toInt() > 0)
        {
            QList<teamResult> teamResultsSet = calculateSetResult(rowToCalculate.at(ix).toInt(), rowToCalculate.at(ix + 1).toInt());
            m1.sets += teamResultsSet.at(0).sets;
            m1.points += teamResultsSet.at(0).points;
            m2.sets += teamResultsSet.at(1).sets;
            m2.points += teamResultsSet.at(1).points;
        }

        ix += 2;
    }

    if(m1.sets > m2.sets)
    {
        return QStringList() << spiel << m1.teamName << m2.teamName;
    }
    else if(m1.sets < m2.sets)
    {
        return QStringList() << spiel << m2.teamName << m1.teamName;
    }
    else
    {
        if(m1.points > m2.points)
        {
            return QStringList() << spiel << m1.teamName << m2.teamName;
        }
        else if(m1.points < m2.points)
        {
            return QStringList() << spiel << m2.teamName << m1.teamName;
        }
        else
        {
            return QStringList() << spiel << m1.teamName << m2.teamName;
        }
    }
}
