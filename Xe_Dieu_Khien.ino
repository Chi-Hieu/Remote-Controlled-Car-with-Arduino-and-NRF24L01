#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int In1 = 2;
int In2 = 3;
int In3 = 4;
int In4 = 5;
int Led = 10;

RF24 radio(7, 8);
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
  radio.openReadingPipe(0, Diachi);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  //pinMode(Led, OUTPUT);
}

void loop() 
{
  if (radio.available()) 
  {
    analogWrite(Led,100);
    radio.read(&data, sizeof(Dulieu));
    if ((data.TienLui > 50) && (data.TienLui < 200)
    && (data.TraiPhai > 50) && (data.TraiPhai < 200))
    {
      digitalWrite(In1, 0);
      digitalWrite(In2, 0);
      digitalWrite(In3, 0);
      digitalWrite(In4, 0);
    }
    if (data.TienLui > 200)
    {
      digitalWrite(In1, 1);
      digitalWrite(In2, 0);
      digitalWrite(In3, 1);
      digitalWrite(In4, 0);
    }
    if (data.TienLui < 50)
    {
      digitalWrite(In1, 0);
      digitalWrite(In2, 1);
      digitalWrite(In3, 0);
      digitalWrite(In4, 1);
    }
    if (data.TraiPhai > 200)
    {
      digitalWrite(In1, 0);
      digitalWrite(In2, 1);
      digitalWrite(In3, 1);
      digitalWrite(In4, 0);
    }
    if (data.TraiPhai < 50)
    {
      digitalWrite(In1, 1);
      digitalWrite(In2, 0);
      digitalWrite(In3, 0);
      digitalWrite(In4, 1);
    }
    Serial.println(data.TienLui);
    Serial.println(data.TraiPhai);
  }
  if (!radio.available()) 
  {
    analogWrite(Led,0);
  }
}
 
