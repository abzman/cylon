
/* LucidTronix Shift Register
 * LED chaser w/ 74HC595 
 * Tutorial at:
 * http://www.lucidtronix.com/tutorials/2
 */

int latchPin = 4; //Pin connected to ST_CP of 74HC595
int clockPin = 3; //Pin connected to SH_CP of 74HC595
int dataPin = 2; //Pin connected to DS of 74HC595
int data[40];
int d = 20;
boolean cylon = 1;
void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int k = 2; k < 33; k++) {
    if(cylon)
    {
    for (int j = 0; j < 40; j++) {
      data[j] = 0;
    }
    data[k] = 1;
    }
        digitalWrite(latchPin, LOW); 
        int h=0;
        int pinState;
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
        digitalWrite(dataPin, 0);
        digitalWrite(clockPin, 0); 
        for (h=40; h>=0; h--)  {
          digitalWrite(clockPin, 0);
          if ( data[h] ) {
            pinState= 0;
          }
          else {	
            pinState= 1;
          }
          digitalWrite(dataPin, pinState); //write the bit
          digitalWrite(clockPin, 1); //shift bits rising clock pin 
          digitalWrite(dataPin, 0);//0 data to prevent bleed through
        }
        //stop shifting
        digitalWrite(clockPin, 0);
        digitalWrite(latchPin, HIGH);
    delay(d);
  }
  
  for (int k = 31; k > 2; k--) {
    for (int j = 0; j < 40; j++) {
      data[j] = 0;
    }
    data[k] = 1;
        digitalWrite(latchPin, LOW); 
        int h=0;
        int pinState;
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
        digitalWrite(dataPin, 0);
        digitalWrite(clockPin, 0); 
        for (h=40; h>=0; h--)  {
          digitalWrite(clockPin, 0);
          if ( data[h] ) {
            pinState= 0;
          }
          else {	
            pinState= 1;
          }
          digitalWrite(dataPin, pinState); //write the bit
          digitalWrite(clockPin, 1); //shift bits rising clock pin 
          digitalWrite(dataPin, 0);//0 data to prevent bleed through
        }
        //stop shifting
        digitalWrite(clockPin, 0);
        digitalWrite(latchPin, HIGH);
    delay(d);
  }
}



