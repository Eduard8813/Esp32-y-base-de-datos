<?php
require_once 'database.php';

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

// Obtener datos de la URL
$temp1 = $_GET['temp1'];
$hum1 = $_GET['hum1'];
$temp2 = $_GET['temp2'];
$hum2 = $_GET['hum2'];

// Insertar datos en la base de datos
$sql = "INSERT INTO readings (temperature, humidity) VALUES ($temp1, $hum1), ($temp2, $hum2)";

if ($conn->query($sql) === TRUE) {
    echo "Datos guardados correctamente";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>