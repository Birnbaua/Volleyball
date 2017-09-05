/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 06.07.2017
 * Time: 13:56
 */
using System;
using System.Drawing;
using System.Windows.Forms;

namespace volleyball
{
	public partial class About : Form
	{
		public About(String versiontext, String developerText)
		{
			InitializeComponent();
			
			this.labelProgramVersion.Text = versiontext;
			this.textBoxInfo.Text = developerText;
		}
	}
}
