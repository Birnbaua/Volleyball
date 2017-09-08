package app;
	
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.*;

public class Main extends Application
{	
	@Override
	public void start(Stage primaryStage) throws Exception
	{
		FXMLLoader loader = new FXMLLoader(getClass().getResource("MainUI.fxml"));
		Parent root = loader.load();
		Scene scene = new Scene(root, 1024, 768);
				
		primaryStage.setTitle("Turnierplaner");
		primaryStage.setScene(scene);
		primaryStage.show();		
	}
	
	public static void main(String[] args) 
	{
		launch(args);
	}
}