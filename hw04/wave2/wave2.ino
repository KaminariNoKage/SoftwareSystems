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

//Sawtooth wave since same type as original
static int waveformsTable = {
    0x22, 0x44, 0x66, 0x88, 0xaa, 0xcc, 0xee, 0x110, 0x132, 0x154,
    0x176, 0x198, 0x1ba, 0x1dc, 0x1fe, 0x220, 0x242, 0x264, 0x286, 0x2a8,
    0x2ca, 0x2ec, 0x30e, 0x330, 0x352, 0x374, 0x396, 0x3b8, 0x3da, 0x3fc,
    0x41e, 0x440, 0x462, 0x484, 0x4a6, 0x4c8, 0x4ea, 0x50c, 0x52e, 0x550,
    0x572, 0x594, 0x5b6, 0x5d8, 0x5fa, 0x61c, 0x63e, 0x660, 0x682, 0x6a4,
    0x6c6, 0x6e8, 0x70a, 0x72c, 0x74e, 0x770, 0x792, 0x7b4, 0x7d6, 0x7f8,
    0x81a, 0x83c, 0x85e, 0x880, 0x8a2, 0x8c4, 0x8e6, 0x908, 0x92a, 0x94c,
    0x96e, 0x990, 0x9b2, 0x9d4, 0x9f6, 0xa18, 0xa3a, 0xa5c, 0xa7e, 0xaa0,
    0xac2, 0xae4, 0xb06, 0xb28, 0xb4a, 0xb6c, 0xb8e, 0xbb0, 0xbd2, 0xbf4,
    0xc16, 0xc38, 0xc5a, 0xc7c, 0xc9e, 0xcc0, 0xce2, 0xd04, 0xd26, 0xd48,
    0xd6a, 0xd8c, 0xdae, 0xdd0, 0xdf2, 0xe14, 0xe36, 0xe58, 0xe7a, 0xe9c,
    0xebe, 0xee0, 0xf02, 0xf24, 0xf46, 0xf68, 0xf8a, 0xfac, 0xfce, 0xff0
  }


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
int maxSamplesNum = 120;

void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
  
  counter += stride;
  if (counter > high) {
    counter = low;
    //Serial.println(counter);
  }

  //Setting wave
  analogWrite(DAC0, waveformsTable[i]);
  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;

  delay(1000);  //Might not need, but putting in here from tutorial code comparrison
  // write to the digital pins  
  writeByte(counter);
}
