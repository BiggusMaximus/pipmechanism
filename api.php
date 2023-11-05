<?php
// Connection to the MySQL database
$servername = "localhost"; // Replace with your database server name or IP
$username = "u862223319_pipmechanism";
$password = "Pipmechanism123";
$dbname = "u862223319_pipmechanism";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Check for POST request
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Get data from the Python client
    $voltage = test_input($_POST['voltage']);
    $current = test_input($_POST['current']);
    $power   = test_input($_POST['power']);

    // Insert data into the database
    $sql = "INSERT INTO pipmechanism (voltage, current, power) VALUES ('$voltage', '$current', '$power')";
    echo $sql;

    if ($conn->query($sql) === true) {
        echo "Data inserted successfully => ";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

?>
