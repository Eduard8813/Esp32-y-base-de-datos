<?php
require_once 'database.php';

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

// Verificar si los parámetros fueron enviados
if (isset($_GET['temp']) && isset($_GET['hum'])) {
    $temp = floatval($_GET['temp']);
    $hum = floatval($_GET['hum']);

    // Preparar la consulta para actualizar los datos en lugar de insertarlos
    $stmt = $conn->prepare("UPDATE sensors SET temperature = ?, humidity = ? ORDER BY id DESC LIMIT 1");
    
    if ($stmt) {
        $stmt->bind_param("dd", $temp, $hum);
        $stmt->execute();
        $stmt->close();
    }
}

$conn->close();
?>


