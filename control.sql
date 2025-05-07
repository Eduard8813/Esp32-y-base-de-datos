-- Crear la base de datos
CREATE DATABASE IF NOT EXISTS prueba;

-- Usar la base de datos creada
USE prueba;

-- Crear la tabla users
CREATE TABLE sensors (
  id INT PRIMARY KEY AUTO_INCREMENT,
  temperature FLOAT,
  humidity FLOAT
);