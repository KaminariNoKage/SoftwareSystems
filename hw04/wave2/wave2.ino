/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  
  pinMode(13, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(10, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(8, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(6, OUTPUT);  
}

int reverseBits(int num)
{
    int count = sizeof(num) * 8 - 1;
    int reverse_num = num;
    
    num >>= 1; 
    while(num)
    {
       reverse_num <<= 1;       
       reverse_num |= num & 1;
       num >>= 1;
       count--;
    }
    reverse_num <<= count;
    return reverse_num;
}

void writeByte(int x) {
  int pin;
  
  //for (pin=13; pin>=6; pin--) {
   // digitalWrite(pin, x&1);
   // x >>= 1;
  //}
  
  // set pins 1 (serial transmit) and 2..7 as output,
  // but leave pin 0 (serial receive) as input
  // (otherwise serial port will stop working!) ...
  DDRD = reverseBits(B11111110);  // digital pins 7,6,5,4,3,2,1,0

  // set pins 8..13 as output...
  DDRB = reverseBits(B00111111);  // digital pins -,-,13,12,11,10,9,8

  // Turn off digital output pins 2..7 ...
  PORTD &= B00000011;   // turns off 2..7, but leaves pins 0 and 1 alone

  // Write simultaneously to pins 8..13...
  PORTB = B00111000;   // turns on 13,12,11; turns off 10,9,8
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;

void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  counter += stride;
  if (counter > high) {
    counter = low;
    //Serial.println(counter);
  }

  // write to the digital pins  
  writeByte(counter);
}
