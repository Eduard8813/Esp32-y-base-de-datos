#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

// Configuración WiFi
const char* ssid = "Familia Mora";
const char* password = "88136473";

// Definir pines del sensor DHT
#define DHTPIN1 4

// Definir tipo de sensor
#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("\nConectado a WiFi!");
  dht1.begin();
}

void loop() {
  float temperature1 = dht1.readTemperature();
  float humidity1 = dht1.readHumidity();

  if (isnan(temperature1) || isnan(humidity1)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature1);
  Serial.print("°C, Hum: ");
  Serial.print(humidity1);
  Serial.println("%");

  // Construir la URL correctamente
  String serverUrl = "http://192.168.0.18/insert.php?temp=" + String(temperature1) + "&hum=" + String(humidity1);
  
  HTTPClient http;
  http.begin(serverUrl);

  int httpCode = http.GET();
  
  if (httpCode > 0) {
    Serial.print("Respuesta del servidor: ");
    Serial.println(http.getString());
  } else {
    Serial.print("Error en solicitud HTTP: ");
    Serial.println(httpCode);
  }

  http.end();
  delay(10000); // Espera 10 segundos antes de enviar nuevamente
}
