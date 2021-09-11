#include <Servo.h> 
Servo horizontal;   
int servoh = 120;       
int servohLimitHigh = 180;
int servohLimitLow = 65;
Servo vertical;      
int servov = 45;   
int servovLimitHigh = 80;
int servovLimitLow = 15;
int ldrlt = 0;    //LDR top left  
int ldrrt = 1;    //LDR top rigt 
int ldrld = 2;    //LDR down left
int ldrrd = 3;    //ldr down rigt

void setup()
{
  Serial.begin(9600);
  horizontal.attach(9); 
  vertical.attach(10);
  horizontal.write(servoh);
  vertical.write(servov);
  delay(3000);
}

void loop() 
{
 


  int lt = analogRead(ldrlt);   
  int rt = analogRead(ldrrt);   
  int ld = analogRead(ldrld);   
  int rd = analogRead(ldrrd);   
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2;      
  int avd = (ld + rd) / 2;       
  int avl = (lt + ld) / 2;      
  int avr = (rt + rd) / 2;      

  int dvert = avt - avd;       
  int dhoriz = avl - avr;      
 
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
  
    
  if (-1*tol > dvert || dvert > tol)    
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
  
  if (-1*tol > dhoriz || dhoriz > tol)     
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
