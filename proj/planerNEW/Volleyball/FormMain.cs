using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using System.Data;
using System.Reflection;
using System.Drawing;
using System.Data.SQLite;
using OpenHtmlToPdf;
using System.Net;
using System.Threading.Tasks;

namespace Volleyball
{
    public partial class FormMain : Form
    {
        #region members
        static readonly string resourcePath = "./matchdata/";
        static readonly string htmlPath = "./htmltemplates/";
        static readonly string pdfPath = "./pdfs/";
        static readonly string settingsFileName = resourcePath + "settings.csv";
        static readonly string fieldsFileName = resourcePath + "fields.csv";
        static readonly string teamsFileName = resourcePath + "teams.csv";
        static readonly string qualifyingFileName = resourcePath + "qualifyinggames.csv", qualifyingResultFileName = resourcePath + "qualifying_result";
        static readonly string interimFileName = resourcePath + "interimgames.csv", interimResultFileName = resourcePath + "interim_results";
        static readonly string crossgamesFileName = resourcePath + "crossgames.csv";
        static readonly string classementgamesFileName = resourcePath + "classementgames.csv";
        static readonly List<String> prefix = new List<String>() { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
        static bool lockAction = false;
        static readonly List<Color> rowColors = new List<Color>() { Color.Yellow, Color.LightGray, Color.Cyan, Color.Magenta };
        static readonly string headerHtml = "<!DOCTYPE html><html><body>";
        static readonly string part1Html = File.ReadAllText(htmlPath + "part1Html.txt");
        static readonly string part2Html = File.ReadAllText(htmlPath + "part2Html.txt");
        static readonly string footerHtml = "</body></html>";
        Settings settings;
        DataTable dtFields, dtTeams, dtQualifying, dtInterim, dtCrossgames, dtClassementgames;
        QualifyingGames qg;
        InterimGames ig;
        CrossGames cg;
        ClassementGames clg;
        Logging log;
        List<List<String>> divisionsTeamList;
        List<String> fieldNames;
        List<int[]> gamePlan = new List<int[]>() { new int[]{ 0, 2, 3 },
                                                   new int[]{ 1, 3, 4 },
                                                   new int[]{ 2, 4, 1 },
                                                   new int[]{ 0, 3, 2 },
                                                   new int[]{ 1, 4, 0 },
                                                   new int[]{ 2, 3, 1 },
                                                   new int[]{ 0, 4, 3 },
                                                   new int[]{ 1, 2, 0 },
                                                   new int[]{ 3, 4, 0 },
                                                   new int[]{ 0, 1, 4 } };
        static readonly List<String> tableNames = new List<String>() { "vorrunde_erg_gr",
                                                                        "vorrunde_spielplan",
                                                                        "zwischenrunde_erg_gr",
                                                                        "zwischenrunde_spielplan",
                                                                        "kreuzspiele_spielplan",
                                                                        "platzspiele_spielplan",
                                                                        "platzierungen" };
        Timer updateTournamentEndtime;
        SQLiteConnection connSqlite;
        #endregion

        public FormMain()
        {
            InitializeComponent();

            init();
        }

        void init()
        {
            log = new Logging();

            initSettings();

            divisionsTeamList = new List<List<String>>();

            initDataTableFields();

            initDataTableTeams();

            initDataTableQualifying();

            initDataTableInterim();

            initDataTableCrossgames();

            initDataTableClassementgames();

            initializeTimer();

            checkBoxUseSecondGameplan_CheckedChanged(checkBoxUseSecondGameplan, EventArgs.Empty);

            checkBoxUseCrossgames_CheckedChanged(checkBoxUseCrossgames, EventArgs.Empty);

            checkBoxUseInterim_CheckedChanged(checkBoxUseInterim, EventArgs.Empty);

            connSqlite = new SQLiteConnection("Data Source = " + resourcePath + "data.db; Version = 3;");

            this.Text = "TournamentPlaner V13";
        }

        void SaveMatchDataToFile(String fileName, List<MatchData> data)
        {
            using (StreamWriter sw = new StreamWriter(fileName))
            {
                foreach (MatchData md in data)
                    sw.WriteLine(md.getRowdataAsCSVString());
            }
        }

        void SaveResultDataToFile(String fileName, List<ResultData> data)
        {
            using (StreamWriter sw = new StreamWriter(fileName))
            {
                foreach (ResultData rd in data)
                    sw.WriteLine(rd.getRowdataAsCSVString());
            }
        }

        List<MatchData> LoadMatchDataFromFile(String fileName)
        {
            List<MatchData> mdList = new List<MatchData>();

            try
            { 
                using (StreamReader sr = new StreamReader(fileName))
                {
                    string line = "";

                    while ((line = sr.ReadLine()) != null)
                    {
                        MatchData md = new MatchData();
                        md.fillRowWithCSVString(line);
                        mdList.Add(md);
                    }
                }
            }
            catch(FileNotFoundException e)
            {
                log.write(e.ToString());
            }

            return mdList;
        }

        List<ResultData> LoadResultDataFromFile(String fileName)
        {
            List<ResultData> rdList = new List<ResultData>();

            try
            {
                using (StreamReader sr = new StreamReader(fileName))
                {
                    string line = "";

                    while ((line = sr.ReadLine()) != null)
                    {
                        ResultData rd = new ResultData();
                        rd.fillRowWithCSVString(line);
                        rdList.Add(rd);
                    }
                }
            }
            catch (FileNotFoundException e)
            {
                log.write(e.ToString());
            }

            return rdList;
        }

        #region data export and upload
        void exportTournamentDataToDB()
        {
            connSqlite.Open();

            try
            {
                SQLiteCommand cmdSqlite = new SQLiteCommand(connSqlite);

                foreach (String tableName in tableNames)
                {
                    if (tableName.Contains("vorrunde_erg") || tableName.Contains("zwischenrunde_erg"))
                    {
                        foreach (String pr in prefix)
                        {
                            cmdSqlite.CommandText = "delete from " + tableName + pr + ";";
                            cmdSqlite.ExecuteNonQuery();
                        }
                    }
                    else
                    {
                        cmdSqlite.CommandText = "delete from " + tableName + ";";
                        cmdSqlite.ExecuteNonQuery();
                    }
                }

                if (qg != null)
                {
                    for (int i = 0; i < qg.matchData.Count; i++)
                    {
                        MatchData md = qg.matchData[i];
                        cmdSqlite.CommandText = "INSERT INTO vorrunde_spielplan VALUES(" + i + "," + md.Round + "," + md.Game + ",'"
                            + md.Time + "'," + md.FieldNumber + ",'" + md.FieldName + "','" + md.TeamA + "','" + md.TeamB + "','"
                            + md.Referee + "'," + md.PointsMatch1TeamA + "," + md.PointsMatch1TeamB
                            + "," + md.PointsMatch2TeamA + "," + md.PointsMatch2TeamB
                            + "," + md.PointsMatch3TeamA + "," + md.PointsMatch3TeamB + ")";
                        cmdSqlite.ExecuteNonQuery();
                    }

                    if (qg.matchData.Count > 0)
                    {
                        foreach (String tableName in tableNames)
                        {
                            if (tableName.Contains("vorrunde_erg"))
                            {
                                for(int i = 0; i < prefix.Count; i++)
                                {
                                    if (i < qg.resultData.Count)
                                    {
                                        for (int ii = 0; ii < qg.resultData[i].Count; ii++)
                                        {
                                            cmdSqlite.CommandText = "INSERT INTO " + tableName + prefix[i];
                                            cmdSqlite.CommandText += " VALUES(" + qg.resultData[i][ii].Rank;
                                            cmdSqlite.CommandText += ",'" + qg.resultData[i][ii].Team + "'";
                                            cmdSqlite.CommandText += "," + qg.resultData[i][ii].PointsSets;
                                            cmdSqlite.CommandText += "," + qg.resultData[i][ii].PointsMatches;
                                            cmdSqlite.CommandText += "," + qg.resultData[i][ii].InternalRank;
                                            cmdSqlite.CommandText += "," + qg.resultData[i][ii].ExternalRank + ")";
                                            cmdSqlite.ExecuteNonQuery();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (ig != null)
                {
                    for (int i = 0; i < ig.matchData.Count; i++)
                    {
                        MatchData md = ig.matchData[i];
                        cmdSqlite.CommandText = "INSERT INTO zwischenrunde_spielplan VALUES(" + i + "," + md.Round + "," + md.Game + ",'"
                            + md.Time + "'," + md.FieldNumber + ",'" + md.FieldName + "','" + md.TeamA + "','" + md.TeamB + "','"
                            + md.Referee + "'," + md.PointsMatch1TeamA + "," + md.PointsMatch1TeamB
                            + "," + md.PointsMatch2TeamA + "," + md.PointsMatch2TeamB
                            + "," + md.PointsMatch3TeamA + "," + md.PointsMatch3TeamB + ")";
                        cmdSqlite.ExecuteNonQuery();
                    }

                    if(ig.matchData.Count > 0)
                    {
                        foreach (String tableName in tableNames)
                        {
                            if (tableName.Contains("zwischenrunde_erg"))
                            {
                                for (int i = 0; i < prefix.Count; i++)
                                {
                                    if (i < ig.resultData.Count)
                                    {
                                        for (int ii = 0; ii < ig.resultData[i].Count; ii++)
                                        {
                                            cmdSqlite.CommandText = "INSERT INTO " + tableName + prefix[i];
                                            cmdSqlite.CommandText += " VALUES(" + ig.resultData[i][ii].Rank;
                                            cmdSqlite.CommandText += ",'" + ig.resultData[i][ii].Team + "'";
                                            cmdSqlite.CommandText += "," + ig.resultData[i][ii].PointsSets;
                                            cmdSqlite.CommandText += "," + ig.resultData[i][ii].PointsMatches;
                                            cmdSqlite.CommandText += "," + ig.resultData[i][ii].InternalRank;
                                            cmdSqlite.CommandText += "," + ig.resultData[i][ii].ExternalRank + ")";
                                            cmdSqlite.ExecuteNonQuery();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (cg != null)
                {
                    for (int i = 0; i < cg.matchData.Count; i++)
                    {
                        MatchData md = cg.matchData[i];
                        cmdSqlite.CommandText = "INSERT INTO kreuzspiele_spielplan VALUES(" + i + "," + md.Round + "," + md.Game + ",'"
                            + md.Time + "'," + md.FieldNumber + ",'" + md.FieldName + "','" + md.TeamA + "','" + md.TeamB + "','"
                            + md.Referee + "'," + md.PointsMatch1TeamA + "," + md.PointsMatch1TeamB
                            + "," + md.PointsMatch2TeamA + "," + md.PointsMatch2TeamB
                            + "," + md.PointsMatch3TeamA + "," + md.PointsMatch3TeamB + ")";
                        cmdSqlite.ExecuteNonQuery();
                    }
                }

                if (clg != null)
                {
                    for (int i = 0; i < clg.matchData.Count; i++)
                    {
                        MatchData md = clg.matchData[i];
                        cmdSqlite.CommandText = "INSERT INTO platzspiele_spielplan VALUES(" + i + "," + md.Round + "," + md.Game + ",'"
                            + md.Time + "'," + md.FieldNumber + ",'" + md.FieldName + "','" + md.TeamA + "','" + md.TeamB + "','"
                            + md.Referee + "'," + md.PointsMatch1TeamA + "," + md.PointsMatch1TeamB
                            + "," + md.PointsMatch2TeamA + "," + md.PointsMatch2TeamB
                            + "," + md.PointsMatch3TeamA + "," + md.PointsMatch3TeamB + ")";
                        cmdSqlite.ExecuteNonQuery();
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
            
            connSqlite.Close();
        }

        bool FileInUse(string path)
        {
            try
            {
                using (FileStream fs = new FileStream(path, FileMode.OpenOrCreate))
                {
                    bool bcw = fs.CanWrite;
                }

                return false;
            }
            catch (IOException ex)
            {
                return true;
            }
        }
        
        void uploadToFTP()
        {
            if (!FileInUse(resourcePath + "data.db"))
            {
                try
                {
                    using (WebClient client = new WebClient())
                    {
                        client.Credentials = new NetworkCredential("38730ftp3", "");
                        client.UploadFile("ftp://e35811-ftp.services.easyname.eu", WebRequestMethods.Ftp.UploadFile, resourcePath + "data.db");
                    }
                    
                    log.write("db file upload finished");
                }
                catch(Exception e)
                {
                    log.write(e.Message);
                }
            }
            else
            {
                log.write("db file is in use, NO upload possible");
            }
        }

        private void buttonFTP_Click(object sender, EventArgs e)
        {
            uploadToFTP();
        }
        #endregion

        #region general ui methods
        void initializeTimer()
        {
            updateTournamentEndtime = new Timer();
            updateTournamentEndtime.Interval = 10 * 1000;
            updateTournamentEndtime.Tick += new EventHandler(timerRecalculateTournamentTime);
            updateTournamentEndtime.Enabled = true;
        }

        void timerRecalculateTournamentTime(object Sender, EventArgs e)
        {
            DateTime lastTimeFromRound = DateTime.Now;
            int addTime = 0;

            if (clg != null && clg.matchData.Count > 0)
            {
                addTime += settings.MinutesForFinals * 60;

                lastTimeFromRound = clg.matchData[clg.matchData.Count - 1].Time;
                lastTimeFromRound = lastTimeFromRound.AddSeconds(addTime);
            }
            else if (cg != null && cg.matchData.Count > 0)
            {
                addTime += calculateTimeForClassementgames();
                addTime += settings.MinutesForFinals * 60;

                lastTimeFromRound = cg.matchData[cg.matchData.Count - 1].Time;
                lastTimeFromRound = lastTimeFromRound.AddSeconds(addTime);
            }
            else if (ig != null && ig.matchData.Count > 0)
            {
                addTime += calculateTimeForCrossgames();
                addTime += calculateTimeForClassementgames();
                addTime += settings.MinutesForFinals * 60;

                lastTimeFromRound = ig.matchData[ig.matchData.Count - 1].Time;
                lastTimeFromRound = lastTimeFromRound.AddSeconds(addTime);
            }
            else if (qg != null && qg.matchData.Count > 0)
            {
                addTime += calculateTimeForInterimgames();
                addTime += calculateTimeForCrossgames();
                addTime += calculateTimeForClassementgames();
                addTime += settings.MinutesForFinals * 60;

                lastTimeFromRound = qg.matchData[qg.matchData.Count - 1].Time;
                lastTimeFromRound = lastTimeFromRound.AddSeconds(addTime);
            }

            this.toolStripStatusLabelEstimatedTournamentTime.Text = lastTimeFromRound.ToString("HH:mm");
        }

        void setRowColorsForEachRound(DataGridView dgv)
        {
            int lastRound = 0;
            int newColor = 0;

            foreach (DataGridViewRow row in dgv.Rows)
            {
                int roundValue = Convert.ToInt32(row.Cells["Runde"].Value);

                if (lastRound < roundValue)
                {
                    lastRound = roundValue;

                    newColor++;

                    if (newColor >= rowColors.Count)
                        newColor = 0;
                }

                row.DefaultCellStyle.BackColor = rowColors[newColor];
            }
        }

        private void tabControl_Click(object sender, EventArgs e)
        {
            String tabName = this.tabControl.SelectedTab.Name;

            if(tabName == "tabPageQualifying")
            {
                setRowColorsForEachRound(dataGridViewQualifyingRound);
            }
            else if(tabName == "tabPageInterim")
            {
                setRowColorsForEachRound(dataGridViewInterimRound);
            }
            else if (tabName == "tabPageCrossgames")
            {
                setRowColorsForEachRound(dataGridViewCrossgamesRound);
            }
            else if (tabName == "tabPageClassement")
            {
                setRowColorsForEachRound(dataGridViewClassementgamesRound);
            }
        }

        int calculateTimeForInterimgames()
        {
            int add = 0;

            add += settings.PauseBetweenQualifyingInterim * 60;
            add += qg.matchData.Count * (((settings.SetsInterim * settings.MinutesPerSetInterim) + settings.PausePerSetInterim) * 60) / fieldNames.Count;

            return add;
        }

        int calculateTimeForCrossgames()
        {
            int add = 0;

            switch (countTeams())
            {
                case 20:
                    add += ((settings.SetsCrossgames * settings.MinutesPerSetCrossgame) + settings.PausePerSetCrossgame) * 60 * 8 / fieldNames.Count;
                    break;
                case 25:
                    add += ((settings.SetsCrossgames * settings.MinutesPerSetCrossgame) + settings.PausePerSetCrossgame) * 60 * 10 / fieldNames.Count;
                    break;
                case 28:
                case 30:
                case 35:
                case 40:
                case 45:
                    add += ((settings.SetsCrossgames * settings.MinutesPerSetCrossgame) + settings.PausePerSetCrossgame) * 60 * 12 / fieldNames.Count;
                    break;
            }

            return add;
        }

        int calculateTimeForClassementgames()
        {
            int add = 0;

            add += settings.PauseBetweenCrossgamesClassement * 60;

            add += ((countTeams() / 2) - 1) * ((settings.SetsClassement * settings.MinutesPerSetClassement) * 60) / fieldNames.Count;

            return add;
        }
        #endregion

        #region settings
        void initSettings()
        {
            settings = new Settings();

            if(File.Exists(settingsFileName))
            {
                using (StreamReader sr = new StreamReader(settingsFileName))
                {
                    string line = "";

                    String[] fieldArray = (line = sr.ReadLine()).Split(';');

                    settings.StartTournament = DateTime.Parse(fieldArray[0]);
                    settings.SetsQualifying = Convert.ToInt32(fieldArray[1]);
                    settings.MinutesPerSetQualifying = Convert.ToInt32(fieldArray[2]);
                    settings.PausePerSetQualifying = Convert.ToInt32(fieldArray[3]);
                    settings.PauseBetweenQualifyingInterim = Convert.ToInt32(fieldArray[4]);
                    settings.SetsInterim = Convert.ToInt32(fieldArray[5]);
                    settings.MinutesPerSetInterim = Convert.ToInt32(fieldArray[6]);
                    settings.PausePerSetInterim = Convert.ToInt32(fieldArray[7]);
                    settings.PauseBetweenInterimCrossgames = Convert.ToInt32(fieldArray[8]);
                    settings.SetsCrossgames = Convert.ToInt32(fieldArray[9]);
                    settings.MinutesPerSetCrossgame = Convert.ToInt32(fieldArray[10]);
                    settings.PausePerSetCrossgame = Convert.ToInt32(fieldArray[11]);
                    settings.PauseBetweenCrossgamesClassement = Convert.ToInt32(fieldArray[12]);
                    settings.SetsClassement = Convert.ToInt32(fieldArray[13]);
                    settings.MinutesPerSetClassement = Convert.ToInt32(fieldArray[14]);
                    settings.MinutesForFinals = Convert.ToInt32(fieldArray[15]);
                    settings.UseSecondGameplan = Convert.ToBoolean(fieldArray[16]);
                    settings.UseCrossgames = Convert.ToBoolean(fieldArray[17]);
                    settings.UseInterim = Convert.ToBoolean(fieldArray[18]);
                }
            }
            else
            {
                loadDefaultSettings();
            }

            loadSettingsToForm();
        }

        void writeSettingsToFile()
        {
            using (StreamWriter sw = new StreamWriter(settingsFileName))
            {
                sw.WriteLine(settings.StartTournament + ";" +
                            settings.SetsQualifying + ";" + 
                            settings.MinutesPerSetQualifying + ";" +
                            settings.PausePerSetQualifying + ";" +
                            settings.PauseBetweenQualifyingInterim + ";" +
                            settings.SetsInterim + ";" +
                            settings.MinutesPerSetInterim + ";" +
                            settings.PausePerSetInterim + ";" +
                            settings.PauseBetweenInterimCrossgames + ";" +
                            settings.SetsCrossgames + ";" +
                            settings.MinutesPerSetCrossgame + ";" +
                            settings.PausePerSetCrossgame + ";" +
                            settings.PauseBetweenCrossgamesClassement + ";" +
                            settings.SetsClassement + ";" +
                            settings.MinutesPerSetClassement + ";" +
                            settings.MinutesForFinals + ";" +
                            settings.UseSecondGameplan + ";" +
                            settings.UseCrossgames + ";" + 
                            settings.UseInterim);
            }
        }

        void loadDefaultSettings()
        {
            settings.StartTournament = DateTime.Parse("09:00");
            settings.SetsQualifying = 1;
            settings.MinutesPerSetQualifying = 10;
            settings.PausePerSetQualifying = 0;
            settings.PauseBetweenQualifyingInterim = 0;
            settings.SetsInterim = 1;
            settings.MinutesPerSetInterim = 10;
            settings.PausePerSetInterim = 0;
            settings.PauseBetweenInterimCrossgames = 0;
            settings.SetsCrossgames = 1;
            settings.MinutesPerSetCrossgame = 10;
            settings.PausePerSetCrossgame = 0;
            settings.PauseBetweenCrossgamesClassement = 0;
            settings.SetsClassement = 1;
            settings.MinutesPerSetClassement = 15;
            settings.MinutesForFinals = 0;
            settings.UseSecondGameplan = true;
            settings.UseCrossgames = true;
            settings.UseInterim = true;

            loadSettingsToForm();
        }

        void loadSettingsToForm()
        {
            dateTimePickerTournamentstart.Value = settings.StartTournament;

            numericUpDownQualifyingSets.Value = settings.SetsQualifying;
            numericUpDownQualifyingMinutesPerSet.Value = settings.MinutesPerSetQualifying;
            numericUpDownQualifyingPauseBetweenSets.Value = settings.PausePerSetQualifying;

            numericUpDownPauseBetweenQualifyingInterim.Value = settings.PauseBetweenQualifyingInterim;

            numericUpDownInterimSets.Value = settings.SetsInterim;
            numericUpDownInterimMinutesPerSet.Value = settings.MinutesPerSetInterim;
            numericUpDownInterimPauseBetweenSets.Value = settings.PausePerSetInterim;

            numericUpDownPauseBetweenInterimCrossgames.Value = settings.PauseBetweenInterimCrossgames;

            numericUpDownCrossgamesSets.Value = settings.SetsCrossgames;
            numericUpDownCrossgamesMinutesPerSet.Value = settings.MinutesPerSetCrossgame;
            numericUpDownCrossgamesPauseBetweenSets.Value = settings.PausePerSetCrossgame;

            if (settings.UseSecondGameplan)
            {
                checkBoxUseSecondGameplan.Checked = true;
            }
            else
            {
                checkBoxUseSecondGameplan.Checked = false;
            }

            if (settings.UseCrossgames)
            {
                checkBoxUseCrossgames.Checked = true;
            }
            else
            {
                checkBoxUseCrossgames.Checked = false;
            }

            if (settings.UseInterim)
            {
                checkBoxUseInterim.Checked = true;
            }
            else
            {
                checkBoxUseInterim.Checked = false;
            }

            numericUpDownPauseBetweenCrossgamesClassement.Value = settings.PauseBetweenCrossgamesClassement;

            numericUpDownClassementSets.Value = settings.SetsClassement;
            numericUpDownClassementMinutesPerSet.Value = settings.MinutesPerSetClassement;
            numericUpDownTimeForFinals.Value = settings.MinutesForFinals;
        }
        
        #region forms
        private void buttonSaveSettings_Click(object sender, EventArgs e)
        {
            settings.StartTournament = dateTimePickerTournamentstart.Value;

            settings.SetsQualifying = Convert.ToInt32(numericUpDownQualifyingSets.Value);
            settings.MinutesPerSetQualifying = Convert.ToInt32(numericUpDownQualifyingMinutesPerSet.Value);
            settings.PausePerSetQualifying = Convert.ToInt32(numericUpDownQualifyingPauseBetweenSets.Value);

            settings.PauseBetweenQualifyingInterim = Convert.ToInt32(numericUpDownPauseBetweenQualifyingInterim.Value);

            settings.SetsInterim = Convert.ToInt32(numericUpDownInterimSets.Value);
            settings.MinutesPerSetInterim = Convert.ToInt32(numericUpDownInterimMinutesPerSet.Value);
            settings.PausePerSetInterim = Convert.ToInt32(numericUpDownInterimPauseBetweenSets.Value);

            settings.PauseBetweenInterimCrossgames = Convert.ToInt32(numericUpDownPauseBetweenInterimCrossgames.Value);

            settings.SetsCrossgames = Convert.ToInt32(numericUpDownCrossgamesSets.Value);
            settings.MinutesPerSetCrossgame = Convert.ToInt32(numericUpDownCrossgamesMinutesPerSet.Value);
            settings.PausePerSetCrossgame = Convert.ToInt32(numericUpDownCrossgamesPauseBetweenSets.Value);

            settings.UseSecondGameplan = checkBoxUseSecondGameplan.Checked;
            settings.UseCrossgames = checkBoxUseCrossgames.Checked;
            settings.UseInterim = checkBoxUseInterim.Checked;

            settings.PauseBetweenCrossgamesClassement = Convert.ToInt32(numericUpDownPauseBetweenCrossgamesClassement.Value);

            settings.SetsClassement = Convert.ToInt32(numericUpDownClassementSets.Value);
            settings.MinutesPerSetClassement = Convert.ToInt32(numericUpDownClassementMinutesPerSet.Value);
            settings.MinutesForFinals = Convert.ToInt32(numericUpDownTimeForFinals.Value);

            writeSettingsToFile();

            writeFieldsToFile();
        }

        private void buttonRejectSettings_Click(object sender, EventArgs e)
        {
            initSettings();
        }

        private void buttonResetSettings_Click(object sender, EventArgs e)
        {
            loadDefaultSettings();
        }

        private void checkBoxUseSecondGameplan_CheckedChanged(object sender, EventArgs e)
        {
            settings.UseSecondGameplan = checkBoxUseSecondGameplan.Checked;
        }

        private void checkBoxUseCrossgames_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxUseCrossgames.Checked)
            {
                numericUpDownCrossgamesSets.Enabled = true;
                numericUpDownCrossgamesMinutesPerSet.Enabled = true;
                numericUpDownCrossgamesPauseBetweenSets.Enabled = true;
                tabControl.TabPages.Insert(3, tabPageCrossgames);
            }
            else
            {
                numericUpDownCrossgamesSets.Enabled = false;
                numericUpDownCrossgamesMinutesPerSet.Enabled = false;
                numericUpDownCrossgamesPauseBetweenSets.Enabled = false;
                tabControl.TabPages.Remove(tabPageCrossgames);
            }
        }

        private void checkBoxUseInterim_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxUseInterim.Checked)
            {
                numericUpDownInterimSets.Enabled = true;
                numericUpDownInterimMinutesPerSet.Enabled = true;
                numericUpDownInterimPauseBetweenSets.Enabled = true;
                tabControl.TabPages.Insert(2, tabPageInterim);                
            }
            else
            {
                numericUpDownInterimSets.Enabled = false;
                numericUpDownInterimMinutesPerSet.Enabled = false;
                numericUpDownInterimPauseBetweenSets.Enabled = false;
                tabControl.TabPages.Remove(tabPageInterim);
            }
        }
        #endregion
        #endregion

        #region fields
        void initDataTableFields()
        {
            fieldNames = new List<String>();
            dtFields = new DataTable("dtFields");

            dtFields.Columns.Add("Platz");
            dtFields.Columns.Add("Name");

            typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                dataGridViewFields,
                                                new object[]{ true });

            dataGridViewFields.DataSource = dtFields;

            foreach (DataGridViewColumn dgvc in dataGridViewFields.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            loadFields();

            if (dtFields.Rows.Count == 0)
            {
                dtFields.Rows.Add(new object[] { "1", "" });
                numericUpDownFields.Value = dtFields.Rows.Count;
                writeFieldsToFile();
            }

            extractFieldnames();
        }

        void extractFieldnames()
        {
            fieldNames.Clear();

            foreach(DataRow dr in dtFields.Rows)
                fieldNames.Add(dr[1].ToString());
        }

        void loadFields()
        {
            try
            {
                using (StreamReader sr = new StreamReader(fieldsFileName))
                {
                    string line = "";

                    while ((line = sr.ReadLine()) != null)
                    {
                        String[] fieldArray = line.Split(';');

                        dtFields.Rows.Add(fieldArray);
                    }
                }

                numericUpDownFields.Value = dtFields.Rows.Count;
            }
            catch (FileNotFoundException e)
            {
                log.write(e.ToString());
            }
        }

        void writeFieldsToFile()
        {
            using (StreamWriter sw = new StreamWriter(fieldsFileName))
            {
                for (int i = 0; i < dtFields.Rows.Count; i++)
                {
                    String text = "";
                    for (int ii = 0; ii < dtFields.Columns.Count; ii++)
                    {
                        text += dtFields.Rows[i][ii];

                        if (!(ii + 1 >= dtFields.Columns.Count))
                            text += ";";
                    }
                    sw.WriteLine(text);
                }
            }
        }

        #region form
        private void numericUpDownFields_ValueChanged(object sender, EventArgs e)
        {
            if (dtFields.Rows.Count > numericUpDownFields.Value)
            {
                dtFields.Rows.RemoveAt(Convert.ToInt32(numericUpDownFields.Value));
            }
            else if(dtFields.Rows.Count < numericUpDownFields.Value)
            {
                dtFields.Rows.Add(new object[] { numericUpDownFields.Value.ToString(), "" });
            }

            writeFieldsToFile();
        }
        #endregion
        #endregion

        #region teams
        void initDataTableTeams()
        {
            dtTeams = new DataTable("dtTeams");

            foreach (String col in prefix)
                dtTeams.Columns.Add("Gruppe " + col);

            typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                dataGridViewTeams,
                                                new object[]{ true });

            dataGridViewTeams.DataSource = dtTeams;

            foreach (DataGridViewColumn dgvc in dataGridViewTeams.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            loadTeams();

            extractTeams();
        }

        void loadTeams()
        {
            try
            {
                using (StreamReader sr = new StreamReader(teamsFileName))
                {
                    string line = "";

                    while ((line = sr.ReadLine()) != null)
                    {
                        String[] teamArray = line.Split(';');
                        
                        dtTeams.Rows.Add(teamArray);
                    }
                }
            }
            catch(FileNotFoundException e)
            {
                log.write("file " + teamsFileName + " not found! nothing to load. " + e.ToString());
            }
        }

        void saveTeams()
        {
            dtTeams = (DataTable)dataGridViewTeams.DataSource;

            using (StreamWriter sw = new StreamWriter(teamsFileName))
            {
                for (int i = 0; i < dtTeams.Rows.Count; i++)
                {
                    String text = "";
                    for (int ii = 0; ii < dtTeams.Columns.Count; ii++)
                    {
                        text += dtTeams.Rows[i][ii];

                        if (!(ii + 1 >= dtTeams.Columns.Count))
                            text += ";";
                    }
                    sw.WriteLine(text);
                }
            }
        }

        bool checkDoubleTeamNames(String teamName)
        {
            if (teamName != "")
            {
                int count = 0;
                foreach (DataRow dr in dtTeams.Rows)
                {
                    for (int i = 0; i < dr.ItemArray.Length; i++)
                    {
                        if (teamName == dr.ItemArray[i].ToString())
                        {
                            count++;

                            if(count > 1)
                                return true;
                        }
                    }
                }
            }

            return false;
        }

        int countTeams()
        {
            int count = 0;

            for(int i = 0; i < dtTeams.Rows.Count; i++)
            {
                for (int ii = 0; ii < dtTeams.Columns.Count; ii++)
                {
                    if(dtTeams.Rows[i][ii].ToString() != "")
                        count++;
                }
            }

            return count;
        }

        void extractTeams()
        {
            divisionsTeamList.Clear();

            for(int i = 0; i < dtTeams.Columns.Count; i++)
            {
                List<String> group = new List<String>();

                for (int ii = 0; ii < dtTeams.Rows.Count; ii++)
                {
                    if(dtTeams.Rows[ii][i].ToString() != "")
                        group.Add(dtTeams.Rows[ii][i].ToString());
                }

                if(group.Count > 0)
                    divisionsTeamList.Add(group);
            }
        }

        #region form
        private void buttonSaveTeams_Click(object sender, EventArgs e)
        {
            log.write("save teams");
            saveTeams();
        }

        private void dataGridViewTeams_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            String teamName = dataGridViewTeams[e.ColumnIndex, e.RowIndex].Value.ToString();

            log.write("team name " + teamName + " entered at position (row/col) " + e.RowIndex + "/" + e.ColumnIndex);

            if (checkDoubleTeamNames(teamName))
            {
                MessageBox.Show("Achtung doppelter Teamname gefunden! Änderung wird verworfen!");
                log.write("found double team name, discard change!");
                dataGridViewTeams[e.ColumnIndex, e.RowIndex].Value = "";
            }
        }

        private void buttonClearTeams_Click(object sender, EventArgs e)
        {
            DialogResult dialogResult = MessageBox.Show("Mannschaften löschen?!", "Daten löschen", MessageBoxButtons.OKCancel);
            if (dialogResult == DialogResult.OK)
            {
                if (divisionsTeamList != null)
                    divisionsTeamList.Clear();

                if (dtTeams != null)
                {
                    dtTeams.Clear();

                    for (int i = 0; i < 5; i++)
                        dtTeams.Rows.Add();

                    saveTeams();
                }
            }
            else if (dialogResult == DialogResult.Cancel)
            {
                // nothing to do
            }
        }

        private void buttonPrintTeams_Click(object sender, EventArgs e)
        {

        }
        #endregion
        #endregion

        #region qualifying
        #region data actions
        void initDataTableQualifying()
        {
            dtQualifying = new DataTable("dtQualifying");
            dtQualifying.Columns.Add("Spiel");
            dtQualifying.Columns.Add("Runde");
            dtQualifying.Columns.Add("Zeit");
            dtQualifying.Columns.Add("Feldnr.");
            dtQualifying.Columns.Add("Feldname");
            dtQualifying.Columns.Add("Team A");
            dtQualifying.Columns.Add("Team B");
            dtQualifying.Columns.Add("Schiedsrichter");
            dtQualifying.Columns.Add("Satz 1 A");
            dtQualifying.Columns.Add("Satz 1 B");
            dtQualifying.Columns.Add("Satz 2 A");
            dtQualifying.Columns.Add("Satz 2 B");
            dtQualifying.Columns.Add("Satz 3 A");
            dtQualifying.Columns.Add("Satz 3 B");

            typeof(DataGridView).InvokeMember("DoubleBuffered", 
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty, 
                                                null, 
                                                dataGridViewQualifyingRound, 
                                                new object[]{ true });

            dataGridViewQualifyingRound.DataSource = dtQualifying;

            foreach (DataGridViewColumn dgvc in dataGridViewQualifyingRound.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            qg = new QualifyingGames(log);

            loadDataQualifyingFromFile();

            loadQualifying();
        }

        void loadDataQualifyingFromFile()
        {
            qg.matchData.Clear();

            qg.matchData = LoadMatchDataFromFile(qualifyingFileName);

            qg.setParameters(divisionsTeamList,
                                gamePlan,
                                settings.StartTournament,
                                settings.SetsQualifying,
                                settings.MinutesPerSetQualifying,
                                settings.PausePerSetQualifying,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames);

            qg.resultData.Clear();

            for(int i = 0; i < prefix.Count; i++)
                qg.resultData.Add(LoadResultDataFromFile(qualifyingResultFileName + "_" + prefix[i] + ".csv")); 
        }

        void loadQualifying()
        {
            if (qg != null)
            {
                if(qg.matchData.Count > 0)
                {
                    foreach(MatchData md in qg.matchData)
                    {
                        dtQualifying.Rows.Add(new object[] { md.Game,
                                                            md.Round,
                                                            md.Time.ToString("HH:mm"),
                                                            md.FieldNumber,
                                                            md.FieldName,
                                                            md.TeamA,
                                                            md.TeamB,
                                                            md.Referee,
                                                            md.PointsMatch1TeamA,
                                                            md.PointsMatch1TeamB,
                                                            md.PointsMatch2TeamA,
                                                            md.PointsMatch2TeamB,
                                                            md.PointsMatch3TeamA,
                                                            md.PointsMatch3TeamB });
                    }

                    if(qg.resultData.Count > 0 && qg.resultData[0].Count == 0)
                        qg.fillResultLists(divisionsTeamList);
                }
            }
        }

        void saveQualifying()
        {
            if (qg != null)
            {
                log.write("calculating qualifying results");

                qg.calculateResults();

                qg.sortResults();

                SaveMatchDataToFile(qualifyingFileName, qg.matchData);

                for (int i = 0; i < prefix.Count; i++)
                {
                    if (qg.resultData.Count > 0 && i < qg.resultData.Count)
                    {
                        if (qg.resultData[i].Count > 0)
                            SaveResultDataToFile(qualifyingResultFileName + "_" + prefix[i] + ".csv", qg.resultData[i]);
                    }
                    else
                    {
                        File.WriteAllText(qualifyingResultFileName + "_" + prefix[i] + ".csv", String.Empty);
                    }
                }

                exportTournamentDataToDB();
            }
        }
        #endregion

        #region form actions
        private void dataGridViewQualifyingRound_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!lockAction)
            {
                switch (e.ColumnIndex)
                {
                    case 2:
                        DateTime gameTime = DateTime.Parse(dtQualifying.Rows[e.RowIndex][2].ToString());

                        qg.recalculateTimeSchedule(e.RowIndex, gameTime);

                        for(int i = 0; i < qg.matchData.Count; i++)
                            dtQualifying.Rows[i][2] = qg.matchData[i].Time.ToString("HH:mm");
                        
                        break;

                    case 8:
                        qg.matchData[e.RowIndex].PointsMatch1TeamA =  int.Parse(dtQualifying.Rows[e.RowIndex][8].ToString());
                        break;

                    case 9:
                        qg.matchData[e.RowIndex].PointsMatch1TeamB = int.Parse(dtQualifying.Rows[e.RowIndex][9].ToString());
                        break;

                    case 10:
                        qg.matchData[e.RowIndex].PointsMatch2TeamA = int.Parse(dtQualifying.Rows[e.RowIndex][10].ToString());
                        break;

                    case 11:
                        qg.matchData[e.RowIndex].PointsMatch2TeamB = int.Parse(dtQualifying.Rows[e.RowIndex][11].ToString());
                        break;

                    case 12:
                        qg.matchData[e.RowIndex].PointsMatch3TeamA = int.Parse(dtQualifying.Rows[e.RowIndex][12].ToString());
                        break;

                    case 13:
                        qg.matchData[e.RowIndex].PointsMatch3TeamB = int.Parse(dtQualifying.Rows[e.RowIndex][13].ToString());
                        break;
                }
            }
        }

        private void buttonGenerateQualifying_Click(object sender, EventArgs e)
        {
            lockAction = true;

            if (qg != null && qg.matchData.Count == 0)
            {
                log.write("generate qualifying games");

                extractFieldnames();

                extractTeams();

                qg.setParameters(divisionsTeamList, 
                                gamePlan,
                                settings.StartTournament,
                                settings.SetsQualifying,
                                settings.MinutesPerSetQualifying,
                                settings.PausePerSetQualifying,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames);

                qg.generateGames();

                loadQualifying();

                saveQualifying();

                setRowColorsForEachRound(dataGridViewQualifyingRound);
            }
            else
            {
                MessageBox.Show("Spiele sind schon vorhanden, generieren abgebrochen!", "Achtung!", MessageBoxButtons.OK);
            }

            lockAction = false;
        }

        private void buttonSaveQualifying_Click(object sender, EventArgs e)
        {
            saveQualifying();
        }
                
        private void buttonClearQualifying_Click(object sender, EventArgs e)
        {
            if (qg != null)
            {
                qg.matchData.Clear();

                qg.resultData.Clear();

                dtQualifying.Clear();

                saveQualifying();
            }
        }

        private void buttonPrintQualifying_Click(object sender, EventArgs e)
        {
            if(qg != null && qg.matchData.Count > 0)
            {
                String gameHtml = headerHtml;

                foreach(MatchData md in qg.matchData)
                {
                    gameHtml += part1Html;

                    gameHtml += "<tr>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.Game + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldNumber + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldName + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamA + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamB + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.Referee + "</span></td>";
                    gameHtml += "</tr>";
                    gameHtml += "</tbody>";
                    gameHtml += "</table>";

                    gameHtml += part2Html;

                    if(md != qg.matchData[qg.matchData.Count - 1])
                        gameHtml += "<div style='page-break-after: always;'></div>";
                }

                gameHtml += footerHtml;

                var pdf = Pdf.From(gameHtml).OfSize(PaperSize.A4).Landscape().Comressed().Content();

                File.WriteAllBytes(pdfPath + "vorrunde.pdf", pdf);
            }
        }

        private void buttonResultsQualifying_Click(object sender, EventArgs e)
        {
            saveQualifying();

            Results rs = new Results(qg);
            rs.saveChangesEvent += saveQualifying;
            rs.ShowDialog();
        }

        private void TextBoxQualifyingFilter_TextChanged(object sender, EventArgs e)
        {
            (dataGridViewQualifyingRound.DataSource as DataTable).DefaultView.RowFilter = string.Format("[Team A] LIKE '{0}%' OR [Team B] LIKE '{0}%' OR Schiedsrichter LIKE '{0}%'", textBoxQualifyingFilter.Text);

            if ((dataGridViewQualifyingRound.DataSource as DataTable).DefaultView.Count == qg.matchData.Count)
            {
                setRowColorsForEachRound(dataGridViewQualifyingRound);
            }
        }
        #endregion
        #endregion

        #region interim games
        #region data actions
        void initDataTableInterim()
        {
            dtInterim = new DataTable("dtInterim");
            dtInterim.Columns.Add("Spiel");
            dtInterim.Columns.Add("Runde");
            dtInterim.Columns.Add("Zeit");
            dtInterim.Columns.Add("Feldnr.");
            dtInterim.Columns.Add("Feldname");
            dtInterim.Columns.Add("Team A");
            dtInterim.Columns.Add("Team B");
            dtInterim.Columns.Add("Schiedsrichter");
            dtInterim.Columns.Add("Satz 1 A");
            dtInterim.Columns.Add("Satz 1 B");
            dtInterim.Columns.Add("Satz 2 A");
            dtInterim.Columns.Add("Satz 2 B");
            dtInterim.Columns.Add("Satz 3 A");
            dtInterim.Columns.Add("Satz 3 B");

            typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                dataGridViewInterimRound,
                                                new object[] { true });

            dataGridViewInterimRound.DataSource = dtInterim;

            foreach (DataGridViewColumn dgvc in dataGridViewInterimRound.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            ig = new InterimGames(log);

            loadDataInterimFromFile();

            loadInterim();
        }

        void loadDataInterimFromFile()
        {
            if (ig != null && qg.matchData.Count > 0)
            {
                ig.matchData.Clear();

                ig.matchData = LoadMatchDataFromFile(interimFileName);

                DateTime startTime = qg.matchData[qg.matchData.Count - 1].Time.AddSeconds((settings.SetsQualifying * settings.MinutesPerSetQualifying * 60) + settings.PausePerSetQualifying);

                ig.setParameters(qg.resultData,
                                gamePlan,
                                startTime,
                                settings.PauseBetweenQualifyingInterim,
                                settings.SetsInterim,
                                settings.MinutesPerSetInterim,
                                settings.PausePerSetInterim,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                qg.matchData[qg.matchData.Count - 1].Round + 1,
                                qg.matchData[qg.matchData.Count - 1].Game + 1,
                                settings.UseSecondGameplan);

                ig.resultData.Clear();

                for (int i = 0; i < prefix.Count; i++)
                    ig.resultData.Add(LoadResultDataFromFile(interimResultFileName + "_" + prefix[i] + ".csv"));
            }
        }

        void loadInterim()
        {
            if (ig != null && ig.matchData.Count > 0)
            {
                foreach (MatchData md in ig.matchData)
                {
                    dtInterim.Rows.Add(new object[] { md.Game,
                                                        md.Round,
                                                        md.Time.ToString("HH:mm"),
                                                        md.FieldNumber,
                                                        md.FieldName,
                                                        md.TeamA,
                                                        md.TeamB,
                                                        md.Referee,
                                                        md.PointsMatch1TeamA,
                                                        md.PointsMatch1TeamB,
                                                        md.PointsMatch2TeamA,
                                                        md.PointsMatch2TeamB,
                                                        md.PointsMatch3TeamA,
                                                        md.PointsMatch3TeamB });
                }
            }
        }

        void saveInterim()
        {
            if (ig != null)
            {
                log.write("calculating interim results");

                if(ig.matchData.Count > 0)
                {
                    ig.calculateResults();
                    ig.sortResults();
                }

                SaveMatchDataToFile(interimFileName, ig.matchData);

                for (int i = 0; i < prefix.Count; i++)
                {
                    if (ig.resultData.Count > 0 && i < ig.resultData.Count)
                    {
                        if (ig.resultData[i].Count > 0)
                            SaveResultDataToFile(interimResultFileName + "_" + prefix[i] + ".csv", ig.resultData[i]);
                    }
                    else
                    {
                        File.WriteAllText(interimResultFileName + "_" + prefix[i] + ".csv", String.Empty);
                    }
                }

                exportTournamentDataToDB();
            }
        }
        #endregion

        #region form actions
        private void dataGridViewInterimRound_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!lockAction)
            {
                switch (e.ColumnIndex)
                {
                    case 2:
                        DateTime gameTime = DateTime.Parse(dtInterim.Rows[e.RowIndex][2].ToString());

                        ig.recalculateTimeSchedule(e.RowIndex, gameTime);

                        for (int i = 0; i < ig.matchData.Count; i++)
                            dtInterim.Rows[i][2] = ig.matchData[i].Time.ToString("HH:mm");

                        break;

                    case 8:
                        ig.matchData[e.RowIndex].PointsMatch1TeamA = int.Parse(dtInterim.Rows[e.RowIndex][8].ToString());
                        break;

                    case 9:
                        ig.matchData[e.RowIndex].PointsMatch1TeamB = int.Parse(dtInterim.Rows[e.RowIndex][9].ToString());
                        break;

                    case 10:
                        ig.matchData[e.RowIndex].PointsMatch2TeamA = int.Parse(dtInterim.Rows[e.RowIndex][10].ToString());
                        break;

                    case 11:
                        ig.matchData[e.RowIndex].PointsMatch2TeamB = int.Parse(dtInterim.Rows[e.RowIndex][11].ToString());
                        break;

                    case 12:
                        ig.matchData[e.RowIndex].PointsMatch3TeamA = int.Parse(dtInterim.Rows[e.RowIndex][12].ToString());
                        break;

                    case 13:
                        ig.matchData[e.RowIndex].PointsMatch3TeamB = int.Parse(dtInterim.Rows[e.RowIndex][13].ToString());
                        break;
                }
            }
        }

        private void buttonGenerateInterim_Click(object sender, EventArgs e)
        {
            lockAction = true;

            List<String> doubleResults = qg.checkEqualDivisionResults();

            if (doubleResults.Count > 0)
            {
                MessageBox.Show("Achtung gleiche Punktestände gefunden! '" + doubleResults[0] + "' = '" + doubleResults[1] + "'! Zwischenrunde wird NICHT generiert!");
                log.write("found double team results " + doubleResults[0] + " = " + doubleResults[1]);
            }
            else
            {
                if (ig != null && qg.matchData.Count > 0 && ig.matchData.Count == 0)
                {
                    log.write("generate interim games");

                    extractFieldnames();

                    DateTime startTime = qg.matchData[qg.matchData.Count - 1].Time.AddSeconds((settings.SetsQualifying * settings.MinutesPerSetQualifying * 60) + settings.PausePerSetQualifying);

                    ig.setParameters(qg.resultData,
                                    gamePlan,
                                    startTime,
                                    settings.PauseBetweenQualifyingInterim,
                                    settings.SetsInterim,
                                    settings.MinutesPerSetInterim,
                                    settings.PausePerSetInterim,
                                    fieldNames.Count,
                                    countTeams(),
                                    fieldNames,
                                    qg.matchData[qg.matchData.Count - 1].Round + 1,
                                    qg.matchData[qg.matchData.Count - 1].Game + 1,
                                    settings.UseSecondGameplan);

                    ig.generateGames();

                    loadInterim();

                    saveInterim();

                    setRowColorsForEachRound(dataGridViewInterimRound);
                }
                else
                {
                    MessageBox.Show("Spiele sind schon vorhanden, generieren abgebrochen!", "Achtung!", MessageBoxButtons.OK);
                }
            }

            lockAction = false;
        }

        private void buttonSaveInterim_Click(object sender, EventArgs e)
        {
            saveInterim();
        }

        private void buttonClearInterim_Click(object sender, EventArgs e)
        {
            if (ig != null)
            {
                ig.matchData.Clear();

                ig.resultData.Clear();

                dtInterim.Clear();

                saveInterim();
            }
        }

        private void buttonPrintInterim_Click(object sender, EventArgs e)
        {
            if (ig != null && ig.matchData.Count > 0)
            {
                String gameHtml = headerHtml;

                foreach (MatchData md in ig.matchData)
                {
                    gameHtml += part1Html;

                    gameHtml += "<tr>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.Game + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldNumber + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldName + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamA + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamB + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.Referee + "</span></td>";
                    gameHtml += "</tr>";
                    gameHtml += "</tbody>";
                    gameHtml += "</table>";

                    gameHtml += part2Html;

                    if (md != ig.matchData[ig.matchData.Count - 1])
                        gameHtml += "<div style='page-break-after: always;'></div>";
                }

                gameHtml += footerHtml;

                var pdf = Pdf.From(gameHtml).OfSize(PaperSize.A4).Landscape().Comressed().Content();

                File.WriteAllBytes(pdfPath + "zwischenrunde.pdf", pdf);
            }
        }

        private void buttonResultsInterim_Click(object sender, EventArgs e)
        {
            saveInterim();

            Results rs = new Results(ig);
            rs.saveChangesEvent += saveInterim;
            rs.ShowDialog();
        }

        private void TextBoxInterimFilter_TextChanged(object sender, EventArgs e)
        {
            (dataGridViewInterimRound.DataSource as DataTable).DefaultView.RowFilter = string.Format("[Team A] LIKE '{0}%' OR [Team B] LIKE '{0}%' OR Schiedsrichter LIKE '{0}%'", textBoxInterimFilter.Text);

            if ((dataGridViewInterimRound.DataSource as DataTable).DefaultView.Count == ig.matchData.Count)
            {
                setRowColorsForEachRound(dataGridViewInterimRound);
            }
        }
        #endregion
        #endregion

        #region crossgames
        #region data actions
        void initDataTableCrossgames()
        {
            dtCrossgames = new DataTable("dtCrossgames");
            dtCrossgames.Columns.Add("Spiel");
            dtCrossgames.Columns.Add("Runde");
            dtCrossgames.Columns.Add("Zeit");
            dtCrossgames.Columns.Add("Feldnr.");
            dtCrossgames.Columns.Add("Feldname");
            dtCrossgames.Columns.Add("Team A");
            dtCrossgames.Columns.Add("Team B");
            dtCrossgames.Columns.Add("Schiedsrichter");
            dtCrossgames.Columns.Add("Satz 1 A");
            dtCrossgames.Columns.Add("Satz 1 B");
            dtCrossgames.Columns.Add("Satz 2 A");
            dtCrossgames.Columns.Add("Satz 2 B");
            dtCrossgames.Columns.Add("Satz 3 A");
            dtCrossgames.Columns.Add("Satz 3 B");

            typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                dataGridViewCrossgamesRound,
                                                new object[] { true });

            dataGridViewCrossgamesRound.DataSource = dtCrossgames;

            foreach (DataGridViewColumn dgvc in dataGridViewCrossgamesRound.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            cg = new CrossGames(log);

            loadDataCrossgamesFromFile();

            loadCrossgames();
        }

        void loadDataCrossgamesFromFile()
        {
            bool tmpMatchDataCountOK = false;

            if (settings.UseInterim)
            {
                log.write("use configuration from interim");

                if (ig.matchData.Count > 0)
                    tmpMatchDataCountOK = true;
            }
            else
            {
                log.write("use configuration from qualifying");

                if (qg.matchData.Count > 0)
                    tmpMatchDataCountOK = true;
            }

            if (cg != null && tmpMatchDataCountOK)
            {
                cg.matchData.Clear();

                cg.matchData = LoadMatchDataFromFile(crossgamesFileName);

                DateTime startTime;
                List<List<ResultData>> tmpResultData;
                int tmpPauseBetweenRounds;
                int tmpRound;
                int tmpGame;

                if (settings.UseInterim)
                {
                    startTime = ig.matchData[ig.matchData.Count - 1].Time.AddSeconds((settings.SetsInterim * settings.MinutesPerSetInterim * 60) + settings.PausePerSetInterim);
                    tmpResultData = ig.resultData;
                    tmpPauseBetweenRounds = settings.PauseBetweenInterimCrossgames;
                    tmpRound = ig.matchData[ig.matchData.Count - 1].Round + 1;
                    tmpGame = ig.matchData[ig.matchData.Count - 1].Game + 1;
                }
                else
                {
                    startTime = qg.matchData[qg.matchData.Count - 1].Time.AddSeconds((settings.SetsQualifying * settings.MinutesPerSetQualifying * 60) + settings.PausePerSetQualifying);
                    tmpResultData = qg.resultData;
                    tmpPauseBetweenRounds = 0;
                    tmpRound = qg.matchData[qg.matchData.Count - 1].Round + 1;
                    tmpGame = qg.matchData[qg.matchData.Count - 1].Game + 1;
                }

                cg.setParameters(tmpResultData,
                                startTime,
                                tmpPauseBetweenRounds,
                                settings.SetsCrossgames,
                                settings.MinutesPerSetCrossgame,
                                settings.PausePerSetCrossgame,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                tmpRound,
                                tmpGame,
                                settings.UseSecondGameplan);

                cg.resultData.Clear();
            }
        }

        void loadCrossgames()
        {
            if (cg != null && cg.matchData.Count > 0)
            {
                foreach (MatchData md in cg.matchData)
                {
                    dtCrossgames.Rows.Add(new object[] { md.Game,
                                                        md.Round,
                                                        md.Time.ToString("HH:mm"),
                                                        md.FieldNumber,
                                                        md.FieldName,
                                                        md.TeamA,
                                                        md.TeamB,
                                                        md.Referee,
                                                        md.PointsMatch1TeamA,
                                                        md.PointsMatch1TeamB,
                                                        md.PointsMatch2TeamA,
                                                        md.PointsMatch2TeamB,
                                                        md.PointsMatch3TeamA,
                                                        md.PointsMatch3TeamB });
                }
            }
        }

        void saveCrossgames()
        {
            if (cg != null)
            {
                log.write("calculating crossgame results");

                SaveMatchDataToFile(crossgamesFileName, cg.matchData);

                exportTournamentDataToDB();
            }
        }
        #endregion

        #region form actions
        private void dataGridViewCrossgamesRound_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!lockAction)
            {
                switch (e.ColumnIndex)
                {
                    case 2:
                        DateTime gameTime = DateTime.Parse(dtCrossgames.Rows[e.RowIndex][2].ToString());

                        cg.recalculateTimeSchedule(e.RowIndex, gameTime);

                        for (int i = 0; i < cg.matchData.Count; i++)
                            dtCrossgames.Rows[i][2] = cg.matchData[i].Time.ToString("HH:mm");

                        break;

                    case 8:
                        cg.matchData[e.RowIndex].PointsMatch1TeamA = int.Parse(dtCrossgames.Rows[e.RowIndex][8].ToString());
                        break;

                    case 9:
                        cg.matchData[e.RowIndex].PointsMatch1TeamB = int.Parse(dtCrossgames.Rows[e.RowIndex][9].ToString());
                        break;

                    case 10:
                        cg.matchData[e.RowIndex].PointsMatch2TeamA = int.Parse(dtCrossgames.Rows[e.RowIndex][10].ToString());
                        break;

                    case 11:
                        cg.matchData[e.RowIndex].PointsMatch2TeamB = int.Parse(dtCrossgames.Rows[e.RowIndex][11].ToString());
                        break;

                    case 12:
                        cg.matchData[e.RowIndex].PointsMatch3TeamA = int.Parse(dtCrossgames.Rows[e.RowIndex][12].ToString());
                        break;

                    case 13:
                        cg.matchData[e.RowIndex].PointsMatch3TeamB = int.Parse(dtCrossgames.Rows[e.RowIndex][13].ToString());
                        break;
                }
            }
        }

        private void buttonGenerateCrossgames_Click(object sender, EventArgs e)
        {
            lockAction = true;

            List<String> doubleResults;

            if (settings.UseInterim)
            {
                log.write("check double results from interim");
                doubleResults = ig.checkEqualDivisionResults();
            }
            else
            {
                log.write("check double results from qualifying");
                doubleResults = qg.checkEqualDivisionResults();
            }

            if (doubleResults.Count > 0)
            {
                MessageBox.Show("Achtung gleiche Punktestände gefunden! '" + doubleResults[0] + "' = '" + doubleResults[1] + "'! Kreuzspiele werden NICHT generiert!");
                log.write("found double team results " + doubleResults[0] + " = " + doubleResults[1]);
            }
            else
            {
                bool tmpMatchDataCountOK = false;

                if(settings.UseInterim)
                {
                    log.write("use configuration from interim");

                    if (ig.matchData.Count > 0)
                        tmpMatchDataCountOK = true;
                }
                else
                {
                    log.write("use configuration from qualifying");

                    if (qg.matchData.Count > 0)
                        tmpMatchDataCountOK = true;
                }

                if (cg != null && cg.matchData.Count == 0 && tmpMatchDataCountOK)
                {
                    log.write("generate crossgames");

                    extractFieldnames();

                    DateTime startTime;
                    List<List<ResultData>> tmpResultData;
                    int tmpPauseBetweenRounds;
                    int tmpRound;
                    int tmpGame;
                    
                    if (settings.UseInterim)
                    {
                        startTime = ig.matchData[ig.matchData.Count - 1].Time.AddSeconds((settings.SetsInterim * settings.MinutesPerSetInterim * 60) + settings.PausePerSetInterim);
                        tmpResultData = ig.resultData;
                        tmpPauseBetweenRounds = settings.PauseBetweenInterimCrossgames;
                        tmpRound = ig.matchData[ig.matchData.Count - 1].Round + 1;
                        tmpGame = ig.matchData[ig.matchData.Count - 1].Game + 1;
                    }
                    else
                    {
                        startTime = qg.matchData[qg.matchData.Count - 1].Time.AddSeconds((settings.SetsQualifying * settings.MinutesPerSetQualifying * 60) + settings.PausePerSetQualifying);
                        tmpResultData = qg.resultData;
                        tmpPauseBetweenRounds = 0;
                        tmpRound = qg.matchData[qg.matchData.Count - 1].Round + 1;
                        tmpGame = qg.matchData[qg.matchData.Count - 1].Game + 1;
                    }

                    cg.setParameters(tmpResultData,
                                    startTime,
                                    tmpPauseBetweenRounds,
                                    settings.SetsCrossgames,
                                    settings.MinutesPerSetCrossgame,
                                    settings.PausePerSetCrossgame,
                                    fieldNames.Count,
                                    countTeams(),
                                    fieldNames,
                                    tmpRound,
                                    tmpGame,
                                    settings.UseSecondGameplan);

                    cg.generateGames();

                    loadCrossgames();

                    saveCrossgames();

                    setRowColorsForEachRound(dataGridViewCrossgamesRound);
                }
                else
                {
                    MessageBox.Show("Spiele sind schon vorhanden, generieren abgebrochen!", "Achtung!", MessageBoxButtons.OK);
                }
            }

            lockAction = false;
        }

        private void buttonSaveCrossgames_Click(object sender, EventArgs e)
        {
            saveCrossgames();
        }

        private void buttonClearCrossgames_Click(object sender, EventArgs e)
        {
            if (cg != null)
            {
                cg.matchData.Clear();

                dtCrossgames.Clear();

                saveCrossgames();
            }
        }

        private void buttonPrintCrossgames_Click(object sender, EventArgs e)
        {
            if (cg != null && cg.matchData.Count > 0)
            {
                String gameHtml = headerHtml;

                foreach (MatchData md in cg.matchData)
                {
                    gameHtml += part1Html;

                    gameHtml += "<tr>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.Game + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldNumber + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldName + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamA + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamB + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.Referee + "</span></td>";
                    gameHtml += "</tr>";
                    gameHtml += "</tbody>";
                    gameHtml += "</table>";

                    gameHtml += part2Html;

                    if (md != cg.matchData[cg.matchData.Count - 1])
                        gameHtml += "<div style='page-break-after: always;'></div>";
                }

                gameHtml += footerHtml;

                var pdf = Pdf.From(gameHtml).OfSize(PaperSize.A4).Landscape().Comressed().Content();

                File.WriteAllBytes(pdfPath + "kreuzspiele.pdf", pdf);
            }
        }

        private void TextBoxCrossgames_TextChanged(object sender, EventArgs e)
        {
            (dataGridViewCrossgamesRound.DataSource as DataTable).DefaultView.RowFilter = string.Format("[Team A] LIKE '{0}%' OR [Team B] LIKE '{0}%' OR Schiedsrichter LIKE '{0}%'", textBoxCrossgamesFilter.Text);

            if ((dataGridViewCrossgamesRound.DataSource as DataTable).DefaultView.Count == cg.matchData.Count)
            {
                setRowColorsForEachRound(dataGridViewCrossgamesRound);
            }
        }
        #endregion
        #endregion

        #region classementgames
        #region data actions
        void initDataTableClassementgames()
        {
            dtClassementgames = new DataTable("dtClassementgames");
            dtClassementgames.Columns.Add("Spiel");
            dtClassementgames.Columns.Add("Runde");
            dtClassementgames.Columns.Add("Zeit");
            dtClassementgames.Columns.Add("Feldnr.");
            dtClassementgames.Columns.Add("Feldname");
            dtClassementgames.Columns.Add("Team A");
            dtClassementgames.Columns.Add("Team B");
            dtClassementgames.Columns.Add("Schiedsrichter");
            dtClassementgames.Columns.Add("Satz 1 A");
            dtClassementgames.Columns.Add("Satz 1 B");
            dtClassementgames.Columns.Add("Satz 2 A");
            dtClassementgames.Columns.Add("Satz 2 B");
            dtClassementgames.Columns.Add("Satz 3 A");
            dtClassementgames.Columns.Add("Satz 3 B");

            typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                dataGridViewClassementgamesRound,
                                                new object[] { true });

            dataGridViewClassementgamesRound.DataSource = dtClassementgames;

            foreach (DataGridViewColumn dgvc in dataGridViewClassementgamesRound.Columns)
                dgvc.SortMode = DataGridViewColumnSortMode.NotSortable;

            clg = new ClassementGames(log);

            loadDataClassementgamesFromFile();

            loadClassementgames();
        }

        void loadDataClassementgamesFromFile()
        {
            bool tmpMatchDataCountOK = false;

            if (settings.UseInterim)
            {
                log.write("use configuration from interim");

                if (ig.matchData.Count > 0)
                    tmpMatchDataCountOK = true;
            }
            else
            {
                log.write("use configuration from qualifying");

                if (qg.matchData.Count > 0)
                    tmpMatchDataCountOK = true;
            }

            if (clg != null && cg.matchData.Count > 0 && tmpMatchDataCountOK)
            {
                clg.matchData.Clear();

                clg.matchData = LoadMatchDataFromFile(classementgamesFileName);

                DateTime startTime = cg.matchData[cg.matchData.Count - 1].Time.AddSeconds(settings.SetsCrossgames * settings.MinutesPerSetCrossgame * 60);

                List<List<ResultData>> tmpResultData;
                
                if (settings.UseInterim)
                {
                    tmpResultData = ig.resultData;
                }
                else
                {
                    tmpResultData = qg.resultData;
                }

                clg.setParameters(tmpResultData,
                                    cg.matchData,
                                    startTime,
                                    settings.PauseBetweenCrossgamesClassement,
                                    settings.SetsClassement,
                                    settings.MinutesPerSetClassement,
                                    0,
                                    fieldNames.Count,
                                    countTeams(),
                                    fieldNames,
                                    cg.matchData[cg.matchData.Count - 1].Round + 1,
                                    cg.matchData[cg.matchData.Count - 1].Game + 1,
                                    settings.UseSecondGameplan); 

                clg.resultData.Clear();
            }
        }

        void loadClassementgames()
        {
            if (clg != null && clg.matchData.Count > 0)
            {
                foreach (MatchData md in clg.matchData)
                {
                    dtClassementgames.Rows.Add(new object[] { md.Game,
                                                        md.Round,
                                                        md.Time.ToString("HH:mm"),
                                                        md.FieldNumber,
                                                        md.FieldName,
                                                        md.TeamA,
                                                        md.TeamB,
                                                        md.Referee,
                                                        md.PointsMatch1TeamA,
                                                        md.PointsMatch1TeamB,
                                                        md.PointsMatch2TeamA,
                                                        md.PointsMatch2TeamB,
                                                        md.PointsMatch3TeamA,
                                                        md.PointsMatch3TeamB });
                }
            }
        }

        void saveClassementgames()
        {
            if (clg != null)
            {
                log.write("calculating classement results");

                SaveMatchDataToFile(classementgamesFileName, clg.matchData);

                if(clg.matchData.Count > 0)
                    clg.createFinalClassement();

                exportTournamentDataToDB();
            }
        }
        #endregion

        #region form actions
        private void dataGridViewClassementgamesRound_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!lockAction)
            {
                switch (e.ColumnIndex)
                {
                    case 2:
                        DateTime gameTime = DateTime.Parse(dtClassementgames.Rows[e.RowIndex][2].ToString());

                        clg.recalculateTimeSchedule(e.RowIndex, gameTime);

                        for (int i = 0; i < clg.matchData.Count; i++)
                            dtClassementgames.Rows[i][2] = clg.matchData[i].Time.ToString("HH:mm");

                        break;

                    case 8:
                        clg.matchData[e.RowIndex].PointsMatch1TeamA = int.Parse(dtClassementgames.Rows[e.RowIndex][8].ToString());
                        break;

                    case 9:
                        clg.matchData[e.RowIndex].PointsMatch1TeamB = int.Parse(dtClassementgames.Rows[e.RowIndex][9].ToString());
                        break;

                    case 10:
                        clg.matchData[e.RowIndex].PointsMatch2TeamA = int.Parse(dtClassementgames.Rows[e.RowIndex][10].ToString());
                        break;

                    case 11:
                        clg.matchData[e.RowIndex].PointsMatch2TeamB = int.Parse(dtClassementgames.Rows[e.RowIndex][11].ToString());
                        break;

                    case 12:
                        clg.matchData[e.RowIndex].PointsMatch3TeamA = int.Parse(dtClassementgames.Rows[e.RowIndex][12].ToString());
                        break;

                    case 13:
                        clg.matchData[e.RowIndex].PointsMatch3TeamB = int.Parse(dtClassementgames.Rows[e.RowIndex][13].ToString());
                        break;
                }
            }
        }

        private void buttonGenerateClassementgames_Click(object sender, EventArgs e)
        {
            lockAction = true;

            if (clg != null && cg.matchData.Count > 0 && clg.matchData.Count == 0)
            {
                log.write("generate classementgames");

                extractFieldnames();

                DateTime startTime = cg.matchData[cg.matchData.Count - 1].Time.AddSeconds(settings.SetsCrossgames * settings.MinutesPerSetCrossgame * 60);

                clg.setParameters(ig.resultData,
                                cg.matchData,
                                startTime,
                                settings.PauseBetweenCrossgamesClassement,
                                settings.SetsClassement,
                                settings.MinutesPerSetClassement,
                                0,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                cg.matchData[cg.matchData.Count - 1].Round + 1,
                                cg.matchData[cg.matchData.Count - 1].Game + 1,
                                settings.UseSecondGameplan);

                clg.generateGames();

                loadClassementgames();

                saveClassementgames();

                setRowColorsForEachRound(dataGridViewClassementgamesRound);
            }
            else
            {
                MessageBox.Show("Spiele sind schon vorhanden, generieren abgebrochen!", "Achtung!", MessageBoxButtons.OK);
            }

            lockAction = false;
        }

        private void buttonSaveClassementgames_Click(object sender, EventArgs e)
        {
            saveClassementgames();
        }

        private void buttonClearClassementgames_Click(object sender, EventArgs e)
        {
            if (clg != null)
            {
                clg.matchData.Clear();

                dtClassementgames.Clear();

                saveClassementgames();
            }
        }

        private void buttonPrintClassementgames_Click(object sender, EventArgs e)
        {
            if (clg != null && clg.matchData.Count > 0)
            {
                String gameHtml = headerHtml;

                foreach (MatchData md in clg.matchData)
                {
                    gameHtml += part1Html;

                    gameHtml += "<tr>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.Game + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 10%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldNumber + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.FieldName + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamA + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.TeamB + "</span></td>";
                    gameHtml += "<td style='font-family: Arial, Helvetica, sans-serif; border: 1px solid black; width: 20%; text-align: center;'><span style='font-size: 30px;'>" + md.Referee + "</span></td>";
                    gameHtml += "</tr>";
                    gameHtml += "</tbody>";
                    gameHtml += "</table>";

                    gameHtml += part2Html;

                    if (md != clg.matchData[clg.matchData.Count - 1])
                        gameHtml += "<div style='page-break-after: always;'></div>";
                }

                gameHtml += footerHtml;

                var pdf = Pdf.From(gameHtml).OfSize(PaperSize.A4).Landscape().Comressed().Content();

                File.WriteAllBytes(pdfPath + "platzspiele.pdf", pdf);
            }
        }

        private void TextBoxClassementgames_TextChanged(object sender, EventArgs e)
        {
            (dataGridViewClassementgamesRound.DataSource as DataTable).DefaultView.RowFilter = string.Format("[Team A] LIKE '{0}%' OR [Team B] LIKE '{0}%' OR Schiedsrichter LIKE '{0}%'", textBoxClassementgamesFilter.Text);

            if ((dataGridViewClassementgamesRound.DataSource as DataTable).DefaultView.Count == clg.matchData.Count)
            {
                setRowColorsForEachRound(dataGridViewClassementgamesRound);
            }
        }
        #endregion
        #endregion
    }
}
