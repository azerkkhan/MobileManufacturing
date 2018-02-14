//Arm 5
//Sequence 3
//Mode 1
//Orientation 1
#include "Kinematics.h"
#include "GlobalArm.h"
extern void IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable, int enablePrinter);
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int playState = 0; // 0 = stopped 1 = playing
volatile int j = 0;  //To enable segmented sketching.

void playSequence()
{
  delay(500);
  Serial.println("Sequencing Mode Active."); 
  Serial.println("Press Pushbutton  to stop");
  playState = 1;  //set playState to 1 as the sequence is now playing
    g_bIKMode = IKM_IK3D_CARTESIAN;
    //###########################################################//
    // SEQUENCE 1 X:(-150,150) Y:(50,200) Z:(20,225) //100 Interpolate is optimum speed.
    //###########################################################// 
////Initialization Block
float y = 150; //Y position after initialization routine.

//Variables for routing algorithm
float y1 = 150;
float y2 = 130;
float x1 = 10;
float x2 = -10;
float z = 113; //Height in mm.
int longDelay = 4000;

//Variables for loops.
float i = 0;
float j = z;
int cooldown = 0;


//Initialization Routine
  for(i = 150; i<200; i+=10){ //Raising first guaranteeing no obstruction. 
      IKSequencingControl(0, y, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);  
   }
   for(i = 200; i>z; i-=10){ //Settling down to initial printing location. 
      IKSequencingControl(x2, y1, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);  
   }
   delay(3000);

//IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable, int enablePrinter);


//
//Printing four walls, 2 millimeters thick and 20 millimeteres high.
//Use low interpolation to increase precision.
//Use lower pauses to decrease choppiness.
//

while(z<200){

//1111111111111111111111111111111
  IKSequencingControl(x2, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
  delay(1750);
  for(i = x2; i < x1; i+=1.5){
    IKSequencingControl(i, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
    }
  delay(750);  
  IKSequencingControl(i, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);
  delay(longDelay);
  IKSequencingControl(i, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
  delay(1750);  

//222222222222222222222222222222  
  for(i = y1; i > y2; i-=1){
    IKSequencingControl(x1, i, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
    }
    delay(750);
      for(i = z; i>(z-6); i-=1.5){
        IKSequencingControl(x1, y2, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);
      }
      delay(longDelay);
      IKSequencingControl(x1, y2, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
      delay(2000);


//333333333333333333333333333333
  for(i = x1; i > x2; i-=1.2){
    IKSequencingControl(i, y2, (z-3), 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
    }
    delay(750);
    for(i = (z-3); i< (z-1); i+=1){
        IKSequencingControl(x2, (y2+2), i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);
      }
  delay(longDelay);
  IKSequencingControl(x2, y2, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
  delay(2000);


//44444444444444444444444444444
  for(i = y2; i < y1; i+=1.2){
    IKSequencingControl(x2, i, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
    }
    delay(750);
    IKSequencingControl(x2, i, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);
    delay(longDelay);
    //IKSequencingControl(x2, i, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
    //delay(750);

        //for(i = z; i < (z+15); i+=1){ //Raise height by z millimeters.
          //IKSequencingControl(x2, y1, i, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
         //}
         //delay(1000);
         //IKSequencingControl(x2, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 1);
         //delay(500);
         //IKSequencingControl(x2, y1, z, 0.000000, 0.000000, 0.000000, 100.000000, 0.000000, 1.000000, 0);
        //if(z<117) z = z+0.5;
          //else z = z+1;
          z = z+0.5;
         //delay(5000);
}

  
   delay(100);
   Serial.println("Pausing Sequencing Mode."); 
   delay(1000);
   //uncomment this to  put the arm in sleep position after a sequence
   //PutArmToSleep();
}
