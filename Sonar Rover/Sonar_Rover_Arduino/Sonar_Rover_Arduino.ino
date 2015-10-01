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


void left()
{
  //analogWrite(en1, en1turn);
  //analogWrite(en2, en2turn);
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);  
  digitalWrite(mlp, HIGH);
  digitalWrite(mln, LOW);
  digitalWrite(mrp, LOW);
  digitalWrite(mrn, HIGH);
  delay(leftdelay);
  stop();
  direc--;
  travel = 0;
  if (direc < 0)
  {
    direc = 3;
  }
  //Serial.println("LEFT TURN");
}

void right()
{
//  analogWrite(en1, en1turn);
//  analogWrite(en2, en2turn);
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(mlp, LOW);
  digitalWrite(mln, HIGH);
  digitalWrite(mrp, HIGH);
  digitalWrite(mrn, LOW);
  delay(rightdelay);
  stop();
  direc++;
  travel = 0;
  if (direc > 3)
  {
    direc = 0;
  }
  //Serial.println("RIGHT TURN");
}

void forward()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(mlp, HIGH);
  digitalWrite(mln, LOW);
  digitalWrite(mrp, HIGH);
  digitalWrite(mrn, LOW);
  delay(forwdelay);
  //stop();
  travel = 10; //10cm
  //Serial.println("FORWARD");
}

void backward()
{
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(mlp, LOW);
  digitalWrite(mln, HIGH);
  digitalWrite(mrp, LOW);
  digitalWrite(mrn, HIGH);
  delay(backdelay);
  stop();
  travel = 5; //10cm
  //Serial.println("BACKWARD");
}

void stop()
{
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite(mlp, LOW);
  digitalWrite(mln, LOW);
  digitalWrite(mrp, LOW);
  digitalWrite(mrn, LOW);
}
