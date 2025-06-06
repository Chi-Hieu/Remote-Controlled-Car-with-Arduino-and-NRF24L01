#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int NutA = 2;
int NutB = 3;
int NutC = 4;
int NutD = 5;
int NutE = 6;
int NutF = 7;
int NutG = 8;
int JoystickX = A1;
int JoystickY = A0;
int TienLui,TraiPhai,Mode;

RF24 radio(9, 10);
const byte Diachi[6] = "00112";

struct Dulieu 
{
  byte TienLui;
  byte TraiPhai;
};
Dulieu data;

void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(Diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(NutA, INPUT_PULLUP);
  pinMode(NutB, INPUT_PULLUP);
  pinMode(NutC, INPUT_PULLUP);
  pinMode(NutD, INPUT_PULLUP);
  pinMode(NutE, INPUT_PULLUP);
  pinMode(NutF, INPUT_PULLUP);
  pinMode(NutG, INPUT_PULLUP);
  Mode = 1;
}

void Joystick()
{
  TienLui = map(analogRead(JoystickX), 0, 1023, 0, 255);
  TraiPhai = map(analogRead(JoystickY), 0, 1023, 0, 255);
}
void NutNhan()
{
  TienLui = 127;
  TraiPhai = 127;
  if (digitalRead(NutA) == 0)
  {
    TienLui = 255;
  }
  if (digitalRead(NutC) == 0)
  {
    TienLui = 0;
  }
  if (digitalRead(NutB) == 0)
  {
    TraiPhai = 255;
  }
  if (digitalRead(NutD) == 0)
  {
    TraiPhai = 0;
  }
}
void loop() 
{
  if (digitalRead(NutF) == 0)
  {
    Mode = 2;
  }
  if (digitalRead(NutE) == 0)
  {
    Mode = 1;
  }
  if (Mode == 2)
  {
    Joystick();
  }
  else
  {
    NutNhan();
  }
  data.TienLui = TienLui;
  data.TraiPhai = TraiPhai;
  radio.write(&data, sizeof(Dulieu));
  Serial.println(data.TienLui);
  Serial.println(data.TraiPhai);
}
