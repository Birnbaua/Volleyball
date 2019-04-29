using System;
using System.Collections.Generic;

namespace Volleyball
{
    class InterimGames : BaseGameHandling
    {
        #region members
        Logging log;
        DateTime startRound;
        int setCounter;
        int minutesSet;
        int minutesPause;
        int fieldCount;
        int teamsCount;
        int lastGameNr;
        int lastRoundNr;
        bool useSecondGamePlaning;
        List<String> fieldNames;
        List<List<String>> divisionsList;
        List<int[]> gamePlan;
        #endregion

        public InterimGames(Logging log) : base(log)
        {
            this.log = log;
        }

        public void setParameters(List<List<String>> divisionsList, List< int[] > gamePlan, DateTime startRound, 
            int pauseBetweenQualifyingInterim, int setCounter, int minutesSet, int minutesPause,
            int fieldCount, int teamsCount, List<String> fieldNames, int lastRoundNr, int lastGameNr, bool useSecondGamePlaning)
        {
            this.startRound = startRound;
            this.setCounter = setCounter;
            this.minutesSet = minutesSet;
            this.minutesPause = minutesPause;
            this.fieldCount = fieldCount;
            this.teamsCount = teamsCount;
            this.fieldNames = fieldNames;
            this.lastGameNr = lastGameNr;
            this.lastRoundNr = lastRoundNr;
            this.useSecondGamePlaning = useSecondGamePlaning;

            setTimeParameters(setCounter, minutesSet, minutesPause);

            startRound = startRound.AddSeconds(pauseBetweenQualifyingInterim * 60);
        }

        public void generateGames()
        {
            // generate game plan over all divisonal games
            if (generateGamePlan())
            {
                insertGameNumber();

                insertRoundNumber(teamsCount, fieldCount);

                insertGameTime(startRound);

                insertFieldnumbersAndFieldnames(fieldCount, fieldNames);

                fillResultLists(divisionsList);
            }
            else
            {
                log.write("could not generate interim games!");
            }
        }

        bool generateGamePlan()
        {
            if (teamsCount % 5 == 0)
            {
                int gamesCount = 0;
                List<List<MatchData>> matchDataHelperList = new List<List<MatchData>>();

                foreach (List<String> divisionList in divisionsList)
                {
                    List<MatchData> matchDataList = new List<MatchData>();

                    foreach (int[] game in gamePlan)
                    {
                        MatchData newMatch = new MatchData();

                        newMatch.TeamA = divisionList[game[0]];
                        newMatch.TeamB = divisionList[game[1]];
                        newMatch.Referee = divisionList[game[2]];

                        matchDataList.Add(newMatch);
                        gamesCount++;
                    }

                    matchDataHelperList.Add(matchDataList);
                }

                for (int i = 1, ii = 0; i <= gamesCount;)
                {
                    foreach (List<MatchData> mdl in matchDataHelperList)
                    {
                        matchData.Add(mdl[ii]);
                        i++;
                    }

                    if (ii >= matchDataHelperList.Count)
                        ii = 0;
                    else
                        ii++;
                }

                return true;
            }

            return false;
        }

        // generate new divisions
        QList<QStringList> generateNewDivisions()
        {
            // help lists
            QList<QStringList> divisionsFirst, divisionsSecond, divisionsThird, divisionsFourth, divisionsFifth;
            QStringList divisionsFirstNames, divisionsSecondNames, divisionsThirdNames, divisionsFourthNames, divisionsFifthNames;

            // get list current ranking results
            QList<QList<QStringList>> resultDivisionsVr;

            // new list for new divisions by rank result
            QList<QStringList> newDivisionsZw;

            // read divisional rank results and add to list
            for (int i = 0; i < divisionCount; i++)
                resultDivisionsVr.append(dbRead("select ms, punkte, satz, intern, extern from vorrunde_erg_gr" + getPrefix(i) + " order by intern asc, punkte desc, satz desc"));

            divisionsFirst = getDivisionsClassement(&resultDivisionsVr, 1);
            divisionsSecond = getDivisionsClassement(&resultDivisionsVr, 2);
            divisionsThird = getDivisionsClassement(&resultDivisionsVr, 3);
            divisionsFourth = getDivisionsClassement(&resultDivisionsVr, 4);
            divisionsFifth = getDivisionsClassement(&resultDivisionsVr, 5);

            log.write("teams count = " + teamsCount + ", useSecondGamePlaning = " + useSecondGamePlaning);

            if (useSecondGamePlaning)
            {
                switch (teamsCount)
                {
                    case 20:
                        // make ranking of all divisions thrid teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 6)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsThirdNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsThirdNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(3)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3));
                        break;

                    case 25:
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        newDivisionsZw.append(divisionsFirstNames);
                        newDivisionsZw.append(divisionsSecondNames);
                        newDivisionsZw.append(divisionsThirdNames);
                        newDivisionsZw.append(divisionsFourthNames);
                        newDivisionsZw.append(divisionsFifthNames);
                        break;

                    case 28:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 6)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(5)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1));
                        break;

                    case 30:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 6)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(4)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(5)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsFourthNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(4)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(5));
                        break;

                    case 35:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 6)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsSecondNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(5)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(6)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(6)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFifthNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFifthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(6));
                        break;

                    case 40:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 5)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsSecondNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsSecondNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(6)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(7)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(6)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(6));
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(7));
                        break;

                    case 45:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 5)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsSecondNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4)
                                                << divisionsThirdNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7)
                                                << divisionsSecondNames.at(8)
                                                << divisionsThirdNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(8)
                                                << divisionsFourthNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(7)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(7)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8));
                        break;

                    case 50:
                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // create divisions with max 5 teams from helpList(can contain teams up to 5)
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsFirstNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7)
                                                << divisionsSecondNames.at(8)
                                                << divisionsSecondNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9));
                        break;

                    case 55:
                        // make ranking of all divisions second teams
                        sortList(&divisionsFirst);

                        if (checkListDoubleResults(&divisionsFirst))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(8));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(9));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(10)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(7)
                                                << divisionsSecondNames.at(8));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(7));

                        // hobby c
                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(10)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(9)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(6));

                        // hobby d
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(10));
                        break;

                    case 60:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsFirstNames.at(9));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(11)
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(8)
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsSecondNames.at(11)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(5));

                        // hobby c
                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(10)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(11)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3));

                        // hobby d
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFourthNames.at(11)
                                                << divisionsFifthNames.at(1));

                        // hobby e
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(10));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(11));

                        break;

                    default:
                        log.write("interim team count not correct");
                        break;
                }
            }
            else
            {
                switch (teamsCount)
                {
                    case 50:
                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsSecondNames.at(8)
                                                << divisionsSecondNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsFirstNames.at(9)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(3)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(6)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(9)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9));
                        break;

                    case 55:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(9)
                                                << divisionsFirstNames.at(10)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(8));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsFourthNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(10)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(5));

                        // hobby c
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(10));

                        break;

                    case 60:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(9)
                                                << divisionsFirstNames.at(10)
                                                << divisionsFirstNames.at(11)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(8)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsFourthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsFourthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(11)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(10)
                                                << divisionsThirdNames.at(11)
                                                << divisionsFourthNames.at(0));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(11)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(10)
                                                << divisionsFifthNames.at(11));
                        break;

                    default: logMessages("ZWISCHENRUNDE_ERROR:: team count not correct");
                }
            }

            return newDivisionsZw;
        }
    }
}
