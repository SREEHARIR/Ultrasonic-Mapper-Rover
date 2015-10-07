import processing.serial.*;

int currentScreen = 0;

int distance; 
int direction = 1;
int angle = 0;

int dista = 0;
int pos = 0;
int travel = 0;
int direc = 1;

int[] alphaVal = new int[100];
int[] distance2 = new int[100];
int lineSize = 4;

boolean firstContact = false;
int[] serialInArray = new int[4];    // Where we'll put what we receive
int serialCount = 0;  


int[] turnx= new int[100];
int[] turny= new int[100];
int posix = 0;
int posiy = 0;
int scale = 4;
int c0 = 0, c1 = 0, c2 = 0, c3 = 0, cp = -1;
int trn = 0;

Serial comPort;

void setup()
{
  size(displayWidth-250, displayHeight-100);

  posix = width/2;
  posiy = height - 10;
  
  for(int i=0;i<100;i++)
  {
    turnx[i]=width/2;
    turny[i]=height -10;
  }

  smooth();
  background(0);

  comPort = new Serial(this, "COM4", 9600);
  //comPort.bufferUntil('\n');
}


void serialEvent(Serial myPort)
{
 myPort.write('A');
 //println('A');
  int inByte = myPort.read();
//  int x = inByte;
  if (firstContact == false)
  {
    if (inByte == 'A')
    { 
      myPort.clear();          // clear the serial port buffer 
      firstContact = true;     // you've had first contact from the microcontroller
      myPort.write('A');       // ask for more
      println('A');
    }
  } else //if(x == 'B')
  {
 //   myPort.clear();
    // Add the latest byte from the serial port to array:
    serialInArray[serialCount] = inByte;
    serialCount++;

    // If we have 4 bytes:
    if (serialCount > 3 ) 
    {
      dista = serialInArray[0];
      pos = serialInArray[1];
      direc = serialInArray[2];
      travel = serialInArray[3];

      updateRadar();
      updateroom();

      // print the values (for debugging purposes only):
      println(dista + "\t" + pos + "\t" + direc + "\t" + travel);

      // Send a capital A to request new sensor readings:
      myPort.write('A');
      println('A');
      // Reset serialCount:
      serialCount = 0;
    }
  }
}
