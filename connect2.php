<?php
// menghubungkan db mysql
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "pip_data";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// ambil data db
$sql = "SELECT voltage, current, power FROM data";
$result = $conn->query($sql);
$row = $result->fetch_assoc();

// menyimpan data
$voltage = $row['voltage'];
$current = $row['current'];
$power = $row['power'];

$conn->close();
?>

