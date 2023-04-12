//Programa : Controle 2 motores DC usando Ponte H L298N
//Autor : MakerHero
 
//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 5;
int IN2 = 18;
int IN3 = 19;
int IN4 = 21;

const int BotaoU = 23;
const int BotaoR = 22;
const int BotaoL = 15;
const int BotaoD = 4;

int estadoU;
int estadoR;
int estadoL;
int estadoD;
  
void setup()
{
  //Define os pinos como saida
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(BotaoU, INPUT);
 pinMode(BotaoR, INPUT);
 pinMode(BotaoL, INPUT);
 pinMode(BotaoD, INPUT);
 
}
  
void loop()
{
  estadoU = digitalRead(BotaoU);
  estadoR = digitalRead(BotaoR);
  estadoL = digitalRead(BotaoL);
  estadoD = digitalRead(BotaoD);
digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  
//  if (estadoU  == LOW)
//  {
//    UP();
//  }
//  else if(estadoR  == LOW)
//  {
//    RIGHT();
//  }
//  else if(estadoL  == LOW)
//  {
//    LEFT();
//  }
//  else if(estadoD  == LOW)
//  {
//    DOWN();
//  }
//  else
//  {
//    STOP();
//  }
// //Gira o Motor A no sentido horario
// digitalWrite(IN1, HIGH);
// digitalWrite(IN2, LOW);
// delay(2000);
// //Para o motor A
// digitalWrite(IN1, HIGH);
// digitalWrite(IN2, HIGH);
// delay(500);
// //Gira o Motor B no sentido horario
// digitalWrite(IN3, HIGH);
// digitalWrite(IN4, LOW);
// delay(2000);
// //Para o motor B
// digitalWrite(IN3, HIGH);
// digitalWrite(IN4, HIGH);
// delay(500);
// 
// //Gira o Motor A no sentido anti-horario
// digitalWrite(IN1, LOW);
// digitalWrite(IN2, HIGH);
// delay(2000);
// //Para o motor A
// digitalWrite(IN1, HIGH);
// digitalWrite(IN2, HIGH);
// delay(500);
// //Gira o Motor B no sentido anti-horario
// digitalWrite(IN3, LOW);
// digitalWrite(IN4, HIGH);
// delay(2000);
// //Para o motor B
// digitalWrite(IN3, HIGH);
// digitalWrite(IN4, HIGH);
// delay(500);
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
