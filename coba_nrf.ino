#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include <Servo.h>
#define led 3
#define buz 4

int recvmsg[1] = {000};

RF24 radio(9,10);
Servo myservo;

const uint64_t pipe = 0xE6E6E6E6E6E6L;
int pos = 0;
void setup() {
  // put your setup code here, to run once:
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  myservo.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (radio.available()){
    radio.read(recvmsg, 1);
    if (recvmsg[0] == 111){
      digitalWrite(led, HIGH);
      digitalWrite(buz, HIGH);
      for(pos = 0; pos<180; pos +=1){
        myservo.write(pos);
        
      }
      }  
    else if(recvmsg[0] == 000){
      digitalWrite(led, LOW);
      digitalWrite(buz, LOW);
        pos = 0;
        myservo.write(pos);
        delay(100);
      }
    }
}
