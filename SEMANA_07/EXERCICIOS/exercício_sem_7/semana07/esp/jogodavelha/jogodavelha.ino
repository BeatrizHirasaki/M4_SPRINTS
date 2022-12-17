#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>

#define LEDX 21
#define LEDEMPATE 47
#define LEDO 48

String serverURL = "SERVER_URL";

void initWiFi(char* _ssid, char* _password) {
  WiFi.begin(_ssid, _password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected to Wi-Fi Network ");
  Serial.println(_ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


String getvencedor() {
  String vencedoratual = "0";

  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;

    String serverPath = serverURL + "/VENCEDOR";
    
    http.begin(serverPath.c_str());
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      vencedoratual = payload;
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  return vencedoratual;
}

void setup() {
  Serial.begin(115200);

  pinMode(LEDX, OUTPUT);
  pinMode(LEDO, OUTPUT);
  pinMode(LEDEMPATE, OUTPUT);

  WiFi.begin(SSID, SENHA);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected to Wi-Fi Network ");
  Serial.println(_ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  String vencedor = getvencedor();

  if (vencedor == "0") {
      digitalWrite(LEDX, LOW);
      digitalWrite(LEDO, LOW);
      digitalWrite(LEDEMPATE, LOW);
  } else if (vencedor == "1"){
      digitalWrite(LEDX, HIGH);
  } else if (vencedor == "2"){
      digitalWrite(LEDO, HIGH);
  } else if (vencedor == "3") {
      digitalWrite(LEDEMPATE, HIGH);
  }

  delay(1000);
}