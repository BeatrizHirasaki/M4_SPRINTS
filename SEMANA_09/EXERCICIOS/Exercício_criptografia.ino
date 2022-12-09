#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string>

using namespace std;

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

//Your Domain name with URL path or IP address with path
const char* serverName = "https://ur524n-3000.preview.csb.app/teobaldo";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;

// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      Serial.println("Posting JSON data to server...");
      // Block until we are able to connect to the WiFi access point
      HTTPClient http;   
        
      http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
      http.addHeader("Content-Type", "application/json");         
      
      StaticJsonDocument<200> doc;
      // Add values in the document
      
      doc["nome"] = "Beatriz Hirasaki Leite";
      doc["turma"] = "3";
      doc["grupo"] = "5";
      doc["mensagem"] = "Oi, eu sou a Bia!";
      // algoritmo de criptografia
      string text = doc["mensagem"];
      int key = 10;
      for (int i = 0; i < text.length(); i++)
      {
          if (text[i] >= 'a' && text[i] <= 'z')
          {
              text[i] = (text[i] - 'a' + key) % 26 + 'a';
          }
          else if (text[i] >= 'A' && text[i] <= 'Z')
          {
              text[i] = (text[i] - 'A' + key) % 26 + 'A';
          }
      }

      doc["criptografia"] = text;

      // Add an array.
      JsonArray data = doc.createNestedArray("data");
      
      String requestBody;
      serializeJson(doc, requestBody);
      
      int httpResponseCode = http.POST(requestBody);
  
      if(httpResponseCode>0){
        
        String response = http.getString();                       
        
        Serial.println(httpResponseCode);   
        Serial.println(response);
      
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
