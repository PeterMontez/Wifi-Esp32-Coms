
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Servo.h>

const char* ssid = "Murilindo";
const char* password = "andregato";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String caminho = "padrao";

const char* PARAM_INPUT_1 = "slider";
const char* PARAM_INPUT_2 = "value";

float servo1;
float servo2;
float servo3;
float servo4;

String servos = String(servo1, 1) + String(servo2, 1) + String(servo3, 1) + String(servo4, 1);

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", caminho.c_str());
  });

  server.on("/getservos", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", servos.c_str());
  });

  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
  String inputMessage1;
  String inputMessage2;
  // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
    inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
    inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
    switch(inputMessage1.toInt()){
      case 1:
        servo1 = inputMessage2.toFloat();
        break;
      case 2:
        servo2 = inputMessage2.toFloat();
        break;
      case 3:
        servo3 = inputMessage2.toFloat();
        break;
      case 4:
        servo4 = inputMessage2.toFloat();
        break;
      default:
        break;
    }
    Serial.println(inputMessage2);
    servos = String(servo1, 1) + ";" + String(servo2, 1) + ";" + String(servo3, 1) + ";" + String(servo4, 1);
  }

  request->send(200, "text/plain", inputMessage1 + ";" +  inputMessage2);
  });
  
  // Start server
  server.begin();
}
 
void loop(){
  
}
