#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
const int trig = 5;
const int echo = 6;

int msg[1]={000};
RF24 radio(9,10);
const uint64_t pipe = 0xE6E6E6E6E6E6;

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;
  Serial.println (distance);
  
  if (distance < 10){
    msg[0] = 111;
    radio.write(msg, 1);
    }
   else {
    msg[0] = 000;
    radio.write(msg, 1);
   }
}
