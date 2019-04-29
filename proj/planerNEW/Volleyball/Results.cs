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

        public delegate void SaveChanges();
        public event SaveChanges saveChangesEvent;
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
                        case 4:
                            int internalRank = int.Parse(resultTables[i].Rows[e.RowIndex][4].ToString());

                            if(roundObject is QualifyingGames)
                            {
                                QualifyingGames qg = (QualifyingGames)roundObject;

                                qg.resultData[i][e.RowIndex].InternalRank = internalRank;

                                saveChangesEvent?.Invoke();
                            }
                            break;

                        case 5:
                            int externalRank = int.Parse(resultTables[i].Rows[e.RowIndex][5].ToString());

                            if (roundObject is QualifyingGames)
                            {
                                QualifyingGames qg = (QualifyingGames)roundObject;

                                qg.resultData[i][e.RowIndex].ExternalRank = externalRank;

                                saveChangesEvent?.Invoke();
                            }
                            break;
                    }
                    break;
                }
            }
        }

        private void Results_Resize(object sender, EventArgs e)
        {
            int formHeightDrittel = ( this.Size.Height - 30 ) / 3;

            foreach(Object obj in this.Controls)
            {
                if( obj is Panel )
                {
                    Panel pan = (Panel)obj;
                    pan.Height = formHeightDrittel;

                    int panWidthDrittel = pan.Size.Width / 3;

                    foreach (Object subObj in pan.Controls)
                    {
                        if( subObj is GroupBox )
                            ((GroupBox)subObj).Width = panWidthDrittel;
                    }
                }
            }
        }
    }
}
