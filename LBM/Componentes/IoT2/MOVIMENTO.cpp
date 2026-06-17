#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

#define PIR_PIN 21
#define LED_PIN 15

const char *ssid = "Laboratorios_Instituição_EXT";
const char *senha = "96252666";

const String url = "...";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -10800;
const int   daylightOffset_sec = 0;

String dataI = "08:00:00";
String dataF = "17:00:00";

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
    verificarHora();
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void verificarHora(){
  String dataA = pegarHora();
  if(dataA < dataI || dataA > dataF){
    mandarAlerta();
    digitalWrite(LED_PIN, HIGH);
  }
}

void mandarAlerta(){
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/json");
      String jsonPayload = "{\"movimento\":true,\"data_movimento\":\"" + pegarHora() + "\"}";
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

String pegarHora(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "";
  }
  char buffer[80];
  strftime(buffer,sizeof(buffer),"%H:%M:%S",&timeinfo);
  return String(buffer);
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Falha ao obter horário");
    return;
  }
  Serial.println(&timeinfo, "%d/%m/%Y %H:%M:%S");
}