#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

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
 
 // WiFi.disconnect(true);
  Serial.println(WiFi.localIP());
}



void writeJSON() {
  DynamicJsonDocument  doc(200);
  doc["sensor"] = "gps";
  doc["time"] = 1351824120;
  JsonArray data = doc.createNestedArray("data");
  data.add(48.756080);
  data.add(2.302038);
  String output;
  serializeJsonPretty(doc, output);// You can also use serializeJson(doc, Serial);
  Serial.println(output);
  // The above line prints:
  // {
  //   "sensor": "gps",
  //   "time": 1351824120,
  //   "data": [
  //     48.756080,
  //     2.302038
  //   ]
  // }
}

void readJSON() {
  DynamicJsonDocument doc(1024);
  String input;
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  long time = obj["time"];
  Serial.println(time);
  int firstdata = obj["data"][0]; 
  Serial.println(firstdata);
}

/*void SendGetRequest() {
 if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://jsonplaceholder.typicode.com/posts/1"); //Specify the URL 
    //(A test json server: https://jsonplaceholder.typicode.com/guide.html)
    
    int httpCode = http.GET();     //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        int userId = obj["userId"];
        Serial.println(userId);
      }
 
    else {
      Serial.println("Error on HTTP request Code:"+httpCode);
    }
 
    http.end(); //Free the resources
  }*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  writeJSON();
  readJSON();
  scanNetworks();
  connectToNetwork();

  printWiFiInfo();
}

void loop() {
  // put your main code here, to run repeatedly:
  setup();
}
