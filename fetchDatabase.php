<?php
// Your database connection details
$servername = "localhost"; // Replace with your database server name or IP
$username = "u862223319_pipmechanism";
$password = "Pipmechanism123";
$dbname = "u862223319_pipmechanism";
$tablename = "pipmechanism";

try {
    $pdo = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
    exit();
}

// Query to fetch the latest data (assuming you have a timestamp field 'timestamp_column' for ordering)
$query = $pdo->query("SELECT voltage, current, power FROM $tablename ORDER BY id DESC LIMIT 1");
$data = $query->fetch(PDO::FETCH_ASSOC);

// Send the data as JSON
header('Content-Type: application/json');
echo json_encode($data);
?>
