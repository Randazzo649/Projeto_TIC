#include <WiFi.h>
#include <HTTPClient.h>

#define PIR_PIN 21
#define LED_PIN 15

const char *ssid = "Laboratorios_Instituição_EXT";
const char *senha = "96252666";

const String url = "...";

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, senha);
  Serial.print("Conectando-se ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
  Serial.println("Calibrando PIR...");
  delay(60000);
  Serial.println("Pronto!");
}

void loop(){
  bool movimento = digitalRead(PIR_PIN);
  if (movimento == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    verificarHora();
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void mandarAlerta(){
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/json");
      String jsonPayload = "{\"movimento\":true}";
      int httpResponseCode = http.POST(jsonPayload);
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Código de resposta: " + String(httpResponseCode));
        Serial.println("Resposta do servidor: " + response);
      } else {
        Serial.println("Erro na requisição. Código: " + String(httpResponseCode));
      }
      http.end();
    }
}