<?php
require_once 'database.php';

// Verificar conexión
if ($conn->connect_error) {
    die("Conexión fallida: " . $conn->connect_error);
}

// Verificar si hay al menos un registro en la tabla
$result = $conn->query("SELECT id FROM sensors ORDER BY id DESC LIMIT 1");

if ($result->num_rows == 0) {
    // Si no hay registros, crea uno por defecto
    $conn->query("INSERT INTO sensors (temperature, humidity) VALUES (0, 0)");
}

// Ahora, obtener los parámetros enviados
if (isset($_GET['temp']) && isset($_GET['hum'])) {
    $temp = floatval($_GET['temp']);
    $hum = floatval($_GET['hum']);

    // Preparar la consulta para actualizar el registro más reciente
    $stmt = $conn->prepare("UPDATE sensors SET temperature = ?, humidity = ? ORDER BY id DESC LIMIT 1");

    if (!$stmt) {
        die("Error en la consulta SQL: " . $conn->error);
    }

    $stmt->bind_param("dd", $temp, $hum);
    $stmt->execute();
    $stmt->close();
}

$conn->close();
?>
