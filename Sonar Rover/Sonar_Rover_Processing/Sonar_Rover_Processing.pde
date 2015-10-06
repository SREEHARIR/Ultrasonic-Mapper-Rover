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
