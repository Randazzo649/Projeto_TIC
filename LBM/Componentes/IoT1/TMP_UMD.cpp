
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define PORTA_DHT 2
#define PORTA_LED 4
#define PERIODO_ENVIO 3000
#define SSD "Laboratorios_Instituição_EXT"
#define SENHA "96252666"
#define SERVIDOR String("http://192.168.15.4/LBM")

DHT dht(PORTA_DHT, DHT11);

//OUTRAS FUNÇÕES
void enviar_medicao_ao_servidor(){

  float temp = dht.readTemperature();
  float umd = dht.readHumidity();
  
  HTTPClient http;
  http.begin(SERVIDOR + "/scripts/recebimento_dados.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int code = http.POST("temp="+String(temp)+"&umid="+String(umd)+"");
  http.end();
}

void reconectar_wifi_em_caso_de_queda(){
  if(WiFi.status() != WL_CONNECTED){
    digitalWrite(PORTA_LED, LOW);
    WiFi.disconnect();
    delay(500);
    WiFi.begin(SSD, SENHA);
    while(WiFi.status() != WL_CONNECTED)
      delay(500);
    digitalWrite(PORTA_LED, HIGH);
  }
}

// FUNÇÕES PRINCIPAIS DO PROGRAMA
void setup() {
    Serial.begin(115200);
    pinMode(PORTA_LED, OUTPUT);
    dht.begin();

    WiFi.begin(SSD, SENHA);
    while( WiFi.status() != WL_CONNECTED )
      delay(1000);
    digitalWrite(PORTA_LED, HIGH);
}

void loop() {
    delay(PERIODO_ENVIO);
    enviar_medicao_ao_servidor();
    reconectar_wifi_em_caso_de_queda();
}

