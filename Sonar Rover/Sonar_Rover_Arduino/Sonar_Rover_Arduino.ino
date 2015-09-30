#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 8); // RX, TX

int en1 = 5;
int en2 = 9;
int mrp = 6;
int mrn = 7;
int mlp = 10;
int mln = 11;
int serv = 3;       //PWM
int trig = 12;
int echo = 2;
Servo servo;


void setup()
{
  Serial.begin(9600);

  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mln, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrn, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(serv, 544, 2480);

   establishContact();
  //delay(100);
  //Serial.println();
  //Serial.write('A');

}


void loop(){
}