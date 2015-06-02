int latchPin = 4; //Pin connected to ST_CP of 74HC595
int clockPin = 3; //Pin connected to SH_CP of 74HC595
int dataPin = 2; //Pin connected to DS of 74HC595
int data[40];
int d = 20;
boolean cylon = 1;
int cylonsize = 35;
boolean scandirection = 0;
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop() {
scan();
}

void scan()
{
  for (int k = (17-((cylonsize-1)/2)); k < (18+((cylonsize-1)/2)); k++) {
    for (int j = 0; j < 40; j++) {
      data[j] = 0;
    }
    data[k] = 1;
    writeOut();
  }
  for (int k = (18+((cylonsize-1)/2))-2; k > (17-((cylonsize-1)/2)); k--) {
    for (int j = 0; j < 40; j++) {
      data[j] = 0;
    }
    data[k] = 1;
    writeOut();
  }
}


void writeOut()
{
  digitalWrite(latchPin, 0); 
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0); 
  for (int h=40; h>=0; h--)  {
    digitalWrite(clockPin, 0);
    digitalWrite(dataPin, !data[h]); //write the bit
    digitalWrite(clockPin, 1); //shift bits rising clock pin 
    digitalWrite(dataPin, 0);//0 data to prevent bleed through
  }
  //stop shifting
  digitalWrite(clockPin, 0);
  digitalWrite(latchPin, HIGH);
  delay(d);
}



