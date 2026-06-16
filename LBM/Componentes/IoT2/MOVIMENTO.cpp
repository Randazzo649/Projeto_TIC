#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

#define PIR_PIN 21
#define LED_PIN 15

const char *ssid = "SEU WIFI";
const char *senha = "SUA SENHA";

const String url = "...";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -10800;
const int   daylightOffset_sec = 0;

String dataalerta = "";

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
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  Serial.println("Calibrando PIR...");
  delay(60000);
  Serial.println("Pronto!");
}

void loop(){
  bool movimento = digitalRead(PIR_PIN);
  if (movimento == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    mandarAlerta();
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void pegarData(){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    String jsonPayload = "{\"movimento\":true,\"data_movimento\":\"" + montarData() + "\"}";
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

void mandarAlerta(){
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/json");
      String jsonPayload = "{\"movimento:\" true, \"data de movimento:\""+ montarData() + "}";
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

String montarData(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  char buffer[80];
  strftime(buffer,sizeof(buffer),"%d/%m/%Y %H:%M:%S",&timeinfo);
  dataalerta = String(buffer);
  return dataalerta;
}