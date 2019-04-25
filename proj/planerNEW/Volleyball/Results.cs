using System;
using System.Collections.Generic;
using System.Data;
using System.Reflection;
using System.Windows.Forms;

namespace Volleyball
{
    public partial class Results : Form
    {
        #region members
        static readonly List<String> resultPrefix = new List<String>() { "Platz", "Mannschaft", "Punkte", "Spielpunkte", "Intern", "Extern" };
        List<DataTable> resultTables = new List<DataTable>();
        List<DataGridView> resultViews = new List<DataGridView>();
        Object roundObject;
        #endregion

        public Results(Object roundObject)
        {
            InitializeComponent();

            this.roundObject = roundObject;
            
            init();

            initData();
        }

        void init()
        {
            resultViews.Add(dataGridViewA);
            resultViews.Add(dataGridViewB);
            resultViews.Add(dataGridViewC);
            resultViews.Add(dataGridViewD);
            resultViews.Add(dataGridViewE);
            resultViews.Add(dataGridViewF);
            resultViews.Add(dataGridViewG);
            resultViews.Add(dataGridViewH);
            resultViews.Add(dataGridViewI);
            resultViews.Add(dataGridViewJ);
            resultViews.Add(dataGridViewK);
            resultViews.Add(dataGridViewL);

            for (int i = 0; i < resultViews.Count; i++)
            {
                typeof(DataGridView).InvokeMember("DoubleBuffered",
                                                BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty,
                                                null,
                                                resultViews[i],
                                                new object[] { true });

                DataTable dt = new DataTable();

                for (int ii = 0; ii < resultPrefix.Count; ii++)
                    dt.Columns.Add(resultPrefix[ii]);

                resultViews[i].DataSource = dt;

                resultTables.Add(dt);
            }
        }

        void initData()
        {
            if (roundObject is QualifyingGames)
            {
                QualifyingGames qg = (QualifyingGames)roundObject;

                for (int i = 0; i < qg.resultData.Count; i++)
                {
                    List<ResultData> rdList = qg.resultData[i];

                    foreach (ResultData rd in rdList)
                    {
                        resultTables[i].Rows.Add(new object[] { rd.Rank,
                                                            rd.Team,
                                                            rd.PointsSets,
                                                            rd.PointsMatches,
                                                            rd.InternalRank,
                                                            rd.ExternalRank });
                    }
                }
            }
        }

        private void dataGridViews_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            for(int i = 0; i < resultViews.Count; i++)
            {
                if(((DataGridView)sender).Name == resultViews[i].Name)
                {
                    switch (e.ColumnIndex)
                    {
                        case 2:
                            int internalRank = int.Parse(resultTables[i].Rows[e.RowIndex].ToString());

                            if(roundObject is QualifyingGames)
                            {
                                QualifyingGames qg = (QualifyingGames)roundObject;

                                qg.resultData[i][e.RowIndex].InternalRank = internalRank;
                            }
                            break;

                        case 3:
                            int externalRank = int.Parse(resultTables[i].Rows[e.RowIndex].ToString());

                            if (roundObject is QualifyingGames)
                            {
                                QualifyingGames qg = (QualifyingGames)roundObject;

                                qg.resultData[i][e.RowIndex].ExternalRank = externalRank;
                            }
                            break;
                    }
                    break;
                }
            }
        }
    }
}
