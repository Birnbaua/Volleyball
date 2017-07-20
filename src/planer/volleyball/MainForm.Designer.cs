/*
 * Created by SharpDevelop.
 * User: Feizlch
 * Date: 15.05.2017
 * Time: 10:43
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace volleyball
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.StatusStrip statusStripTournamentTime;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelZeitDescr;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabelZeit;
		private System.Windows.Forms.DataGridView dataGridViewTeams;
		private System.Windows.Forms.Button buttonSaveTeams;
		private System.Windows.Forms.Button buttonClearTeams;
		private System.Windows.Forms.TabControl tabControl;
		private System.Windows.Forms.TabPage tabPageTeamsTime;
		private System.Windows.Forms.TabPage tabPageQualifying;
		private System.Windows.Forms.TabPage tabPageInterim;
		private System.Windows.Forms.TabPage tabPageCrossgames;
		private System.Windows.Forms.TabPage tabPageClassement;
		private System.Windows.Forms.MenuStrip menuStrip;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
		private System.Windows.Forms.DataGridView dataGridViewQualifying;
		private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.GroupBox groupBoxTeams;
		private System.Windows.Forms.Button buttonQfPrint;
		private System.Windows.Forms.Button buttonQfDelete;
		private System.Windows.Forms.Button buttonQfSave;
		private System.Windows.Forms.Button buttonQfGenerate;
		private System.Windows.Forms.Button buttonInPrint;
		private System.Windows.Forms.Button buttonInResults;
		private System.Windows.Forms.Button buttonInDelete;
		private System.Windows.Forms.Button buttonInSave;
		private System.Windows.Forms.Button buttonInGenerate;
		private System.Windows.Forms.DataGridView dataGridViewInterim;
		private System.Windows.Forms.Button buttonPreClPrint;
		private System.Windows.Forms.Button buttonPreClDelete;
		private System.Windows.Forms.Button buttonPreClSave;
		private System.Windows.Forms.DataGridView dataGridViewPreClassement;
		private System.Windows.Forms.Button buttonClPrint;
		private System.Windows.Forms.Button buttonClResult;
		private System.Windows.Forms.Button buttonClDelete;
		private System.Windows.Forms.Button buttonClSave;
		private System.Windows.Forms.Button buttonClGenerate;
		private System.Windows.Forms.DataGridView dataGridViewClassement;
		private System.Windows.Forms.Button buttonQfOverallResults;
		private System.Windows.Forms.Button buttonQfResults;
		private System.Windows.Forms.Button buttonPreClGenerate;
		private System.Windows.Forms.GroupBox groupBoxFields;
		private System.Windows.Forms.DataGridView dataGridViewFields;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.NumericUpDown numericUpDownFieldCount;
		private System.Windows.Forms.ToolStripMenuItem dokumentationToolStripMenuItem;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.statusStripTournamentTime = new System.Windows.Forms.StatusStrip();
			this.toolStripStatusLabelZeitDescr = new System.Windows.Forms.ToolStripStatusLabel();
			this.toolStripStatusLabelZeit = new System.Windows.Forms.ToolStripStatusLabel();
			this.dataGridViewTeams = new System.Windows.Forms.DataGridView();
			this.buttonSaveTeams = new System.Windows.Forms.Button();
			this.buttonClearTeams = new System.Windows.Forms.Button();
			this.tabControl = new System.Windows.Forms.TabControl();
			this.tabPageTeamsTime = new System.Windows.Forms.TabPage();
			this.groupBoxFields = new System.Windows.Forms.GroupBox();
			this.numericUpDownFieldCount = new System.Windows.Forms.NumericUpDown();
			this.label1 = new System.Windows.Forms.Label();
			this.dataGridViewFields = new System.Windows.Forms.DataGridView();
			this.groupBoxTeams = new System.Windows.Forms.GroupBox();
			this.tabPageQualifying = new System.Windows.Forms.TabPage();
			this.buttonQfOverallResults = new System.Windows.Forms.Button();
			this.buttonQfPrint = new System.Windows.Forms.Button();
			this.buttonQfResults = new System.Windows.Forms.Button();
			this.buttonQfDelete = new System.Windows.Forms.Button();
			this.buttonQfSave = new System.Windows.Forms.Button();
			this.buttonQfGenerate = new System.Windows.Forms.Button();
			this.dataGridViewQualifying = new System.Windows.Forms.DataGridView();
			this.tabPageInterim = new System.Windows.Forms.TabPage();
			this.buttonInPrint = new System.Windows.Forms.Button();
			this.buttonInResults = new System.Windows.Forms.Button();
			this.buttonInDelete = new System.Windows.Forms.Button();
			this.buttonInSave = new System.Windows.Forms.Button();
			this.buttonInGenerate = new System.Windows.Forms.Button();
			this.dataGridViewInterim = new System.Windows.Forms.DataGridView();
			this.tabPageCrossgames = new System.Windows.Forms.TabPage();
			this.buttonPreClPrint = new System.Windows.Forms.Button();
			this.buttonPreClDelete = new System.Windows.Forms.Button();
			this.buttonPreClSave = new System.Windows.Forms.Button();
			this.buttonPreClGenerate = new System.Windows.Forms.Button();
			this.dataGridViewPreClassement = new System.Windows.Forms.DataGridView();
			this.tabPageClassement = new System.Windows.Forms.TabPage();
			this.buttonClPrint = new System.Windows.Forms.Button();
			this.buttonClResult = new System.Windows.Forms.Button();
			this.buttonClDelete = new System.Windows.Forms.Button();
			this.buttonClSave = new System.Windows.Forms.Button();
			this.buttonClGenerate = new System.Windows.Forms.Button();
			this.dataGridViewClassement = new System.Windows.Forms.DataGridView();
			this.menuStrip = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.dokumentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStripTournamentTime.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).BeginInit();
			this.tabControl.SuspendLayout();
			this.tabPageTeamsTime.SuspendLayout();
			this.groupBoxFields.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownFieldCount)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewFields)).BeginInit();
			this.groupBoxTeams.SuspendLayout();
			this.tabPageQualifying.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewQualifying)).BeginInit();
			this.tabPageInterim.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewInterim)).BeginInit();
			this.tabPageCrossgames.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewPreClassement)).BeginInit();
			this.tabPageClassement.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewClassement)).BeginInit();
			this.menuStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// statusStripTournamentTime
			// 
			this.statusStripTournamentTime.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
			this.toolStripStatusLabelZeitDescr,
			this.toolStripStatusLabelZeit});
			this.statusStripTournamentTime.Location = new System.Drawing.Point(0, 746);
			this.statusStripTournamentTime.Name = "statusStripTournamentTime";
			this.statusStripTournamentTime.Size = new System.Drawing.Size(1164, 22);
			this.statusStripTournamentTime.TabIndex = 0;
			this.statusStripTournamentTime.Text = "statusStrip1";
			// 
			// toolStripStatusLabelZeitDescr
			// 
			this.toolStripStatusLabelZeitDescr.Name = "toolStripStatusLabelZeitDescr";
			this.toolStripStatusLabelZeitDescr.Size = new System.Drawing.Size(168, 17);
			this.toolStripStatusLabelZeitDescr.Text = "vorraussichtliches Turnierende";
			// 
			// toolStripStatusLabelZeit
			// 
			this.toolStripStatusLabelZeit.Name = "toolStripStatusLabelZeit";
			this.toolStripStatusLabelZeit.Size = new System.Drawing.Size(34, 17);
			this.toolStripStatusLabelZeit.Text = "00:00";
			// 
			// dataGridViewTeams
			// 
			this.dataGridViewTeams.AllowUserToAddRows = false;
			this.dataGridViewTeams.AllowUserToDeleteRows = false;
			this.dataGridViewTeams.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewTeams.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewTeams.Location = new System.Drawing.Point(6, 48);
			this.dataGridViewTeams.MultiSelect = false;
			this.dataGridViewTeams.Name = "dataGridViewTeams";
			this.dataGridViewTeams.Size = new System.Drawing.Size(1138, 178);
			this.dataGridViewTeams.TabIndex = 1;
			// 
			// buttonSaveTeams
			// 
			this.buttonSaveTeams.Location = new System.Drawing.Point(6, 19);
			this.buttonSaveTeams.Name = "buttonSaveTeams";
			this.buttonSaveTeams.Size = new System.Drawing.Size(92, 23);
			this.buttonSaveTeams.TabIndex = 2;
			this.buttonSaveTeams.Text = "Speichern";
			this.buttonSaveTeams.UseVisualStyleBackColor = true;
			this.buttonSaveTeams.Click += new System.EventHandler(this.ButtonTeamsSaveClick);
			// 
			// buttonClearTeams
			// 
			this.buttonClearTeams.Location = new System.Drawing.Point(104, 19);
			this.buttonClearTeams.Name = "buttonClearTeams";
			this.buttonClearTeams.Size = new System.Drawing.Size(92, 23);
			this.buttonClearTeams.TabIndex = 3;
			this.buttonClearTeams.Text = "Löschen";
			this.buttonClearTeams.UseVisualStyleBackColor = true;
			this.buttonClearTeams.Click += new System.EventHandler(this.ButtonClearTeamsClick);
			// 
			// tabControl
			// 
			this.tabControl.Controls.Add(this.tabPageTeamsTime);
			this.tabControl.Controls.Add(this.tabPageQualifying);
			this.tabControl.Controls.Add(this.tabPageInterim);
			this.tabControl.Controls.Add(this.tabPageCrossgames);
			this.tabControl.Controls.Add(this.tabPageClassement);
			this.tabControl.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl.Location = new System.Drawing.Point(0, 24);
			this.tabControl.Name = "tabControl";
			this.tabControl.SelectedIndex = 0;
			this.tabControl.Size = new System.Drawing.Size(1164, 722);
			this.tabControl.TabIndex = 4;
			// 
			// tabPageTeamsTime
			// 
			this.tabPageTeamsTime.Controls.Add(this.groupBoxFields);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTeams);
			this.tabPageTeamsTime.Location = new System.Drawing.Point(4, 22);
			this.tabPageTeamsTime.Name = "tabPageTeamsTime";
			this.tabPageTeamsTime.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageTeamsTime.Size = new System.Drawing.Size(1156, 696);
			this.tabPageTeamsTime.TabIndex = 0;
			this.tabPageTeamsTime.Text = "Mannschaften/Zeitplan";
			this.tabPageTeamsTime.UseVisualStyleBackColor = true;
			// 
			// groupBoxFields
			// 
			this.groupBoxFields.Controls.Add(this.numericUpDownFieldCount);
			this.groupBoxFields.Controls.Add(this.label1);
			this.groupBoxFields.Controls.Add(this.dataGridViewFields);
			this.groupBoxFields.Dock = System.Windows.Forms.DockStyle.Right;
			this.groupBoxFields.Location = new System.Drawing.Point(853, 3);
			this.groupBoxFields.Name = "groupBoxFields";
			this.groupBoxFields.Size = new System.Drawing.Size(300, 458);
			this.groupBoxFields.TabIndex = 5;
			this.groupBoxFields.TabStop = false;
			this.groupBoxFields.Text = "Felder";
			// 
			// numericUpDownFieldCount
			// 
			this.numericUpDownFieldCount.Location = new System.Drawing.Point(6, 19);
			this.numericUpDownFieldCount.Maximum = new decimal(new int[] {
			20,
			0,
			0,
			0});
			this.numericUpDownFieldCount.Minimum = new decimal(new int[] {
			1,
			0,
			0,
			0});
			this.numericUpDownFieldCount.Name = "numericUpDownFieldCount";
			this.numericUpDownFieldCount.Size = new System.Drawing.Size(61, 20);
			this.numericUpDownFieldCount.TabIndex = 3;
			this.numericUpDownFieldCount.Value = new decimal(new int[] {
			1,
			0,
			0,
			0});
			this.numericUpDownFieldCount.ValueChanged += new System.EventHandler(this.NumericUpDownFieldCountValueChanged);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(73, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(100, 23);
			this.label1.TabIndex = 2;
			this.label1.Text = "Anzahl Spielfelder";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// dataGridViewFields
			// 
			this.dataGridViewFields.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewFields.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewFields.Location = new System.Drawing.Point(6, 45);
			this.dataGridViewFields.Name = "dataGridViewFields";
			this.dataGridViewFields.Size = new System.Drawing.Size(288, 407);
			this.dataGridViewFields.TabIndex = 1;
			// 
			// groupBoxTeams
			// 
			this.groupBoxTeams.Controls.Add(this.dataGridViewTeams);
			this.groupBoxTeams.Controls.Add(this.buttonClearTeams);
			this.groupBoxTeams.Controls.Add(this.buttonSaveTeams);
			this.groupBoxTeams.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBoxTeams.Location = new System.Drawing.Point(3, 461);
			this.groupBoxTeams.Name = "groupBoxTeams";
			this.groupBoxTeams.Size = new System.Drawing.Size(1150, 232);
			this.groupBoxTeams.TabIndex = 4;
			this.groupBoxTeams.TabStop = false;
			this.groupBoxTeams.Text = "Teams";
			// 
			// tabPageQualifying
			// 
			this.tabPageQualifying.Controls.Add(this.buttonQfOverallResults);
			this.tabPageQualifying.Controls.Add(this.buttonQfPrint);
			this.tabPageQualifying.Controls.Add(this.buttonQfResults);
			this.tabPageQualifying.Controls.Add(this.buttonQfDelete);
			this.tabPageQualifying.Controls.Add(this.buttonQfSave);
			this.tabPageQualifying.Controls.Add(this.buttonQfGenerate);
			this.tabPageQualifying.Controls.Add(this.dataGridViewQualifying);
			this.tabPageQualifying.Location = new System.Drawing.Point(4, 22);
			this.tabPageQualifying.Name = "tabPageQualifying";
			this.tabPageQualifying.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageQualifying.Size = new System.Drawing.Size(1156, 696);
			this.tabPageQualifying.TabIndex = 1;
			this.tabPageQualifying.Text = "Vorrunde";
			this.tabPageQualifying.UseVisualStyleBackColor = true;
			// 
			// buttonQfOverallResults
			// 
			this.buttonQfOverallResults.Location = new System.Drawing.Point(1061, 5);
			this.buttonQfOverallResults.Name = "buttonQfOverallResults";
			this.buttonQfOverallResults.Size = new System.Drawing.Size(92, 23);
			this.buttonQfOverallResults.TabIndex = 9;
			this.buttonQfOverallResults.Text = "Gesamtreihung";
			this.buttonQfOverallResults.UseVisualStyleBackColor = true;
			this.buttonQfOverallResults.Click += new System.EventHandler(this.ButtonQfOverallResultsClick);
			// 
			// buttonQfPrint
			// 
			this.buttonQfPrint.Location = new System.Drawing.Point(300, 5);
			this.buttonQfPrint.Name = "buttonQfPrint";
			this.buttonQfPrint.Size = new System.Drawing.Size(92, 23);
			this.buttonQfPrint.TabIndex = 8;
			this.buttonQfPrint.Text = "Drucken";
			this.buttonQfPrint.UseVisualStyleBackColor = true;
			this.buttonQfPrint.Click += new System.EventHandler(this.ButtonQfPrintClick);
			// 
			// buttonQfResults
			// 
			this.buttonQfResults.Location = new System.Drawing.Point(944, 5);
			this.buttonQfResults.Name = "buttonQfResults";
			this.buttonQfResults.Size = new System.Drawing.Size(111, 23);
			this.buttonQfResults.TabIndex = 7;
			this.buttonQfResults.Text = "Ergebnisse";
			this.buttonQfResults.UseVisualStyleBackColor = true;
			this.buttonQfResults.Click += new System.EventHandler(this.ButtonQfResultsClick);
			// 
			// buttonQfDelete
			// 
			this.buttonQfDelete.Location = new System.Drawing.Point(202, 5);
			this.buttonQfDelete.Name = "buttonQfDelete";
			this.buttonQfDelete.Size = new System.Drawing.Size(92, 23);
			this.buttonQfDelete.TabIndex = 6;
			this.buttonQfDelete.Text = "Löschen";
			this.buttonQfDelete.UseVisualStyleBackColor = true;
			this.buttonQfDelete.Click += new System.EventHandler(this.ButtonQfDeleteClick);
			// 
			// buttonQfSave
			// 
			this.buttonQfSave.Location = new System.Drawing.Point(104, 5);
			this.buttonQfSave.Name = "buttonQfSave";
			this.buttonQfSave.Size = new System.Drawing.Size(92, 23);
			this.buttonQfSave.TabIndex = 5;
			this.buttonQfSave.Text = "Speichern";
			this.buttonQfSave.UseVisualStyleBackColor = true;
			this.buttonQfSave.Click += new System.EventHandler(this.ButtonQfSaveClick);
			// 
			// buttonQfGenerate
			// 
			this.buttonQfGenerate.Location = new System.Drawing.Point(6, 5);
			this.buttonQfGenerate.Name = "buttonQfGenerate";
			this.buttonQfGenerate.Size = new System.Drawing.Size(92, 23);
			this.buttonQfGenerate.TabIndex = 4;
			this.buttonQfGenerate.Text = "Generieren";
			this.buttonQfGenerate.UseVisualStyleBackColor = true;
			this.buttonQfGenerate.Click += new System.EventHandler(this.ButtonQfGenerateClick);
			// 
			// dataGridViewQualifying
			// 
			this.dataGridViewQualifying.AllowUserToAddRows = false;
			this.dataGridViewQualifying.AllowUserToDeleteRows = false;
			this.dataGridViewQualifying.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewQualifying.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewQualifying.Location = new System.Drawing.Point(3, 34);
			this.dataGridViewQualifying.MultiSelect = false;
			this.dataGridViewQualifying.Name = "dataGridViewQualifying";
			this.dataGridViewQualifying.Size = new System.Drawing.Size(1150, 659);
			this.dataGridViewQualifying.TabIndex = 2;
			this.dataGridViewQualifying.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewQualifyingCellValueChanged);
			// 
			// tabPageInterim
			// 
			this.tabPageInterim.Controls.Add(this.buttonInPrint);
			this.tabPageInterim.Controls.Add(this.buttonInResults);
			this.tabPageInterim.Controls.Add(this.buttonInDelete);
			this.tabPageInterim.Controls.Add(this.buttonInSave);
			this.tabPageInterim.Controls.Add(this.buttonInGenerate);
			this.tabPageInterim.Controls.Add(this.dataGridViewInterim);
			this.tabPageInterim.Location = new System.Drawing.Point(4, 22);
			this.tabPageInterim.Name = "tabPageInterim";
			this.tabPageInterim.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageInterim.Size = new System.Drawing.Size(1156, 696);
			this.tabPageInterim.TabIndex = 2;
			this.tabPageInterim.Text = "Zwischenrunde";
			this.tabPageInterim.UseVisualStyleBackColor = true;
			// 
			// buttonInPrint
			// 
			this.buttonInPrint.Location = new System.Drawing.Point(300, 5);
			this.buttonInPrint.Name = "buttonInPrint";
			this.buttonInPrint.Size = new System.Drawing.Size(92, 23);
			this.buttonInPrint.TabIndex = 14;
			this.buttonInPrint.Text = "Drucken";
			this.buttonInPrint.UseVisualStyleBackColor = true;
			this.buttonInPrint.Click += new System.EventHandler(this.ButtonInPrintClick);
			// 
			// buttonInResults
			// 
			this.buttonInResults.Location = new System.Drawing.Point(1061, 5);
			this.buttonInResults.Name = "buttonInResults";
			this.buttonInResults.Size = new System.Drawing.Size(92, 23);
			this.buttonInResults.TabIndex = 13;
			this.buttonInResults.Text = "Ergebnisse";
			this.buttonInResults.UseVisualStyleBackColor = true;
			this.buttonInResults.Click += new System.EventHandler(this.ButtonInResultsClick);
			// 
			// buttonInDelete
			// 
			this.buttonInDelete.Location = new System.Drawing.Point(202, 5);
			this.buttonInDelete.Name = "buttonInDelete";
			this.buttonInDelete.Size = new System.Drawing.Size(92, 23);
			this.buttonInDelete.TabIndex = 12;
			this.buttonInDelete.Text = "Löschen";
			this.buttonInDelete.UseVisualStyleBackColor = true;
			this.buttonInDelete.Click += new System.EventHandler(this.ButtonInDeleteClick);
			// 
			// buttonInSave
			// 
			this.buttonInSave.Location = new System.Drawing.Point(104, 5);
			this.buttonInSave.Name = "buttonInSave";
			this.buttonInSave.Size = new System.Drawing.Size(92, 23);
			this.buttonInSave.TabIndex = 11;
			this.buttonInSave.Text = "Speichern";
			this.buttonInSave.UseVisualStyleBackColor = true;
			this.buttonInSave.Click += new System.EventHandler(this.ButtonInSaveClick);
			// 
			// buttonInGenerate
			// 
			this.buttonInGenerate.Location = new System.Drawing.Point(6, 5);
			this.buttonInGenerate.Name = "buttonInGenerate";
			this.buttonInGenerate.Size = new System.Drawing.Size(92, 23);
			this.buttonInGenerate.TabIndex = 10;
			this.buttonInGenerate.Text = "Generieren";
			this.buttonInGenerate.UseVisualStyleBackColor = true;
			this.buttonInGenerate.Click += new System.EventHandler(this.ButtonInGenerateClick);
			// 
			// dataGridViewInterim
			// 
			this.dataGridViewInterim.AllowUserToAddRows = false;
			this.dataGridViewInterim.AllowUserToDeleteRows = false;
			this.dataGridViewInterim.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewInterim.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewInterim.Location = new System.Drawing.Point(3, 34);
			this.dataGridViewInterim.MultiSelect = false;
			this.dataGridViewInterim.Name = "dataGridViewInterim";
			this.dataGridViewInterim.Size = new System.Drawing.Size(1150, 659);
			this.dataGridViewInterim.TabIndex = 9;
			this.dataGridViewInterim.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewInterimCellValueChanged);
			// 
			// tabPageCrossgames
			// 
			this.tabPageCrossgames.Controls.Add(this.buttonPreClPrint);
			this.tabPageCrossgames.Controls.Add(this.buttonPreClDelete);
			this.tabPageCrossgames.Controls.Add(this.buttonPreClSave);
			this.tabPageCrossgames.Controls.Add(this.buttonPreClGenerate);
			this.tabPageCrossgames.Controls.Add(this.dataGridViewPreClassement);
			this.tabPageCrossgames.Location = new System.Drawing.Point(4, 22);
			this.tabPageCrossgames.Name = "tabPageCrossgames";
			this.tabPageCrossgames.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageCrossgames.Size = new System.Drawing.Size(1156, 696);
			this.tabPageCrossgames.TabIndex = 3;
			this.tabPageCrossgames.Text = "Kreuz/Vorplatzierungsrunde";
			this.tabPageCrossgames.UseVisualStyleBackColor = true;
			// 
			// buttonPreClPrint
			// 
			this.buttonPreClPrint.Location = new System.Drawing.Point(300, 5);
			this.buttonPreClPrint.Name = "buttonPreClPrint";
			this.buttonPreClPrint.Size = new System.Drawing.Size(92, 23);
			this.buttonPreClPrint.TabIndex = 14;
			this.buttonPreClPrint.Text = "Drucken";
			this.buttonPreClPrint.UseVisualStyleBackColor = true;
			// 
			// buttonPreClDelete
			// 
			this.buttonPreClDelete.Location = new System.Drawing.Point(202, 5);
			this.buttonPreClDelete.Name = "buttonPreClDelete";
			this.buttonPreClDelete.Size = new System.Drawing.Size(92, 23);
			this.buttonPreClDelete.TabIndex = 12;
			this.buttonPreClDelete.Text = "Löschen";
			this.buttonPreClDelete.UseVisualStyleBackColor = true;
			// 
			// buttonPreClSave
			// 
			this.buttonPreClSave.Location = new System.Drawing.Point(104, 5);
			this.buttonPreClSave.Name = "buttonPreClSave";
			this.buttonPreClSave.Size = new System.Drawing.Size(92, 23);
			this.buttonPreClSave.TabIndex = 11;
			this.buttonPreClSave.Text = "Speichern";
			this.buttonPreClSave.UseVisualStyleBackColor = true;
			// 
			// buttonPreClGenerate
			// 
			this.buttonPreClGenerate.Location = new System.Drawing.Point(6, 5);
			this.buttonPreClGenerate.Name = "buttonPreClGenerate";
			this.buttonPreClGenerate.Size = new System.Drawing.Size(92, 23);
			this.buttonPreClGenerate.TabIndex = 10;
			this.buttonPreClGenerate.Text = "Generieren";
			this.buttonPreClGenerate.UseVisualStyleBackColor = true;
			this.buttonPreClGenerate.Click += new System.EventHandler(this.ButtonPreClGenerateClick);
			// 
			// dataGridViewPreClassement
			// 
			this.dataGridViewPreClassement.AllowUserToAddRows = false;
			this.dataGridViewPreClassement.AllowUserToDeleteRows = false;
			this.dataGridViewPreClassement.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewPreClassement.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewPreClassement.Location = new System.Drawing.Point(3, 34);
			this.dataGridViewPreClassement.MultiSelect = false;
			this.dataGridViewPreClassement.Name = "dataGridViewPreClassement";
			this.dataGridViewPreClassement.Size = new System.Drawing.Size(1150, 658);
			this.dataGridViewPreClassement.TabIndex = 9;
			this.dataGridViewPreClassement.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewPreClassementCellValueChanged);
			// 
			// tabPageClassement
			// 
			this.tabPageClassement.Controls.Add(this.buttonClPrint);
			this.tabPageClassement.Controls.Add(this.buttonClResult);
			this.tabPageClassement.Controls.Add(this.buttonClDelete);
			this.tabPageClassement.Controls.Add(this.buttonClSave);
			this.tabPageClassement.Controls.Add(this.buttonClGenerate);
			this.tabPageClassement.Controls.Add(this.dataGridViewClassement);
			this.tabPageClassement.Location = new System.Drawing.Point(4, 22);
			this.tabPageClassement.Name = "tabPageClassement";
			this.tabPageClassement.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageClassement.Size = new System.Drawing.Size(1156, 696);
			this.tabPageClassement.TabIndex = 4;
			this.tabPageClassement.Text = "Platzierungsrunde";
			this.tabPageClassement.UseVisualStyleBackColor = true;
			// 
			// buttonClPrint
			// 
			this.buttonClPrint.Location = new System.Drawing.Point(300, 5);
			this.buttonClPrint.Name = "buttonClPrint";
			this.buttonClPrint.Size = new System.Drawing.Size(92, 23);
			this.buttonClPrint.TabIndex = 14;
			this.buttonClPrint.Text = "Drucken";
			this.buttonClPrint.UseVisualStyleBackColor = true;
			// 
			// buttonClResult
			// 
			this.buttonClResult.Location = new System.Drawing.Point(1061, 5);
			this.buttonClResult.Name = "buttonClResult";
			this.buttonClResult.Size = new System.Drawing.Size(92, 23);
			this.buttonClResult.TabIndex = 13;
			this.buttonClResult.Text = "Endergebnis";
			this.buttonClResult.UseVisualStyleBackColor = true;
			// 
			// buttonClDelete
			// 
			this.buttonClDelete.Location = new System.Drawing.Point(202, 5);
			this.buttonClDelete.Name = "buttonClDelete";
			this.buttonClDelete.Size = new System.Drawing.Size(92, 23);
			this.buttonClDelete.TabIndex = 12;
			this.buttonClDelete.Text = "Löschen";
			this.buttonClDelete.UseVisualStyleBackColor = true;
			// 
			// buttonClSave
			// 
			this.buttonClSave.Location = new System.Drawing.Point(104, 5);
			this.buttonClSave.Name = "buttonClSave";
			this.buttonClSave.Size = new System.Drawing.Size(92, 23);
			this.buttonClSave.TabIndex = 11;
			this.buttonClSave.Text = "Speichern";
			this.buttonClSave.UseVisualStyleBackColor = true;
			// 
			// buttonClGenerate
			// 
			this.buttonClGenerate.Location = new System.Drawing.Point(6, 5);
			this.buttonClGenerate.Name = "buttonClGenerate";
			this.buttonClGenerate.Size = new System.Drawing.Size(92, 23);
			this.buttonClGenerate.TabIndex = 10;
			this.buttonClGenerate.Text = "Generieren";
			this.buttonClGenerate.UseVisualStyleBackColor = true;
			// 
			// dataGridViewClassement
			// 
			this.dataGridViewClassement.AllowUserToAddRows = false;
			this.dataGridViewClassement.AllowUserToDeleteRows = false;
			this.dataGridViewClassement.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewClassement.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewClassement.Location = new System.Drawing.Point(3, 34);
			this.dataGridViewClassement.MultiSelect = false;
			this.dataGridViewClassement.Name = "dataGridViewClassement";
			this.dataGridViewClassement.Size = new System.Drawing.Size(1150, 658);
			this.dataGridViewClassement.TabIndex = 9;
			this.dataGridViewClassement.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewClassementCellValueChanged);
			// 
			// menuStrip
			// 
			this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
			this.fileToolStripMenuItem,
			this.helpToolStripMenuItem});
			this.menuStrip.Location = new System.Drawing.Point(0, 0);
			this.menuStrip.Name = "menuStrip";
			this.menuStrip.Size = new System.Drawing.Size(1164, 24);
			this.menuStrip.TabIndex = 5;
			this.menuStrip.Text = "menuStrip";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
			this.exitToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 20);
			this.fileToolStripMenuItem.Text = "Datei";
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(120, 22);
			this.exitToolStripMenuItem.Text = "Beenden";
			// 
			// helpToolStripMenuItem
			// 
			this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
			this.dokumentationToolStripMenuItem,
			this.aboutToolStripMenuItem});
			this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
			this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
			this.helpToolStripMenuItem.Text = "Hilfe";
			// 
			// dokumentationToolStripMenuItem
			// 
			this.dokumentationToolStripMenuItem.Name = "dokumentationToolStripMenuItem";
			this.dokumentationToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
			this.dokumentationToolStripMenuItem.Text = "Dokumentation";
			this.dokumentationToolStripMenuItem.Click += new System.EventHandler(this.DokumentationToolStripMenuItemClick);
			// 
			// aboutToolStripMenuItem
			// 
			this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
			this.aboutToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
			this.aboutToolStripMenuItem.Text = "Über...";
			this.aboutToolStripMenuItem.Click += new System.EventHandler(this.AboutToolStripMenuItemClick);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1164, 768);
			this.Controls.Add(this.tabControl);
			this.Controls.Add(this.statusStripTournamentTime);
			this.Controls.Add(this.menuStrip);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MainMenuStrip = this.menuStrip;
			this.Name = "MainForm";
			this.Text = "Volleyball";
			this.statusStripTournamentTime.ResumeLayout(false);
			this.statusStripTournamentTime.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewTeams)).EndInit();
			this.tabControl.ResumeLayout(false);
			this.tabPageTeamsTime.ResumeLayout(false);
			this.groupBoxFields.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownFieldCount)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewFields)).EndInit();
			this.groupBoxTeams.ResumeLayout(false);
			this.tabPageQualifying.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewQualifying)).EndInit();
			this.tabPageInterim.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewInterim)).EndInit();
			this.tabPageCrossgames.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewPreClassement)).EndInit();
			this.tabPageClassement.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.dataGridViewClassement)).EndInit();
			this.menuStrip.ResumeLayout(false);
			this.menuStrip.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}
	}
}
