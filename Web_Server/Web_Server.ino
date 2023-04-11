#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Murilindo";
const char* password = "andregato";

//Your IP address or domain name with URL path
const char* serverNameTemp = "http://192.168.4.1/teste1";
const char* serverNameHumi = "http://192.168.4.1/teste2";
const char* serverNamePres = "http://192.168.4.1/teste1";

String temperature;
String humidity;
String pressure;

unsigned long previousMillis = 0;
const long interval = 5000;

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
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      temperature = httpGETRequest(serverNameTemp);
      humidity = httpGETRequest(serverNameHumi);
      pressure = httpGETRequest(serverNamePres);
      Serial.println("Temperature: " + temperature + " *C - Humidity: " + humidity + " % - Pressure: " + pressure + " hPa");
      
      display.clearDisplay();
      
      // display temperature
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("T: ");
      display.print(temperature);
      display.print(" ");
      display.setTextSize(1);
      display.cp437(true);
      display.write(248);
      display.setTextSize(2);
      display.print("C");
      
      // display humidity
      display.setTextSize(2);
      display.setCursor(0, 25);
      display.print("H: ");
      display.print(humidity);
      display.print(" %"); 
      
      // display pressure
      display.setTextSize(2);
      display.setCursor(0, 50);
      display.print("P:");
      display.print(pressure);
      display.setTextSize(1);
      display.setCursor(110, 56);
      display.print("hPa");
           
      display.display();
      
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
