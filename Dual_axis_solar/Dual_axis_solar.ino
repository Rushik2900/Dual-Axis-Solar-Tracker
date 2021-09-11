#include <Servo.h> 

// horizontal servo--------------------------------------
Servo horizontal;   
int servoh = 120;   // 120;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

// vertical servo-----------------------------------------
Servo vertical;      
int servov = 45;    //   45;     // stand vertical servo

int servovLimitHigh = 80;
int servovLimitLow = 15;


// LDR pin connections-------------------------------------
// all are analogpins;
int ldrlt = 0;    //LDR top left  
int ldrrt = 1;    //LDR top rigt 
int ldrld = 2;    //LDR down left
int ldrrd = 3;    //ldr down rigt

void setup()
{
  Serial.begin(9600);
  // servo connections
  horizontal.attach(9); 
  vertical.attach(10);
  // initial position of servo
  horizontal.write(servoh);
  vertical.write(servov);
  delay(3000);
}

void loop() 
{
 


  int lt = analogRead(ldrlt);   // top left
  int rt = analogRead(ldrrt);   // top right
  int ld = analogRead(ldrld);   // down left
  int rd = analogRead(ldrrd);   // down rigt
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2;      // average top value 
  int avd = (ld + rd) / 2;      // average down value 
  int avl = (lt + ld) / 2;      // average left value 
  int avr = (rt + rd) / 2;      // average right value 

  int dvert = avt - avd;        // Diffirence of up and down
  int dhoriz = avl - avr;       // Diffirence of left and rigt
  
  
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.print(" ");
  
    
  if (-1*tol > dvert || dvert > tol)    // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
    if (servov > servovLimitHigh) 
    { 
     servov = servovLimitHigh;
    }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol)      // check if the diffirence is in the tolerance else change horizontal angle
  {
    if (avl > avr)
    {
      servoh = --servoh;
      if (servoh < servohLimitLow)
      {
        servoh = servohLimitLow;
      }
    }
    else if (avl < avr)
    {
      servoh = ++servoh;
      if (servoh > servohLimitHigh)
      {
        servoh = servohLimitHigh;
      }
    }
    else if (avl = avr)
    {
      // nothing
    }
    horizontal.write(servoh);
  }
  delay(dtime);
} 
