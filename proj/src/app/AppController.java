package app;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.TextFieldTableCell;
import system.DataHandling;
import system.Logging;

public class AppController implements Initializable
{
	private static PrintWriter pw;
	private List<String[]> teamsGroupList;
	
	public void initialize(URL arg0, ResourceBundle arg1)
	{
		try 
		{	
			pw = new PrintWriter("Messages_" + newTimestamp() + ".log");
			
			Logging.setFile(pw);
			
			for(int i = 0; i < DataHandling.Prefixes.length; i++)
			{
				TableColumn tc = new TableColumn(DataHandling.Prefixes[i]);
				tc.setCellFactory(TextFieldTableCell.forTableColumn());
				viewTeams.getColumns().add(tc);
			}
			
			viewTeams.getSelectionModel().setCellSelectionEnabled(true);
			
			loadTeams();
		}
		catch (IOException e) 
		{
			e.printStackTrace();
		}		
	}
		
	private String newTimestamp()
	{
		return new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss").format(new Date());
	}
		
	private void resetTeams() throws IOException
	{
		Logging.write("clear teams");
		
		teamsGroupList = DataHandling.clearTeams();
	}
		
	private void loadTeams() throws IOException
	{
		Logging.write("load teams");
		
		ObservableList<ObservableList<String>> data = FXCollections.observableArrayList();
		
		teamsGroupList = DataHandling.readTeams();
		
		if(teamsGroupList == null)
			return;
		
		for(int i = 0; i < teamsGroupList.size(); i++) 
		{
			ObservableList<String> row = FXCollections.observableArrayList();
            row.clear();
            
            for(int ii = 0; ii < teamsGroupList.get(i).length; ii++) 
                row.add(teamsGroupList.get(i)[ii]);
            
            data.add(row);
		}
		
		viewTeams.setItems(data);
	}
	
	private void saveTeams() throws IOException
	{
		Logging.write("save teams");
		
		for(int i = 0; i < DataHandling.getGroupSize(); i++)
		{
			for(int ii = 1; ii < DataHandling.Prefixes.length; ii++)
			{
				TableColumn col = (TableColumn)viewTeams.getColumns().get(ii);
				teamsGroupList.get(i)[ii] = (String)col.getCellObservableValue(i).getValue();
			}
		}

		DataHandling.writeTeams(teamsGroupList);
		
		loadTeams();
	}
	
	// **************************************************************************
	// ****************************** ui/fxml part ******************************
	// **************************************************************************
	@FXML private MenuItem ExitApplication, ShowDocumentation, ShowAbout;
	@FXML private TableView viewTeams;
		
	@FXML
	private void exitApplication(ActionEvent event)
	{
		pw.close();
		System.exit(0);
	}
	
	@FXML
	private void showDocumentation(ActionEvent event)
	{
	}
	
	@FXML
	private void showAbout(ActionEvent event)
	{
		
	}
	
	@FXML
	private void saveTeams(ActionEvent event) throws IOException
	{
		saveTeams();
	}
	
	@FXML
	private void cleanTeams(ActionEvent event) throws IOException
	{
		resetTeams();
		
		saveTeams();
	}
	
	@FXML
	private void printTeams(ActionEvent event)
	{
		
	}
}
