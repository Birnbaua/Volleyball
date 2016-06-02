<?php
	header('Access-Control-Allow-Origin: *');
    if(isset($_GET["query"]))
	{
		try
		{
			$db = new PDO("sqlite:database.db");
			$query = $db->prepare($_GET["query"]);
			$query->execute();
			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			echo json_encode($result);
		}
		catch(PDOException $e)
		{
			echo $e->getMessage();
		}
	}
?>