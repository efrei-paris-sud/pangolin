#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


const char* ssid = "0";
const char* password = "12345678";

void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 

    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    //Serial.print("Encryption type: ");
    //Serial.print(WiFi.encryptionType(i)); the type is  wifi_auth_mode_t
   
    Serial.println("-----------------------");
 
  
  }
}

void connectToNetwork() {
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }
  
  Serial.println("Connected to network");
}

void printWiFiInfo() {
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

}
  
void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  scanNetworks();
  connectToNetwork();
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
  }
  printWiFiInfo();
}
 

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    HTTPClient http;
    DynamicJsonDocument doc(1024);
 
    http.begin("https://samples.openweathermap.org/data/2.5/weather?q=London,uk&appid=b6907d289e10d714a6e88b30761fae22"); //Specify the URL
    int httpCode = http.GET();  //Make the request

    String payload;
    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        delay(120000);
      return;
    }
    // Get the root object in the document
    JsonObject root = doc.as<JsonObject>();

    float temperature = root["main"]["temp"];
    int humidity = root["main"]["humidity"];
    int pressure = root["main"]["pressure"];
        
    Serial.println(humidity);
    delay(2000);
  
    Serial.println(pressure);
    delay(2000);
    temperature = round(temperature);
    Serial.println(temperature);    
    delay(30000);
    } else {
      Serial.println("Error on HTTP request");
      delay(30000);
    }
    http.end(); //Free the resources
  }  
}
