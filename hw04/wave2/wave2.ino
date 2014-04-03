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

void change(){}

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  

  pinMode(ledPin, OUTPUT);
  
  //pinMode(13, OUTPUT);  
  //pinMode(12, OUTPUT);  
  //pinMode(11, OUTPUT);  
  //pinMode(10, OUTPUT);  
  //pinMode(9, OUTPUT);  
  //pinMode(8, OUTPUT);  
  //pinMode(7, OUTPUT);  
  //pinMode(6, OUTPUT);
  
  //Set pins 7-6 as output, leave 5-0 alone
  DDRD = B11000000;  // digital pins 7,6,5,4,3,2,1,0
  // set pins 8..13 as output...
  DDRB = B00111111;
  
  //Setting up timer for 1ms
  
  cli();//stop interrupts
  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set timer count for 1khz increments
  OCR1A = 1999;// = (16*10^6) / (1000*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
  
  attachInterrupt(buttonPin1, change, RISING);
  
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
  int y = reverseBits(x);
  int z = reverseBits(x);
  
  y <<= 6;  // 11111111 << 1100000
  z >>= 2;  //11111111 >> 00111111

  //for (pin=13; pin>=6; pin--) {
   // digitalWrite(pin, x&1);
   // x >>= 1;
  //}
  
  //Turn on pins 7-6
  PORTD &= y;
  
  //Turn on pins 13-8
  PORTB = z;
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;
int i = 0;

ISR(TIMER1_COMPA_vect) {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  counter += stride;
  if (counter > high) {
    counter = low;
  }

  // write to the digital pins  
  writeByte(counter);
}

void loop() {
  
}
