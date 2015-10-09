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


void drawRadar() 
{
  frame.setTitle("RADAR");
  background(0, 0, 0, 0);
  fill(255);

  for (int i=0; i<91; i++)
  {

    alphaVal[i]=alphaVal[i]-4;

    if (alphaVal[i]<0)
    {
      alphaVal[i]=0;
    }

    stroke(255, distance2[i], 0, alphaVal[i]);

    strokeWeight(2);
    line(width/2, height, (width/2)-cos(radians((90-i)*2))*(distance2[i]*lineSize), height-sin(radians((90-i)*2))*(distance2[i]*lineSize));

    stroke(255, 255, 255, alphaVal[i]);
    strokeWeight(1);
    ellipse((width/2)-cos(radians((90-i)*2))*(distance2[i]*lineSize), height-sin(radians((90-i)*2))*(distance2[i]*lineSize), 5, 5);
  }
}

void updateRadar ()
{
  alphaVal[pos/2] = 180;
  distance2[pos/2] = dista;
  distance2[pos/2] = int(map((distance2[pos/2]), 1, 255, 1, height));

}
void drawRoom() 
{
  frame.setTitle("ROOM");
  background(0);
  fill(55,175,15,255);
  stroke(255);
  strokeWeight(2);
  ellipse(posix, posiy, 5, 5);
  constrain(trn,0,100);
  for(int i=1;i<trn;i++)
  {
    stroke(170,25,25,255);
    strokeWeight(2);
    line(turnx[i-1], turny[i-1], turnx[i], turny[i]);
  }
  stroke(50,250,200,255);
  line(turnx[trn],turny[trn],posix,posiy);
}

void updateroom()
{
  switch(direc)
  {
  case 0:
  //  c0+=travel;
  //  if (c0==scale)
    {
      posiy-=travel;
      c0=0;
      if(cp!=0)
      {
        turnx[trn]=posix;
        turny[trn]=posiy;
        trn++;
        cp=0;
      }
    }
    break;
  case 1:
   // c1+=travel;
   // if (c1==scale)
    {
      posix+=travel;
      c1=0;
      if(cp!=1)
      {
        turnx[trn]=posix;
        turny[trn]=posiy;
        trn++;
        cp=1;
      }
    }
    break;
  case 2:
 //   c2+=travel;
 //   if (c2==scale)
    {
      posiy+=travel;
      c2=0;
      if(cp!=2)
      {
        turnx[trn]=posix;
        turny[trn]=posiy;
        trn++;
        cp=2;
      }
    }
    break;
  case 3:
 //   c3+=travel;
 //   if (c3==scale)
    {
      posix-=travel;
      c3=0;
      if(cp!=3)
      {
        turnx[trn]=posix;
        turny[trn]=posiy;
        trn++;
        cp=3;
      }
    }
    break;
  }
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
