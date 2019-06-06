using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using System.Data;
using System.Reflection;
using System.Drawing;

namespace Volleyball
{
    public partial class FormMain : Form
    {
        #region members
        static readonly String settingsFileName = "settings.csv";
        static readonly String fieldsFileName = "fields.csv";
        static readonly String teamsFileName = "teams.csv";
        static readonly String qualifyingFileName = "qualifyinggames.csv", qualifyingResultFileName = "qualifying_result";
        static readonly String interimFileName = "interimgames.csv", interimResultFileName = "interim_results";
        static readonly String crossgamesFileName = "crossgames.csv";
        static readonly String classementgamesFileName = "classementgames.csv";
        static readonly List<String> prefix = new List<String>() { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
        static bool lockAction = false;
        static readonly List<Color> rowColors = new List<Color>() { Color.Yellow, Color.LightGray, Color.Cyan, Color.Magenta };
        Settings settings;
        DataTable dtFields, dtTeams, dtQualifying, dtInterim, dtCrossgames;
        QualifyingGames qg;
        InterimGames ig;
        CrossGames cg;
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
                                                   new int[]{ 0, 1, 4 }};
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

            checkBoxUseCrossgames_CheckedChanged(checkBoxUseCrossgames, EventArgs.Empty);
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

        #region general ui methods
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
                setRowColorsForEachRound(dataGridViewQualifyingRound);
            }
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
                    settings.PauseAfterFinals = Convert.ToInt32(fieldArray[16]);
                    settings.UseCrossgames = Convert.ToBoolean(fieldArray[17]);
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
                            settings.PauseAfterFinals + ";" +
                            settings.UseCrossgames);
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
            settings.PauseAfterFinals = 0;
            settings.UseCrossgames = true;

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

            if(settings.UseCrossgames)
            {
                checkBoxUseCrossgames.Checked = true;
            }
            else
            {
                checkBoxUseCrossgames.Checked = false;
            }

            numericUpDownPauseBetweenCrossgamesClassement.Value = settings.PauseBetweenCrossgamesClassement;

            numericUpDownClassementSets.Value = settings.SetsClassement;
            numericUpDownClassementMinutesPerSet.Value = settings.MinutesPerSetClassement;
            numericUpDownTimeForFinals.Value = settings.MinutesForFinals;
            numericUpDownPauseAfterFinal.Value = settings.PauseAfterFinals;
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

            settings.UseCrossgames = checkBoxUseCrossgames.Checked;

            settings.PauseBetweenCrossgamesClassement = Convert.ToInt32(numericUpDownPauseBetweenCrossgamesClassement.Value);

            settings.SetsClassement = Convert.ToInt32(numericUpDownClassementSets.Value);
            settings.MinutesPerSetClassement = Convert.ToInt32(numericUpDownClassementMinutesPerSet.Value);
            settings.MinutesForFinals = Convert.ToInt32(numericUpDownTimeForFinals.Value);
            settings.PauseAfterFinals = Convert.ToInt32(numericUpDownPauseAfterFinal.Value);

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

        private void checkBoxUseCrossgames_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxUseCrossgames.Checked)
            {
                numericUpDownCrossgamesSets.Enabled = true;
                numericUpDownCrossgamesMinutesPerSet.Enabled = true;
                numericUpDownCrossgamesPauseBetweenSets.Enabled = true;
            }
            else
            {
                numericUpDownCrossgamesSets.Enabled = false;
                numericUpDownCrossgamesMinutesPerSet.Enabled = false;
                numericUpDownCrossgamesPauseBetweenSets.Enabled = false;
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

            loadFields();

            if (dtFields.Rows.Count == 0)
            {
                dtFields.Rows.Add(new object[] { "1", "" });
                numericUpDownFields.Value = dtFields.Rows.Count;
                writeFieldsToFile();
            }
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
                for(int ii = 0; ii < dtTeams.Columns.Count; ii++)
                    count++;
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

                for (int i = 0; i < qg.resultData.Count; i++)
                {
                    if(qg.resultData[i].Count > 0)
                        SaveResultDataToFile(qualifyingResultFileName + "_" + prefix[i] + ".csv", qg.resultData[i]);
                }
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

            if (qg != null)
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

            ig = new InterimGames(log);

            loadDataInterimFromFile();

            loadInterim();
        }

        void loadDataInterimFromFile()
        {
            ig.matchData.Clear();

            ig.matchData = LoadMatchDataFromFile(interimFileName);

            ig.setParameters(qg.resultData,
                                gamePlan,
                                qg.matchData[qg.matchData.Count - 1].Time,
                                settings.PauseBetweenQualifyingInterim,
                                settings.SetsInterim,
                                settings.MinutesPerSetInterim,
                                settings.PausePerSetInterim,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                qg.matchData[qg.matchData.Count - 1].Round + 1,
                                qg.matchData[qg.matchData.Count - 1].Game + 1,
                                true); //TODO!!!

            ig.resultData.Clear();

            for (int i = 0; i < prefix.Count; i++)
                ig.resultData.Add(LoadResultDataFromFile(interimResultFileName + "_" + prefix[i] + ".csv"));
        }

        void loadInterim()
        {
            if (ig != null)
            {
                if (ig.matchData.Count > 0)
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
        }

        void saveInterim()
        {
            if (ig != null)
            {
                log.write("calculating interim results");

                ig.calculateResults();

                ig.sortResults();

                SaveMatchDataToFile(interimFileName, ig.matchData);

                for (int i = 0; i < ig.resultData.Count; i++)
                {
                    if (ig.resultData[i].Count > 0)
                        SaveResultDataToFile(interimResultFileName + "_" + prefix[i] + ".csv", ig.resultData[i]);
                }
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

            if (doubleResults.Count == 0 && ig != null)
            {
                log.write("generate interim games");

                ig.setParameters(qg.resultData,
                                gamePlan,
                                qg.matchData[qg.matchData.Count].Time,
                                settings.PauseBetweenQualifyingInterim,
                                settings.SetsInterim,
                                settings.MinutesPerSetInterim,
                                settings.PausePerSetInterim,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                qg.matchData[qg.matchData.Count].Round + 1,
                                qg.matchData[qg.matchData.Count].Game + 1,
                                true); //TODO!!! => welcher spielplan wird gewählt mit 50+ teams

                ig.generateGames();

                loadInterim();

                saveInterim();

                setRowColorsForEachRound(dataGridViewInterimRound);
            }
            else
            {
                MessageBox.Show("Achtung gleiche Punktestände gefunden! '" + doubleResults[0] + "' = '" + doubleResults[1] + "'! Zwischenrunde wird NICHT generiert!");
                log.write("found double team results " + doubleResults[0] + " = " + doubleResults[1]);
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

                loadInterim();
            }
        }

        private void buttonPrintInterim_Click(object sender, EventArgs e)
        {

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
            (dataGridViewInterimRound.DataSource as DataTable).DefaultView.RowFilter = string.Format("[Team A] LIKE '{0}%' OR [Team B] LIKE '{0}%' OR Schiedsrichter LIKE '{0}%'", textBoxQualifyingFilter.Text);

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

            dataGridViewCrossgamesRound.DataSource = dtInterim;

            cg = new CrossGames(log);

            loadDataCrossgamesFromFile();

            loadCrossgames();
        }

        void loadDataCrossgamesFromFile()
        {
            cg.matchData.Clear();

            cg.matchData = LoadMatchDataFromFile(crossgamesFileName);

            cg.setParameters(ig.resultData,
                                ig.matchData[ig.matchData.Count - 1].Time,
                                settings.PauseBetweenInterimCrossgames,
                                settings.SetsCrossgames,
                                settings.MinutesPerSetCrossgame,
                                settings.PausePerSetCrossgame,
                                fieldNames.Count,
                                countTeams(),
                                fieldNames,
                                ig.matchData[ig.matchData.Count - 1].Round + 1,
                                ig.matchData[ig.matchData.Count - 1].Game + 1,
                                true); //TODO!!!

            cg.resultData.Clear();
        }

        void loadCrossgames()
        {
            if (cg != null)
            {
                if (cg.matchData.Count > 0)
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
        }

        void saveCrossgames()
        {
            if (cg != null)
            {
                log.write("calculating crossgame results");

                cg.calculateResults();

                cg.sortResults();

                SaveMatchDataToFile(crossgamesFileName, cg.matchData);
            }
        }
        #endregion

        #region form actions
        #endregion
        #endregion
    }
}
