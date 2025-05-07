#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

// Configuración WiFi
const char* ssid = "The kind ";
const char* password = "88136473";

// Definir pines de los sensores DHT
#define DHTPIN1 14  // Sensor 1 en GPIO 14
#define DHTPIN2 12  // Sensor 2 en GPIO 12

// Definir tipo de sensor
#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  dht1.begin();
  dht2.begin();
}

void loop() {
  float temperature1 = dht1.readTemperature();
  float humidity1 = dht1.readHumidity();
  float temperature2 = dht2.readTemperature();
  float humidity2 = dht2.readHumidity();

  if (isnan(temperature1) || isnan(humidity1) || isnan(temperature2) || isnan(humidity2)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

  Serial.print("Temperatura 1: ");
  Serial.print(temperature1);
  Serial.print(" °C, Humedad 1: ");
  Serial.print(humidity1);
  Serial.println(" %");

  Serial.print("Temperatura 2: ");
  Serial.print(temperature2);
  Serial.print(" °C, Humedad 2: ");
  Serial.print(humidity2);
  Serial.println(" %");

  // Enviar datos al servidor web (PHP)
  HTTPClient http;
  http.begin("http://localhost/base/insert.php" + String(temperature1) + "&hum1=" + String(humidity1) + "&temp2=" + String(temperature2) + "&hum2=" + String(humidity2));
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("Datos enviados al servidor");
  } else {
    Serial.println("Error en la solicitud HTTP");
  }

  http.end();
  delay(10000); // Espera 10 segundos antes de enviar nuevamente
}
