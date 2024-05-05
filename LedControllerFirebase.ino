#include <ESP32Firebase.h>

#define WIFI_SSID "PrivateNetwork"          // Nombre de tu red WiFi
#define WIFI_PASSWORD "jsuh9900"      // Contraseña de tu red WiFi
#define FIREBASE_URL "specchtotextesp32-default-rtdb.firebaseio.com"  // URL de referencia de tu proyecto Firebase

#define LED_PIN 22 // Pin del LED

Firebase firebase(FIREBASE_URL);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Conectar a WiFi
  Serial.println("Conectando a la red WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int wifiConnectAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiConnectAttempts < 20) { // Intenta conectarse durante un máximo de 10 segundos
    delay(500);
    Serial.print(".");
    wifiConnectAttempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n¡Error al conectar a la red WiFi!");
    while (1) {} // Bucle infinito si no se puede conectar a la red WiFi
  }

  Serial.println("\nConexión WiFi establecida");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int command = firebase.getInt("comando/message"); // Obtener datos de la base de datos Firebase
  Serial.println("comando ...");
  Serial.println(command);

  if (command == 0) { // Detener
    digitalWrite(LED_PIN, LOW);
  }

  if (command == 1) { // Encender LED
    digitalWrite(LED_PIN, HIGH);
  }

  // Esperar un tiempo antes de consultar Firebase nuevamente (evita el acceso excesivo a la base de datos)
  delay(1000);
}
