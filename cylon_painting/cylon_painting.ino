#include <SerialCommand.h>
SerialCommand SCmd;

int latchPin = 4; //Pin connected to ST_CP of 74HC595
int clockPin = 3; //Pin connected to SH_CP of 74HC595
int dataPin = 2; //Pin connected to DS of 74HC595
int data[40];
int datum = 0;
int d = 20;
boolean cylon = 1;
int cylonsize = 33;
boolean scandirection = 1;

int temp;
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  datum = (17-((cylonsize-1)/2));
  Serial.begin(115200); 
  SCmd.addCommand("ON",on);
  SCmd.addCommand("OFF",off);
  SCmd.addCommand("POS",position);
  SCmd.addCommand("SIZE",size);
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 
  Serial.println("Ready"); 
}
void loop() {
  SCmd.readSerial();
  if(cylon)
  {
    scan();
  }
}

void on()
{
  cylon = 1;
}
void off()
{
  cylon = 0;
}
void position()
{
  char *arg;
  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    temp = atoi(arg);
    if(temp<35)
    {
      data[datum] = 0;
      datum=temp;
      data[datum] = 1;
      writeOut();
    }
    else
    {
      Serial.println("too big, please enter a number less than 35");
    }
  }
}
void size()
{
  char *arg;
  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    temp = atoi(arg);
    if(temp<36)
    {
      cylonsize=temp;

      data[datum]=0;
      datum = (17-((cylonsize-1)/2));
      data[datum]=1;
    }
    else
    {
      Serial.println("too big, please enter a number less than 36");
    }
  }
}

void scan()
{
  data[datum] = 0;
  if(scandirection)
  {
    if(datum == (18+((cylonsize-1)/2)))
    {
      //datum -=1;
      scandirection = 0;
    }
    else
    {
      datum +=1;
    }
  }
  else
  {
    if(datum == (17-((cylonsize-1)/2)))
    {
      //datum +=1;
      scandirection = 1;
    }
    else
    {
      datum -=1;
    }
  }
  data[datum] = 1;

  writeOut();
}


void writeOut()
{
  digitalWrite(latchPin, 0); 
  digitalWrite(dataPin, 0);
  for (int h=40; h>=0; h--)  {
    digitalWrite(clockPin, 0);
    digitalWrite(dataPin, !data[h]); //write the bit
    digitalWrite(clockPin, 1); //shift bits rising clock pin 
    digitalWrite(dataPin, 0);//0 data to prevent bleed through
  }
  //stop shifting
  digitalWrite(clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(d);
}



void unrecognized()
{
  Serial.println("What?"); 
}



