#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "Murilindo";
const char* password = "andregato";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String teste1 = "teste1";
String teste2 = "teste2";
String caminho = "padrao";

float SliderTemp;
float Servo1;
float Servo2;
float Servo3;
float Servo4;

String servosState = "";

const char* PARAM_INPUT_1 = "servo";
const char* PARAM_INPUT_2 = "value";

void setup(){
  pinMode(2, OUTPUT);
  
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
  
  server.on("/teste1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", teste1.c_str());
  });
  
  server.on("/teste2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", teste2.c_str());
  });

  server.on("/teste2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", teste2.c_str());
  });

  server.on("/H", HTTP_GET, [](AsyncWebServerRequest *request){
    ledOn();
    request->send_P(200, "text/plain", teste1.c_str());
  });

  server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
    ledOff();
    request->send_P(200, "text/plain", teste1.c_str());
  });

  server.on("/servos", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String servo;
    String value;
    int servoSlc;
    // GET input1 value on <ESP_IP>/servos?slider=<inputMessage1>&value=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      servo = request->getParam(PARAM_INPUT_1)->value();
      value = request->getParam(PARAM_INPUT_2)->value();
      
      SliderTemp = value.toFloat();
      servoSlc = servo.toInt();
      
      switch(servoSlc)
      {
        case 1:
          Servo1 = SliderTemp;
          break;
        case 2:
          Servo2 = SliderTemp;
          break;
        case 3:
          Servo3 = SliderTemp;
          break;
        case 4:
          Servo4 = SliderTemp;
          break;
        default:
          break;
      }
      
    }
    request->send(200, "text/plain", servo);
  });

  server.on("/getservos", HTTP_GET, [](AsyncWebServerRequest *request){
    servosState = (String(Servo1) + (String)Servo2 + (String)Servo3 + (String)Servo4);
    request->send_P(200, "text/plain", servosState.c_str());
  });
  
  // Start server
  server.begin();
}

void ledOn(){
  digitalWrite(2, HIGH);
}

void ledOff(){
  digitalWrite(2, LOW);
}

void loop(){
  
}
