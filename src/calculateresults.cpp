#include "calculateresults.h"

CalculateResults::CalculateResults(QObject *parent) : QObject(parent)
{

}

CalculateResults::~CalculateResults()
{

}

QList<CalculateResults::teamResult> CalculateResults::calculateResults(QList<QStringList> *toCalculate)
{
    QList<teamResult> resultList;

    for(int i = 0; i < toCalculate->size(); i++)
    {
        QStringList rowToCalculate = toCalculate->at(i);

        teamResult m1;
        teamResult m2;

        m1.teamName = rowToCalculate.at(1);
        m1.sets = 0;
        m1.points = 0;

        m2.teamName = rowToCalculate.at(2);
        m2.sets = 0;
        m2.points = 0;

        // first set
        if(rowToCalculate.at(3).toInt() > 0 && rowToCalculate.at(4).toInt() > 0) // 1ter satz
        {
            // first team wins
            if(rowToCalculate.at(3).toInt() > rowToCalculate.at(4).toInt())
            {
                m1.sets += 2;
                m1.points += rowToCalculate.at(3).toInt() - rowToCalculate.at(4).toInt();
                m2.points += rowToCalculate.at(4).toInt() - rowToCalculate.at(3).toInt();
            }
            // second team wins
            else if(rowToCalculate.at(3).toInt() < rowToCalculate.at(4).toInt())
            {
                m2.sets += 2;
                m2.points += rowToCalculate.at(4).toInt() - rowToCalculate.at(3).toInt();
                m1.points += rowToCalculate.at(3).toInt() - rowToCalculate.at(4).toInt();
            }
            // draw game
            else
            {
                m1.sets += 1;
                m2.sets += 1;
            }

            // second set
            if(rowToCalculate.at(5).toInt() > 0 && rowToCalculate.at(6).toInt() > 0) // 1ter satz
            {
                // first team wins
                if(rowToCalculate.at(5).toInt() > rowToCalculate.at(6).toInt())
                {
                    m1.sets += 2;
                    m1.points += rowToCalculate.at(5).toInt() - rowToCalculate.at(6).toInt();
                    m2.points += rowToCalculate.at(6).toInt() - rowToCalculate.at(5).toInt();
                }
                // second team wins
                else if(rowToCalculate.at(5).toInt() < rowToCalculate.at(6).toInt())
                {
                    m2.sets += 2;
                    m2.points += rowToCalculate.at(6).toInt() - rowToCalculate.at(5).toInt();
                    m1.points += rowToCalculate.at(5).toInt() - rowToCalculate.at(6).toInt();
                }
                // draw game
                else
                {
                    m1.sets += 1;
                    m2.sets += 1;
                }

                // third set
                if(rowToCalculate.at(7).toInt() > 0 && rowToCalculate.at(8).toInt() > 0) // 1ter satz
                {
                    // first team wins
                    if(rowToCalculate.at(7).toInt() > rowToCalculate.at(8).toInt())
                    {
                        m1.sets += 2;
                        m1.points += rowToCalculate.at(7).toInt() - rowToCalculate.at(8).toInt();
                        m2.points += rowToCalculate.at(8).toInt() - rowToCalculate.at(7).toInt();
                    }
                    // second team wins
                    else if(rowToCalculate.at(7).toInt() < rowToCalculate.at(8).toInt())
                    {
                        m2.sets += 2;
                        m2.points += rowToCalculate.at(8).toInt() - rowToCalculate.at(7).toInt();
                        m1.sets += rowToCalculate.at(7).toInt() - rowToCalculate.at(8).toInt();
                    }
                    // draw game
                    else
                    {
                        m1.sets += 1;
                        m2.sets += 1;
                    }
                }
            }
        }
        resultList << m1 << m2;
    }
    return resultList;
}

QList<CalculateResults::teamResult> CalculateResults::addResultsVrZw(QList<CalculateResults::teamResult> teamResults)
{
    QList<teamResult> calcTeamResults;

    foreach(teamResult tR, teamResults)
    {
        bool contains = false;
        foreach(teamResult cTR, calcTeamResults)
        {
            if(cTR.teamName == tR.teamName)
            {
                contains = true;
                break;
            }
        }

        if(!contains)
        {
            QList<teamResult> intermedResult;
            teamResult result;

            result.sets = 0;
            result.points = 0;

            foreach(teamResult cTR, teamResults)
            {
                if(cTR.teamName == tR.teamName)
                    intermedResult.append(cTR);
            }

            foreach(teamResult cTR, intermedResult)
            {
                result.teamName = cTR.teamName;
                result.sets += cTR.sets;
                result.points += cTR.points;
            }

            calcTeamResults << result;
        }
    }

    return calcTeamResults;
}

QStringList CalculateResults::getResultsKrPl(QStringList rowToCalculate)
{
    teamResult m1;
    teamResult m2;
    QString spiel = rowToCalculate.at(0);

    m1.teamName = rowToCalculate.at(1);
    m1.sets = 0;
    m1.points = 0;

    m2.teamName = rowToCalculate.at(2);
    m2.sets = 0;
    m2.points = 0;

    // first set
    if(rowToCalculate.at(3).toInt() > 0 && rowToCalculate.at(4).toInt() > 0) // 1ter satz
    {
        // first team wins
        if(rowToCalculate.at(3).toInt() > rowToCalculate.at(4).toInt())
        {
            m1.sets += 2;
            m1.points += rowToCalculate.at(3).toInt() - rowToCalculate.at(4).toInt();
            m2.points += rowToCalculate.at(4).toInt() - rowToCalculate.at(3).toInt();
        }
        // second team wins
        else if(rowToCalculate.at(3).toInt() < rowToCalculate.at(4).toInt())
        {
            m2.sets += 2;
            m2.points += rowToCalculate.at(4).toInt() - rowToCalculate.at(3).toInt();
            m1.points += rowToCalculate.at(3).toInt() - rowToCalculate.at(4).toInt();
        }
        // draw game
        else
        {
            m1.sets += 1;
            m2.sets += 1;
        }

        // second set
        if(rowToCalculate.at(5).toInt() > 0 && rowToCalculate.at(6).toInt() > 0) // 1ter satz
        {
            // first team wins
            if(rowToCalculate.at(5).toInt() > rowToCalculate.at(6).toInt())
            {
                m1.sets += 2;
                m1.points += rowToCalculate.at(5).toInt() - rowToCalculate.at(6).toInt();
                m2.points += rowToCalculate.at(6).toInt() - rowToCalculate.at(5).toInt();
            }
            // second team wins
            else if(rowToCalculate.at(5).toInt() < rowToCalculate.at(6).toInt())
            {
                m2.sets += 2;
                m2.points += rowToCalculate.at(6).toInt() - rowToCalculate.at(5).toInt();
                m1.points += rowToCalculate.at(5).toInt() - rowToCalculate.at(6).toInt();
            }
            // draw game
            else
            {
                m1.sets += 1;
                m2.sets += 1;
            }

            // third set
            if(rowToCalculate.at(7).toInt() > 0 && rowToCalculate.at(8).toInt() > 0) // 1ter satz
            {
                // first team wins
                if(rowToCalculate.at(7).toInt() > rowToCalculate.at(8).toInt())
                {
                    m1.sets += 2;
                    m1.points += rowToCalculate.at(7).toInt() - rowToCalculate.at(8).toInt();
                    m2.points += rowToCalculate.at(8).toInt() - rowToCalculate.at(7).toInt();
                }
                // second team wins
                else if(rowToCalculate.at(7).toInt() < rowToCalculate.at(8).toInt())
                {
                    m2.sets += 2;
                    m2.points += rowToCalculate.at(8).toInt() - rowToCalculate.at(7).toInt();
                    m1.sets += rowToCalculate.at(7).toInt() - rowToCalculate.at(8).toInt();
                }
                // draw game
                else
                {
                    m1.sets += 1;
                    m2.sets += 1;
                }
            }
        }
    }

    if(m1.sets > m2.sets)
        return QStringList() << spiel << m1.teamName << m2.teamName;
    else
        return QStringList() << spiel << m2.teamName << m1.teamName;
}
