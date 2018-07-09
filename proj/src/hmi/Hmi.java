package hmi;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

public class Hmi 
{
	private JFrame frmVolleyballPlaner;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) 
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				try 
				{
					Hmi window = new Hmi();
					window.frmVolleyballPlaner.setVisible(true);
				} 
				catch (Exception e) 
				{
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Hmi() 
	{
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		frmVolleyballPlaner = new JFrame();
		frmVolleyballPlaner.setTitle("Volleyball Planer V13");
		frmVolleyballPlaner.setBounds(100, 100, 1024, 768);
		frmVolleyballPlaner.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		frmVolleyballPlaner.setJMenuBar(menuBar);
		
		JMenu mnFile = new JMenu("Datei");
		menuBar.add(mnFile);
		
		JMenuItem mntmBeenden = new JMenuItem("Beenden");
		mnFile.add(mntmBeenden);
		
		JMenu mnFenster = new JMenu("Fenster");
		menuBar.add(mnFenster);
		
		JMenuItem mntmVorrunde = new JMenuItem("Vorrunde");
		mnFenster.add(mntmVorrunde);
		
		JMenuItem mntmZwischenrunde = new JMenuItem("Zwischenrunde");
		mnFenster.add(mntmZwischenrunde);
		
		JMenuItem mntmKreuzspiele = new JMenuItem("Kreuzspiele");
		mnFenster.add(mntmKreuzspiele);
		
		JMenuItem mntmPlatzierungsspiele = new JMenuItem("Platzierungsspiele");
		mnFenster.add(mntmPlatzierungsspiele);
		
		JMenuItem mntmPlatzierungen = new JMenuItem("Platzierungen");
		mnFenster.add(mntmPlatzierungen);
		
		JMenu mnEinstellungen = new JMenu("Einstellungen");
		menuBar.add(mnEinstellungen);
		
		JMenuItem mntmMannschaften = new JMenuItem("Mannschaften");
		mnEinstellungen.add(mntmMannschaften);
		
		JMenuItem mntmFelder = new JMenuItem("Felder");
		mnEinstellungen.add(mntmFelder);
		
		JMenuItem mntmEinstellungen = new JMenuItem("Planeinstellungen");
		mnEinstellungen.add(mntmEinstellungen);
		
		JMenu mnHilfe = new JMenu("Hilfe");
		menuBar.add(mnHilfe);
		
		JMenuItem mntmHilfe = new JMenuItem("Hilfe");
		mnHilfe.add(mntmHilfe);
		
		JMenuItem mntmber = new JMenuItem("\u00DCber ...");
		mnHilfe.add(mntmber);
	}
}
