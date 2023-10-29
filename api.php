<?php
// Connection to the MySQL database
$servername = "localhost";
$username = "u862223319_pipmechanism";
$password = "Pipmechanism123";
$dbname = "u862223319_pipmechanism";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Check for GET request
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    // Get data from the query parameters
    $float_column1 = $_GET['float_column1'];
    $float_column2 = $_GET['float_column2'];
    $float_column3 = $_GET['float_column3'];

    // Insert data into the database
    $sql = "INSERT INTO your_table_name (float_column1, float_column2, float_column3) VALUES ('$float_column1', '$float_column2', '$float_column3')";

    if ($conn->query($sql) === true) {
        echo "Data inserted successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>
