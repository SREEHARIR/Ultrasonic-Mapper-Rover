import processing.serial.*;

int distance;
int angle=0;
int direction=1;

int[] alphaVal = new int[100];
int[] distance2 = new int[100];
int lineSize = 4;

String comPortString;
Serial comPort;

/*---------------------SETUP---------------------------*/
void setup( ) {
 size(displayWidth-300,displayHeight-300);
 smooth();
 background(0);
 

 comPort = new Serial(this, "COM8", 9600);
 comPort.bufferUntil('\n');
 
 for(int i=0; i<91; i++){
 alphaVal[i] = 0;
 }
}
 
/*---------------------DRAW-----------------*/
void draw( ) {
 background(0);
 
 for(int i=0; i<91; i++){
 
 alphaVal[i]=alphaVal[i]-4;
 
 if(alphaVal[i]<0){
 alphaVal[i]=0;
 }
 
 stroke(255,distance2[i],0,alphaVal[i]);
 
 strokeWeight(2);
 line(width/2, height, (width/2)-cos(radians(i*2))*(distance2[i]*lineSize), height-sin(radians(i*2))*(distance2[i]*lineSize));
 
 stroke(255);
 strokeWeight(1);
 ellipse((width/2)-cos(radians(i*2))*(distance2[i]*lineSize), height-sin(radians(i*2))*(distance2[i]*lineSize),5,5);
 }
}

void mousePressed(){
 sendAngle();
}

void serialEvent(Serial cPort){
 comPortString = cPort.readStringUntil('\n');
 if(comPortString != null) {
 comPortString=trim(comPortString);
 
 distance = int(map(Integer.parseInt(comPortString),1,200,1,height));
 drawSonar(angle,distance);
 
 sendAngle();
 }
}

/*---------------------------sendAngle() FUNCTION----------------*/
void sendAngle(){
 comPort.write((180-angle)+".");
 
 angle=angle+(2*direction);
 if(angle>178||angle<1){
 direction=direction*-1;
 }
}

/*-----------------sketchFullScreen(): Allows for FullScreen view------*/
boolean sketchFullScreen() {
 return false;
}

/*----------------- drawSonar(): update the line/dot positions---------*/
void drawSonar(int sonAngle, int newDist){
 alphaVal[sonAngle/2] = 180;
 distance2[sonAngle/2] = newDist;
}
