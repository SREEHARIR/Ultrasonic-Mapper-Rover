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

unsigned long dist[181];
long distleft;
long distright;
long distforw;
int leftdelay = 200;
int rightdelay = 200;
int forwdelay = 100;
int backdelay = 100;
int en1turn = 200;
int en2turn = 200;
int objleft = 0;
int objright = 0;
int objforw = 0;
int objback = 0;
int pos = 0;
int direc = 0;      //0-forw,1-right,2-back,3-left
int travel = 0;
int forwthresh = 50;
int leftthresh = 30;
int rightthresh = 30;

int sweepinc = 3;

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

void loop()
{
  //int x = distance();
//  left();
  //right();
  //forward();
  //backward();
  obstacle_avoid();
  // sweep();

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

void obstacle_avoid()
{
  int i = 0;
  sweep();
  for (i = 0; i < 60; i++)
  {
    distright += dist[i];
    distforw += dist[i + 60];
    distleft += dist[i + 120];
  }
  distforw /= 20;
  distleft /= 20;
  distright /= 20;

  if (distleft < leftthresh)
  {
    objleft = 1;
  }
  else
  {
    objleft = 0;
  }
  //Serial.print("distleft");
  //Serial.println(distleft);
  if (distright < rightthresh)
  {
    objright = 1;
  }
  else
  {
    objright = 0;
  }
  //Serial.print("distright");
  //Serial.println(distright);
  if (distforw < forwthresh)
  {
    objforw = 1;
  }
  else
  {
    objforw = 0;
  }
  //Serial.print("distforw");
  //Serial.println(distforw);
  if (objforw == 1)
  {
    if (objleft == 1)
    {
      if (objright == 1)
      {
        backward();
      }
      else
      {
        right();
      }
    }
    else
    {
      left();
    }
  }
  else
  {
    forward();
  }
}

void sweep()
{
  int sw_delay = 2;
//  for (pos = 0; pos <= 180; pos++)
//  {
//    servo.write(pos);
//    distance();
//    //delay(sw_delay);
//    //Serial.println(pos);
//  }
//  
  A:
  pos = pos + sweepinc;
  servo.write(pos);
  distance();
  if (pos == 0 || pos == 180) {
    sweepinc = -sweepinc ;
  }
  else 
  {
    goto A;
  }
//
//  for (pos = 0; pos >= 0; pos--)
//  {
//    servo.write(pos);
//    distance();
//    //delay(sw_delay);
//    //Serial.println(pos);
//  }
}

long distance()
{
  unsigned long dista = 0, duration = 0;
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  dista = duration / 29.1 / 2;
  dist[pos] = dista;
  delay(5);

 // if (Serial.available())
  {
   // if (Serial.read() == 'A')
    {
      //   Serial.read();
      // Serial.write('B');
      //Serial.println();
      //Serial.println(duration);
      Serial.write(dista);
      //Serial.println(dista);
      Serial.write(pos);
      //Serial.println(pos);
      Serial.write(direc);
      //Serial.println(direc);
      Serial.write(travel);
      //Serial.println(travel
      //Serial.println("cm");
      travel = 0;
    }
  }

}

void establishContact() {
  while (Serial.read() != 'A')
  {
    //mySerial.write('A');   // send a capital A
    Serial.write('A');
    delay(300);
  }
}
