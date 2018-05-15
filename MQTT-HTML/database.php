<?php
	$servername = "timodebimo.nl";
	$username = "timodebimo_admin";
	$password = "Koffie1";
	$dbname = "timodebimo_coffeemaker";

	//Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	//Check connection
	if($conn->connect_error){
		die("Connection failed: " . $conn->connect_error);
	}

	$sql = "SELECT * FROM Drinks";
	$result = $conn->query($sql);
	echo $result;
	$conn->close();
?>
