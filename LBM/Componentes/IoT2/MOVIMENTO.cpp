#include <WiFi.h>
#include <HTTPClient.h>

#define PIR_PIN 21
#define LED_PIN 15

const char *ssid = "Laboratorios_Instituição_EXT";
const char *senha = "96252666";

const String url = "http://192.168.1.101/scripts/invasoes.php";

void conectar_wifi(){
  WiFi.begin(ssid, senha);
  Serial.print("Conectando-se ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
}

void reconectar_wifi(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("\ndesconectado");
    WiFi.disconnect();
    delay(500);
    WiFi.begin(ssid, senha);
    while(WiFi.status() != WL_CONNECTED)
      delay(500);
    Serial.print("\nreconectado");
  }
}

void mandar_alerta(){
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

void detectar_movimentar(){
  static bool estadoAnterior = LOW;
  bool movimento = digitalRead(PIR_PIN);
  if (movimento == HIGH && estadoAnterior == LOW) {
    digitalWrite(LED_PIN, HIGH);
    mandarAlerta();
  }
  if (movimento == LOW) 
    digitalWrite(LED_PIN, LOW);
  estadoAnterior = movimento;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  conectar_wifi();
  Serial.println("Calibrando PIR...");
  delay(60000);
  Serial.println("Pronto!");
}

void loop(){
  detectar_movimento();
  reconectar_wifi();
}