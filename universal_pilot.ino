/*
  Arduino Wireless Communication
      - Sender Code
  by Mikołaj Muller
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//radio
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
char text[20];
byte valueToSend[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//input
const int joyLeftYPin = 0;
const int joyLeftXPin = 1;
const int joyLeftSwPin = 8;

const int joyRightYPin = 2;
const int joyRightXPin = 3;
const int joyRightSwPin = 7;

const int potentLefPin = 4;
const int potentRightPin = 5;


void setup() {
  Serial.begin(9600);

  pinMode(joyLeftSwPin, INPUT_PULLUP);
  pinMode(joyRightSwPin, INPUT_PULLUP);

  // radio setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  valueToSend[0] = mapToByte(analogRead(joyLeftYPin));
  valueToSend[1] = mapToByte(analogRead(joyLeftXPin));
  valueToSend[2] = !digitalRead(joyLeftSwPin);

  valueToSend[3] = mapToByte(analogRead(joyRightYPin));
  valueToSend[4] = mapToByte(analogRead(joyRightXPin));
  valueToSend[5] = !digitalRead(joyRightSwPin);

  valueToSend[6] = mapToByte(analogRead(potentLefPin));
  valueToSend[7] = mapToByte(analogRead(potentRightPin));

  printSendValue(valueToSend);

  radio.write(&valueToSend, sizeof(valueToSend));
//  delay(100);
}

byte mapToByte(int v) {
  return map(v, 0, 1023, 0, 255);
}

void printSendValue(byte* t) {
  Serial.print("joyLeftX=");
  Serial.print(t[0]);
  Serial.print(" joyLeftY=");
  Serial.print(t[1]);
  Serial.print(" joyLeftclick=");
  Serial.print(t[2]);

  Serial.print(" joyRighttX=");
  Serial.print(t[3]);
  Serial.print(" joyRightY=");
  Serial.print(t[4]);
  Serial.print(" joyRightclick=");
  Serial.print(t[5]);

  Serial.print(" potentLefttPin=");
  Serial.print(t[6]);
  Serial.print(" potentRightPin=");
  Serial.print(t[7]);
  Serial.println();
}
