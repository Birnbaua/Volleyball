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
		private System.Windows.Forms.GroupBox groupBoxTimeplanInterim;
		private System.Windows.Forms.GroupBox groupBoxTimeplanQualifying;
		private System.Windows.Forms.GroupBox groupBoxTimeplanPreClassement;
		private System.Windows.Forms.GroupBox groupBoxTimeplanClassement;
		private System.Windows.Forms.GroupBox groupBoxTournamentStartTimes;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.NumericUpDown numericUpDownBreakPreClassementClassement;
		private System.Windows.Forms.NumericUpDown numericUpDownBreakInterimCrossgames;
		private System.Windows.Forms.NumericUpDown numericUpDownBreakQualifyingInterim;
		private System.Windows.Forms.DateTimePicker dateTimePickerTournamentStartTime;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.NumericUpDown numericUpDownQfBreakPerRound;
		private System.Windows.Forms.NumericUpDown numericUpDownQfMinPerGame;
		private System.Windows.Forms.NumericUpDown numericUpDownQfGames;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.Label label13;
		private System.Windows.Forms.Label label14;
		private System.Windows.Forms.NumericUpDown numericUpDownPreClBreakPerRound;
		private System.Windows.Forms.NumericUpDown numericUpDownPreClMinPerGame;
		private System.Windows.Forms.NumericUpDown numericUpDownPreClGames;
		private System.Windows.Forms.Label label18;
		private System.Windows.Forms.NumericUpDown numericUpDownTimeForHonor;
		private System.Windows.Forms.Label label15;
		private System.Windows.Forms.Label label16;
		private System.Windows.Forms.Label label17;
		private System.Windows.Forms.NumericUpDown numericUpDownTimeFinalGame;
		private System.Windows.Forms.NumericUpDown numericUpDownClMinPerGame;
		private System.Windows.Forms.NumericUpDown numericUpDownClGames;
		private System.Windows.Forms.Panel panelTeamConfigButtons;
		private System.Windows.Forms.Button buttonSaveChanges;
		private System.Windows.Forms.Button buttonCancelChanges;
		private System.Windows.Forms.Button buttonDefaultConfiguration;
		private System.Windows.Forms.CheckBox checkBoxPreClassementGames;
		private System.Windows.Forms.CheckBox checkBoxCrossgames;
		private System.Windows.Forms.Label labelMode;
		private System.Windows.Forms.NumericUpDown numericUpDownItBreakPerRound;
		private System.Windows.Forms.NumericUpDown numericUpDownItMinPerGame;
		private System.Windows.Forms.NumericUpDown numericUpDownItGames;
		
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
			this.panelTeamConfigButtons = new System.Windows.Forms.Panel();
			this.labelMode = new System.Windows.Forms.Label();
			this.checkBoxCrossgames = new System.Windows.Forms.CheckBox();
			this.checkBoxPreClassementGames = new System.Windows.Forms.CheckBox();
			this.buttonDefaultConfiguration = new System.Windows.Forms.Button();
			this.buttonCancelChanges = new System.Windows.Forms.Button();
			this.buttonSaveChanges = new System.Windows.Forms.Button();
			this.groupBoxTimeplanInterim = new System.Windows.Forms.GroupBox();
			this.label9 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.label11 = new System.Windows.Forms.Label();
			this.numericUpDownItBreakPerRound = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownItMinPerGame = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownItGames = new System.Windows.Forms.NumericUpDown();
			this.groupBoxTimeplanQualifying = new System.Windows.Forms.GroupBox();
			this.label6 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.numericUpDownQfBreakPerRound = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownQfMinPerGame = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownQfGames = new System.Windows.Forms.NumericUpDown();
			this.groupBoxTimeplanPreClassement = new System.Windows.Forms.GroupBox();
			this.label12 = new System.Windows.Forms.Label();
			this.label13 = new System.Windows.Forms.Label();
			this.label14 = new System.Windows.Forms.Label();
			this.numericUpDownPreClBreakPerRound = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownPreClMinPerGame = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownPreClGames = new System.Windows.Forms.NumericUpDown();
			this.groupBoxTimeplanClassement = new System.Windows.Forms.GroupBox();
			this.label18 = new System.Windows.Forms.Label();
			this.numericUpDownTimeForHonor = new System.Windows.Forms.NumericUpDown();
			this.label15 = new System.Windows.Forms.Label();
			this.label16 = new System.Windows.Forms.Label();
			this.label17 = new System.Windows.Forms.Label();
			this.numericUpDownTimeFinalGame = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownClMinPerGame = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownClGames = new System.Windows.Forms.NumericUpDown();
			this.groupBoxTournamentStartTimes = new System.Windows.Forms.GroupBox();
			this.dateTimePickerTournamentStartTime = new System.Windows.Forms.DateTimePicker();
			this.label5 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.numericUpDownBreakPreClassementClassement = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownBreakInterimCrossgames = new System.Windows.Forms.NumericUpDown();
			this.numericUpDownBreakQualifyingInterim = new System.Windows.Forms.NumericUpDown();
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
			this.panelTeamConfigButtons.SuspendLayout();
			this.groupBoxTimeplanInterim.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItBreakPerRound)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItMinPerGame)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItGames)).BeginInit();
			this.groupBoxTimeplanQualifying.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfBreakPerRound)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfMinPerGame)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfGames)).BeginInit();
			this.groupBoxTimeplanPreClassement.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClBreakPerRound)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClMinPerGame)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClGames)).BeginInit();
			this.groupBoxTimeplanClassement.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownTimeForHonor)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownTimeFinalGame)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownClMinPerGame)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownClGames)).BeginInit();
			this.groupBoxTournamentStartTimes.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakPreClassementClassement)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakInterimCrossgames)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakQualifyingInterim)).BeginInit();
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
			this.statusStripTournamentTime.Size = new System.Drawing.Size(1084, 22);
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
			this.dataGridViewTeams.Size = new System.Drawing.Size(1058, 232);
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
			this.tabControl.Size = new System.Drawing.Size(1084, 722);
			this.tabControl.TabIndex = 4;
			// 
			// tabPageTeamsTime
			// 
			this.tabPageTeamsTime.Controls.Add(this.panelTeamConfigButtons);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTimeplanInterim);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTimeplanQualifying);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTimeplanPreClassement);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTimeplanClassement);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTournamentStartTimes);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxFields);
			this.tabPageTeamsTime.Controls.Add(this.groupBoxTeams);
			this.tabPageTeamsTime.Location = new System.Drawing.Point(4, 22);
			this.tabPageTeamsTime.Name = "tabPageTeamsTime";
			this.tabPageTeamsTime.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageTeamsTime.Size = new System.Drawing.Size(1076, 696);
			this.tabPageTeamsTime.TabIndex = 0;
			this.tabPageTeamsTime.Text = "Mannschaften/Zeitplan";
			this.tabPageTeamsTime.UseVisualStyleBackColor = true;
			// 
			// panelTeamConfigButtons
			// 
			this.panelTeamConfigButtons.Controls.Add(this.labelMode);
			this.panelTeamConfigButtons.Controls.Add(this.checkBoxCrossgames);
			this.panelTeamConfigButtons.Controls.Add(this.checkBoxPreClassementGames);
			this.panelTeamConfigButtons.Controls.Add(this.buttonDefaultConfiguration);
			this.panelTeamConfigButtons.Controls.Add(this.buttonCancelChanges);
			this.panelTeamConfigButtons.Controls.Add(this.buttonSaveChanges);
			this.panelTeamConfigButtons.Dock = System.Windows.Forms.DockStyle.Top;
			this.panelTeamConfigButtons.Location = new System.Drawing.Point(3, 3);
			this.panelTeamConfigButtons.Name = "panelTeamConfigButtons";
			this.panelTeamConfigButtons.Size = new System.Drawing.Size(1070, 33);
			this.panelTeamConfigButtons.TabIndex = 11;
			// 
			// labelMode
			// 
			this.labelMode.Location = new System.Drawing.Point(699, 4);
			this.labelMode.Name = "labelMode";
			this.labelMode.Size = new System.Drawing.Size(50, 23);
			this.labelMode.TabIndex = 9;
			this.labelMode.Text = "Modus:";
			this.labelMode.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// checkBoxCrossgames
			// 
			this.checkBoxCrossgames.Location = new System.Drawing.Point(755, 4);
			this.checkBoxCrossgames.Name = "checkBoxCrossgames";
			this.checkBoxCrossgames.Size = new System.Drawing.Size(104, 24);
			this.checkBoxCrossgames.TabIndex = 14;
			this.checkBoxCrossgames.Text = "Kreuzspiele";
			this.checkBoxCrossgames.UseVisualStyleBackColor = true;
			// 
			// checkBoxPreClassementGames
			// 
			this.checkBoxPreClassementGames.Location = new System.Drawing.Point(865, 4);
			this.checkBoxPreClassementGames.Name = "checkBoxPreClassementGames";
			this.checkBoxPreClassementGames.Size = new System.Drawing.Size(199, 24);
			this.checkBoxPreClassementGames.TabIndex = 12;
			this.checkBoxPreClassementGames.Text = "Vorplatzspiele (50, 55 u. 60 Teams)";
			this.checkBoxPreClassementGames.UseVisualStyleBackColor = true;
			// 
			// buttonDefaultConfiguration
			// 
			this.buttonDefaultConfiguration.Location = new System.Drawing.Point(285, 4);
			this.buttonDefaultConfiguration.Name = "buttonDefaultConfiguration";
			this.buttonDefaultConfiguration.Size = new System.Drawing.Size(135, 23);
			this.buttonDefaultConfiguration.TabIndex = 14;
			this.buttonDefaultConfiguration.Text = "Konfiguration rücksetzen";
			this.buttonDefaultConfiguration.UseVisualStyleBackColor = true;
			this.buttonDefaultConfiguration.Click += new System.EventHandler(this.ButtonDefaultConfigurationClick);
			// 
			// buttonCancelChanges
			// 
			this.buttonCancelChanges.Location = new System.Drawing.Point(144, 4);
			this.buttonCancelChanges.Name = "buttonCancelChanges";
			this.buttonCancelChanges.Size = new System.Drawing.Size(135, 23);
			this.buttonCancelChanges.TabIndex = 13;
			this.buttonCancelChanges.Text = "Änderungen verwerfen";
			this.buttonCancelChanges.UseVisualStyleBackColor = true;
			this.buttonCancelChanges.Click += new System.EventHandler(this.ButtonCancelChangesClick);
			// 
			// buttonSaveChanges
			// 
			this.buttonSaveChanges.Location = new System.Drawing.Point(3, 4);
			this.buttonSaveChanges.Name = "buttonSaveChanges";
			this.buttonSaveChanges.Size = new System.Drawing.Size(135, 23);
			this.buttonSaveChanges.TabIndex = 12;
			this.buttonSaveChanges.Text = "Änderungen speichern";
			this.buttonSaveChanges.UseVisualStyleBackColor = true;
			this.buttonSaveChanges.Click += new System.EventHandler(this.ButtonSaveChangesClick);
			// 
			// groupBoxTimeplanInterim
			// 
			this.groupBoxTimeplanInterim.Controls.Add(this.label9);
			this.groupBoxTimeplanInterim.Controls.Add(this.label10);
			this.groupBoxTimeplanInterim.Controls.Add(this.label11);
			this.groupBoxTimeplanInterim.Controls.Add(this.numericUpDownItBreakPerRound);
			this.groupBoxTimeplanInterim.Controls.Add(this.numericUpDownItMinPerGame);
			this.groupBoxTimeplanInterim.Controls.Add(this.numericUpDownItGames);
			this.groupBoxTimeplanInterim.Location = new System.Drawing.Point(383, 168);
			this.groupBoxTimeplanInterim.Name = "groupBoxTimeplanInterim";
			this.groupBoxTimeplanInterim.Size = new System.Drawing.Size(384, 98);
			this.groupBoxTimeplanInterim.TabIndex = 10;
			this.groupBoxTimeplanInterim.TabStop = false;
			this.groupBoxTimeplanInterim.Text = "Zeitplanung Zwischenrunde";
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(6, 65);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(220, 23);
			this.label9.TabIndex = 19;
			this.label9.Text = "Pause (min) zw. den Runden";
			this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label10
			// 
			this.label10.Location = new System.Drawing.Point(6, 40);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(220, 23);
			this.label10.TabIndex = 18;
			this.label10.Text = "Minuten pro Satz";
			this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label11
			// 
			this.label11.Location = new System.Drawing.Point(6, 16);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(220, 23);
			this.label11.TabIndex = 17;
			this.label11.Text = "Sätze";
			this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownItBreakPerRound
			// 
			this.numericUpDownItBreakPerRound.Location = new System.Drawing.Point(247, 69);
			this.numericUpDownItBreakPerRound.Name = "numericUpDownItBreakPerRound";
			this.numericUpDownItBreakPerRound.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownItBreakPerRound.TabIndex = 16;
			// 
			// numericUpDownItMinPerGame
			// 
			this.numericUpDownItMinPerGame.Location = new System.Drawing.Point(247, 44);
			this.numericUpDownItMinPerGame.Name = "numericUpDownItMinPerGame";
			this.numericUpDownItMinPerGame.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownItMinPerGame.TabIndex = 15;
			// 
			// numericUpDownItGames
			// 
			this.numericUpDownItGames.Location = new System.Drawing.Point(247, 19);
			this.numericUpDownItGames.Name = "numericUpDownItGames";
			this.numericUpDownItGames.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownItGames.TabIndex = 14;
			// 
			// groupBoxTimeplanQualifying
			// 
			this.groupBoxTimeplanQualifying.Controls.Add(this.label6);
			this.groupBoxTimeplanQualifying.Controls.Add(this.label7);
			this.groupBoxTimeplanQualifying.Controls.Add(this.label8);
			this.groupBoxTimeplanQualifying.Controls.Add(this.numericUpDownQfBreakPerRound);
			this.groupBoxTimeplanQualifying.Controls.Add(this.numericUpDownQfMinPerGame);
			this.groupBoxTimeplanQualifying.Controls.Add(this.numericUpDownQfGames);
			this.groupBoxTimeplanQualifying.Location = new System.Drawing.Point(3, 168);
			this.groupBoxTimeplanQualifying.Name = "groupBoxTimeplanQualifying";
			this.groupBoxTimeplanQualifying.Size = new System.Drawing.Size(374, 98);
			this.groupBoxTimeplanQualifying.TabIndex = 9;
			this.groupBoxTimeplanQualifying.TabStop = false;
			this.groupBoxTimeplanQualifying.Text = "Zeitplanung Vorrunde";
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(6, 65);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(220, 23);
			this.label6.TabIndex = 13;
			this.label6.Text = "Pause (min) zw. den Runden";
			this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(6, 40);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(220, 23);
			this.label7.TabIndex = 12;
			this.label7.Text = "Minuten pro Satz";
			this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label8
			// 
			this.label8.Location = new System.Drawing.Point(6, 16);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(220, 23);
			this.label8.TabIndex = 11;
			this.label8.Text = "Sätze";
			this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownQfBreakPerRound
			// 
			this.numericUpDownQfBreakPerRound.Location = new System.Drawing.Point(248, 69);
			this.numericUpDownQfBreakPerRound.Name = "numericUpDownQfBreakPerRound";
			this.numericUpDownQfBreakPerRound.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownQfBreakPerRound.TabIndex = 10;
			// 
			// numericUpDownQfMinPerGame
			// 
			this.numericUpDownQfMinPerGame.Location = new System.Drawing.Point(248, 44);
			this.numericUpDownQfMinPerGame.Name = "numericUpDownQfMinPerGame";
			this.numericUpDownQfMinPerGame.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownQfMinPerGame.TabIndex = 9;
			// 
			// numericUpDownQfGames
			// 
			this.numericUpDownQfGames.Location = new System.Drawing.Point(248, 19);
			this.numericUpDownQfGames.Name = "numericUpDownQfGames";
			this.numericUpDownQfGames.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownQfGames.TabIndex = 8;
			// 
			// groupBoxTimeplanPreClassement
			// 
			this.groupBoxTimeplanPreClassement.Controls.Add(this.label12);
			this.groupBoxTimeplanPreClassement.Controls.Add(this.label13);
			this.groupBoxTimeplanPreClassement.Controls.Add(this.label14);
			this.groupBoxTimeplanPreClassement.Controls.Add(this.numericUpDownPreClBreakPerRound);
			this.groupBoxTimeplanPreClassement.Controls.Add(this.numericUpDownPreClMinPerGame);
			this.groupBoxTimeplanPreClassement.Controls.Add(this.numericUpDownPreClGames);
			this.groupBoxTimeplanPreClassement.Location = new System.Drawing.Point(3, 272);
			this.groupBoxTimeplanPreClassement.Name = "groupBoxTimeplanPreClassement";
			this.groupBoxTimeplanPreClassement.Size = new System.Drawing.Size(374, 129);
			this.groupBoxTimeplanPreClassement.TabIndex = 8;
			this.groupBoxTimeplanPreClassement.TabStop = false;
			this.groupBoxTimeplanPreClassement.Text = "Zeitplanung Kreuzspiele";
			// 
			// label12
			// 
			this.label12.Location = new System.Drawing.Point(6, 66);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(220, 23);
			this.label12.TabIndex = 22;
			this.label12.Text = "Pause (min) zw. den Runden";
			this.label12.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label13
			// 
			this.label13.Location = new System.Drawing.Point(6, 41);
			this.label13.Name = "label13";
			this.label13.Size = new System.Drawing.Size(220, 23);
			this.label13.TabIndex = 21;
			this.label13.Text = "Minuten pro Satz";
			this.label13.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label14
			// 
			this.label14.Location = new System.Drawing.Point(6, 17);
			this.label14.Name = "label14";
			this.label14.Size = new System.Drawing.Size(220, 23);
			this.label14.TabIndex = 20;
			this.label14.Text = "Sätze";
			this.label14.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownPreClBreakPerRound
			// 
			this.numericUpDownPreClBreakPerRound.Location = new System.Drawing.Point(248, 70);
			this.numericUpDownPreClBreakPerRound.Name = "numericUpDownPreClBreakPerRound";
			this.numericUpDownPreClBreakPerRound.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownPreClBreakPerRound.TabIndex = 10;
			// 
			// numericUpDownPreClMinPerGame
			// 
			this.numericUpDownPreClMinPerGame.Location = new System.Drawing.Point(248, 45);
			this.numericUpDownPreClMinPerGame.Name = "numericUpDownPreClMinPerGame";
			this.numericUpDownPreClMinPerGame.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownPreClMinPerGame.TabIndex = 9;
			// 
			// numericUpDownPreClGames
			// 
			this.numericUpDownPreClGames.Location = new System.Drawing.Point(248, 20);
			this.numericUpDownPreClGames.Name = "numericUpDownPreClGames";
			this.numericUpDownPreClGames.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownPreClGames.TabIndex = 8;
			// 
			// groupBoxTimeplanClassement
			// 
			this.groupBoxTimeplanClassement.Controls.Add(this.label18);
			this.groupBoxTimeplanClassement.Controls.Add(this.numericUpDownTimeForHonor);
			this.groupBoxTimeplanClassement.Controls.Add(this.label15);
			this.groupBoxTimeplanClassement.Controls.Add(this.label16);
			this.groupBoxTimeplanClassement.Controls.Add(this.label17);
			this.groupBoxTimeplanClassement.Controls.Add(this.numericUpDownTimeFinalGame);
			this.groupBoxTimeplanClassement.Controls.Add(this.numericUpDownClMinPerGame);
			this.groupBoxTimeplanClassement.Controls.Add(this.numericUpDownClGames);
			this.groupBoxTimeplanClassement.Location = new System.Drawing.Point(383, 272);
			this.groupBoxTimeplanClassement.Name = "groupBoxTimeplanClassement";
			this.groupBoxTimeplanClassement.Size = new System.Drawing.Size(384, 129);
			this.groupBoxTimeplanClassement.TabIndex = 7;
			this.groupBoxTimeplanClassement.TabStop = false;
			this.groupBoxTimeplanClassement.Text = "Zeitplan Platzierungspiele/Finale";
			// 
			// label18
			// 
			this.label18.Location = new System.Drawing.Point(6, 92);
			this.label18.Name = "label18";
			this.label18.Size = new System.Drawing.Size(220, 23);
			this.label18.TabIndex = 15;
			this.label18.Text = "Dauer Pause inkl. Siegerehrung nach Finale";
			this.label18.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownTimeForHonor
			// 
			this.numericUpDownTimeForHonor.Location = new System.Drawing.Point(247, 93);
			this.numericUpDownTimeForHonor.Name = "numericUpDownTimeForHonor";
			this.numericUpDownTimeForHonor.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownTimeForHonor.TabIndex = 14;
			// 
			// label15
			// 
			this.label15.Location = new System.Drawing.Point(6, 67);
			this.label15.Name = "label15";
			this.label15.Size = new System.Drawing.Size(220, 23);
			this.label15.TabIndex = 13;
			this.label15.Text = "geschätzte Spielzeit Finale (min)";
			this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label16
			// 
			this.label16.Location = new System.Drawing.Point(6, 38);
			this.label16.Name = "label16";
			this.label16.Size = new System.Drawing.Size(235, 27);
			this.label16.TabIndex = 12;
			this.label16.Text = "geschätzte Platzierungsspielzeit pro Satz (min)";
			this.label16.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label17
			// 
			this.label17.Location = new System.Drawing.Point(6, 18);
			this.label17.Name = "label17";
			this.label17.Size = new System.Drawing.Size(220, 23);
			this.label17.TabIndex = 11;
			this.label17.Text = "Sätze";
			this.label17.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownTimeFinalGame
			// 
			this.numericUpDownTimeFinalGame.Location = new System.Drawing.Point(247, 68);
			this.numericUpDownTimeFinalGame.Name = "numericUpDownTimeFinalGame";
			this.numericUpDownTimeFinalGame.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownTimeFinalGame.TabIndex = 10;
			// 
			// numericUpDownClMinPerGame
			// 
			this.numericUpDownClMinPerGame.Location = new System.Drawing.Point(247, 43);
			this.numericUpDownClMinPerGame.Name = "numericUpDownClMinPerGame";
			this.numericUpDownClMinPerGame.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownClMinPerGame.TabIndex = 9;
			// 
			// numericUpDownClGames
			// 
			this.numericUpDownClGames.Location = new System.Drawing.Point(247, 18);
			this.numericUpDownClGames.Name = "numericUpDownClGames";
			this.numericUpDownClGames.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownClGames.TabIndex = 8;
			// 
			// groupBoxTournamentStartTimes
			// 
			this.groupBoxTournamentStartTimes.Controls.Add(this.dateTimePickerTournamentStartTime);
			this.groupBoxTournamentStartTimes.Controls.Add(this.label5);
			this.groupBoxTournamentStartTimes.Controls.Add(this.label4);
			this.groupBoxTournamentStartTimes.Controls.Add(this.label3);
			this.groupBoxTournamentStartTimes.Controls.Add(this.label2);
			this.groupBoxTournamentStartTimes.Controls.Add(this.numericUpDownBreakPreClassementClassement);
			this.groupBoxTournamentStartTimes.Controls.Add(this.numericUpDownBreakInterimCrossgames);
			this.groupBoxTournamentStartTimes.Controls.Add(this.numericUpDownBreakQualifyingInterim);
			this.groupBoxTournamentStartTimes.Location = new System.Drawing.Point(3, 42);
			this.groupBoxTournamentStartTimes.Name = "groupBoxTournamentStartTimes";
			this.groupBoxTournamentStartTimes.Size = new System.Drawing.Size(764, 120);
			this.groupBoxTournamentStartTimes.TabIndex = 6;
			this.groupBoxTournamentStartTimes.TabStop = false;
			this.groupBoxTournamentStartTimes.Text = "Turnierstart/Pausenzeiten";
			// 
			// dateTimePickerTournamentStartTime
			// 
			this.dateTimePickerTournamentStartTime.CustomFormat = "HH:mm";
			this.dateTimePickerTournamentStartTime.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
			this.dateTimePickerTournamentStartTime.Location = new System.Drawing.Point(232, 16);
			this.dateTimePickerTournamentStartTime.Name = "dateTimePickerTournamentStartTime";
			this.dateTimePickerTournamentStartTime.ShowUpDown = true;
			this.dateTimePickerTournamentStartTime.Size = new System.Drawing.Size(75, 20);
			this.dateTimePickerTournamentStartTime.TabIndex = 8;
			this.dateTimePickerTournamentStartTime.Value = new System.DateTime(2017, 8, 3, 10, 0, 0, 0);
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(6, 88);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(220, 23);
			this.label5.TabIndex = 7;
			this.label5.Text = "Pause zw. Kreuz - und Platzierungsspiele";
			this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(6, 63);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(220, 23);
			this.label4.TabIndex = 6;
			this.label4.Text = "Pause zw. Zwischenrunde und Kreuzspiele";
			this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(6, 39);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(220, 23);
			this.label3.TabIndex = 5;
			this.label3.Text = "Pause zw. Vor- und Zwischenrunde";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(6, 16);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(220, 23);
			this.label2.TabIndex = 4;
			this.label2.Text = "Start Turnier (HH:mm)";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// numericUpDownBreakPreClassementClassement
			// 
			this.numericUpDownBreakPreClassementClassement.Location = new System.Drawing.Point(232, 91);
			this.numericUpDownBreakPreClassementClassement.Name = "numericUpDownBreakPreClassementClassement";
			this.numericUpDownBreakPreClassementClassement.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownBreakPreClassementClassement.TabIndex = 2;
			// 
			// numericUpDownBreakInterimCrossgames
			// 
			this.numericUpDownBreakInterimCrossgames.Location = new System.Drawing.Point(232, 66);
			this.numericUpDownBreakInterimCrossgames.Name = "numericUpDownBreakInterimCrossgames";
			this.numericUpDownBreakInterimCrossgames.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownBreakInterimCrossgames.TabIndex = 1;
			// 
			// numericUpDownBreakQualifyingInterim
			// 
			this.numericUpDownBreakQualifyingInterim.Location = new System.Drawing.Point(232, 41);
			this.numericUpDownBreakQualifyingInterim.Name = "numericUpDownBreakQualifyingInterim";
			this.numericUpDownBreakQualifyingInterim.Size = new System.Drawing.Size(75, 20);
			this.numericUpDownBreakQualifyingInterim.TabIndex = 0;
			// 
			// groupBoxFields
			// 
			this.groupBoxFields.Controls.Add(this.numericUpDownFieldCount);
			this.groupBoxFields.Controls.Add(this.label1);
			this.groupBoxFields.Controls.Add(this.dataGridViewFields);
			this.groupBoxFields.Location = new System.Drawing.Point(773, 42);
			this.groupBoxFields.Name = "groupBoxFields";
			this.groupBoxFields.Size = new System.Drawing.Size(300, 359);
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
			this.dataGridViewFields.AllowUserToAddRows = false;
			this.dataGridViewFields.AllowUserToDeleteRows = false;
			this.dataGridViewFields.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
			| System.Windows.Forms.AnchorStyles.Left) 
			| System.Windows.Forms.AnchorStyles.Right)));
			this.dataGridViewFields.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridViewFields.Location = new System.Drawing.Point(6, 45);
			this.dataGridViewFields.Name = "dataGridViewFields";
			this.dataGridViewFields.Size = new System.Drawing.Size(288, 308);
			this.dataGridViewFields.TabIndex = 1;
			// 
			// groupBoxTeams
			// 
			this.groupBoxTeams.Controls.Add(this.dataGridViewTeams);
			this.groupBoxTeams.Controls.Add(this.buttonClearTeams);
			this.groupBoxTeams.Controls.Add(this.buttonSaveTeams);
			this.groupBoxTeams.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBoxTeams.Location = new System.Drawing.Point(3, 407);
			this.groupBoxTeams.Name = "groupBoxTeams";
			this.groupBoxTeams.Size = new System.Drawing.Size(1070, 286);
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
			this.tabPageQualifying.Size = new System.Drawing.Size(1076, 696);
			this.tabPageQualifying.TabIndex = 1;
			this.tabPageQualifying.Text = "Vorrunde";
			this.tabPageQualifying.UseVisualStyleBackColor = true;
			// 
			// buttonQfOverallResults
			// 
			this.buttonQfOverallResults.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonQfOverallResults.Location = new System.Drawing.Point(981, 5);
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
			this.buttonQfResults.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonQfResults.Location = new System.Drawing.Point(864, 5);
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
			this.dataGridViewQualifying.Size = new System.Drawing.Size(1070, 659);
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
			this.tabPageInterim.Size = new System.Drawing.Size(1076, 696);
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
			this.buttonInResults.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonInResults.Location = new System.Drawing.Point(981, 6);
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
			this.dataGridViewInterim.Size = new System.Drawing.Size(1070, 659);
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
			this.tabPageCrossgames.Size = new System.Drawing.Size(1076, 696);
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
			this.dataGridViewPreClassement.Size = new System.Drawing.Size(1070, 658);
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
			this.tabPageClassement.Size = new System.Drawing.Size(1076, 696);
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
			this.buttonClResult.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.buttonClResult.Location = new System.Drawing.Point(981, 5);
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
			this.dataGridViewClassement.Size = new System.Drawing.Size(1070, 658);
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
			this.menuStrip.Size = new System.Drawing.Size(1084, 24);
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
			this.ClientSize = new System.Drawing.Size(1084, 768);
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
			this.panelTeamConfigButtons.ResumeLayout(false);
			this.groupBoxTimeplanInterim.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItBreakPerRound)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItMinPerGame)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownItGames)).EndInit();
			this.groupBoxTimeplanQualifying.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfBreakPerRound)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfMinPerGame)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownQfGames)).EndInit();
			this.groupBoxTimeplanPreClassement.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClBreakPerRound)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClMinPerGame)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownPreClGames)).EndInit();
			this.groupBoxTimeplanClassement.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownTimeForHonor)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownTimeFinalGame)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownClMinPerGame)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownClGames)).EndInit();
			this.groupBoxTournamentStartTimes.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakPreClassementClassement)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakInterimCrossgames)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownBreakQualifyingInterim)).EndInit();
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
