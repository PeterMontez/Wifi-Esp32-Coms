#include <WiFi.h>
#include <HTTPClient.h>
#include <Servo.h>

const char* ssid     = "Murilindo";
const char* password = "andregato";

const char* serverIP = "http://192.168.4.1/getservos";

String servosFull;

int servo1;
int servo2;
int servo3;
int servo4;

int IN1 = 4;
int IN2 = 5;
int IN3 = 18;
int IN4 = 19;

static const int servoPin1 = 21; //Garra
static const int servoPin2 = 22; //L - Pulso
static const int servoPin3 = 23; //R - Cutuvelo (Frente e tras)
static const int servoPin4 = 13; //Base

Servo Garra;
Servo Pulso;
Servo Cutuvelo;
Servo Base;

WiFiServer server(80);

void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    STOP();

    Garra.attach(servoPin1);
    Pulso.attach(servoPin2);
    Cutuvelo.attach(servoPin3);
    Base.attach(servoPin4);
    
    Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /FO")) {
          UP();
        }
        if (currentLine.endsWith("GET /FF")) {
          STOP();
        }
        else if (currentLine.endsWith("GET /TO")) {
          DOWN();
        }
        if (currentLine.endsWith("GET /TF")) {
          STOP();
        }
        else if (currentLine.endsWith("GET /DO")) {
          RIGHT();
        }
        if (currentLine.endsWith("GET /DF")) {
          STOP();
        }
        if (currentLine.endsWith("GET /EO")) {
          LEFT();
        }
        if (currentLine.endsWith("GET /EF")) {
          STOP();
        }
        if (currentLine.endsWith("GET /US")) {
          getServos();
          moveServos();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void STOP()
{
  digitalWrite(IN1, LOW); //RIGHT
  digitalWrite(IN2, LOW); //RIGHT
  digitalWrite(IN3, LOW); //LEFT
  digitalWrite(IN4, LOW); //LEFT
}

void UP()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void DOWN()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void RIGHT()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void LEFT()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void getServos()
{
  Serial.println("ENTROU NA FUNCAO");
  servosFull = httpGETRequest(serverIP);
  Serial.println(servosFull);
}

void moveServos()
{
  
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
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
