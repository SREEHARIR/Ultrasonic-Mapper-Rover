#include <Servo.h> 


Servo servo1;

static const int minAngle = 0;
static const int maxAngle = 180;
int servoAngle;
int servoPos;
int servoPin = 9;



#define echoPin 2
#define trigPin 12
#define LEDPin 13
long duration;
long HR_dist=0;
int HR_angle=0;
int HR_dir=1; 
int minimumRange=2; 
int maximumRange=500;

/*--------------------SETUP()------------------------*/
void setup() {
 
 Serial.begin (9600);
 
 servo1.attach(servoPin);
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT);
}

/*----------------------LOOP()--------------------------*/
void loop() { 
 
 if (Serial.available()) {
 
 HR_angle = Serial.parseInt();
 
 if(HR_angle>-1){
 
 servoPos = constrain(map(HR_angle, 0,180,minAngle,maxAngle),minAngle,maxAngle);
 servo1.write(servoPos);
 
 getDistance();
 }
 }
}

/*--------------------getDistance() FUNCTION ---------------*/
void getDistance(){ 
 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 HR_dist = duration/58.2;
 
 if (HR_dist >= maximumRange || HR_dist <= minimumRange){
   
 Serial.println("0");
 digitalWrite(LEDPin, HIGH); 
 } else {
 
 Serial.println(HR_dist);
 digitalWrite(LEDPin, LOW);
 }
}
