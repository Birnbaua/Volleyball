using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Reporting.WinForms;
using System.IO;
using System.Diagnostics;

namespace vbtournamentreporter
{
    public partial class reporter : Form
    {
        public reporter()
        {
            try
            {
                InitializeComponent();
            }
            catch (System.IO.FileNotFoundException e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void reporter_Load(object sender, EventArgs e)
        {
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_gra_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_gra_viewTableAdapter.Fill(this.tables.zwischenrunde_gra_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grb_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grb_viewTableAdapter.Fill(this.tables.zwischenrunde_grb_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grc_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grc_viewTableAdapter.Fill(this.tables.zwischenrunde_grc_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grd_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grd_viewTableAdapter.Fill(this.tables.zwischenrunde_grd_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_gre_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_gre_viewTableAdapter.Fill(this.tables.zwischenrunde_gre_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grf_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grf_viewTableAdapter.Fill(this.tables.zwischenrunde_grf_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grg_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grg_viewTableAdapter.Fill(this.tables.zwischenrunde_grg_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_grh_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_grh_viewTableAdapter.Fill(this.tables.zwischenrunde_grh_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.platzierungen_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.platzierungen_viewTableAdapter.Fill(this.tables.platzierungen_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.platzspiele_spielplan". Sie können sie bei Bedarf verschieben oder entfernen.
            this.platzspiele_spielplanTableAdapter.Fill(this.tables.platzspiele_spielplan);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.kreuzspiele_spielplan". Sie können sie bei Bedarf verschieben oder entfernen.
            this.kreuzspiele_spielplanTableAdapter.Fill(this.tables.kreuzspiele_spielplan);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.zwischenrunde_spielplan". Sie können sie bei Bedarf verschieben oder entfernen.
            this.zwischenrunde_spielplanTableAdapter.Fill(this.tables.zwischenrunde_spielplan);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_gra_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_gra_viewTableAdapter.Fill(this.tables.vorrunde_gra_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grb_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grb_viewTableAdapter.Fill(this.tables.vorrunde_grb_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grc_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grc_viewTableAdapter.Fill(this.tables.vorrunde_grc_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grd_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grd_viewTableAdapter.Fill(this.tables.vorrunde_grd_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_gre_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_gre_viewTableAdapter.Fill(this.tables.vorrunde_gre_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grf_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grf_viewTableAdapter.Fill(this.tables.vorrunde_grf_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grg_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grg_viewTableAdapter.Fill(this.tables.vorrunde_grg_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_grh_view". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_grh_viewTableAdapter.Fill(this.tables.vorrunde_grh_view);
            // TODO: Diese Codezeile lädt Daten in die Tabelle "tables.vorrunde_spielplan". Sie können sie bei Bedarf verschieben oder entfernen.
            this.vorrunde_spielplanTableAdapter.Fill(this.tables.vorrunde_spielplan);
            this.reportViewerVS.RefreshReport();
            this.reportViewerVR.RefreshReport();
            this.reportViewerZS.RefreshReport();
            this.reportViewerZR.RefreshReport();
            this.reportViewerKS.RefreshReport();
            this.reportViewerPS.RefreshReport();
            this.reportViewerPR.RefreshReport();
        }
    }
}
