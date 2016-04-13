/*==============================
  BLUETOOTH SERIAL COMMANDER v01
  ==============================
  by Jeff Wu, <http://www.jwxstudios.com>
  
  Derrived from Bluetooth_Test_v002.
 
*/

// LIBS
#include <Servo.h>  // servo library

// VARS
int ledPin = 11; //PWM available pin, NANO: 3,5,6,9,10,11
int fadeSpeed = 5;
int fadeDelay = 5;
int maxBrightness = 255;
int minBrightness = 0;
// === bluetooth specific
char val;  //char variable to hold data from serial port

// == Servo position
int servoPos = 0;  //keeps track of current servo position

// == command keys definitions 
const char key1 = 'q';
const char key2 = 'w';
const char key3 = 'e';
const char key4 = 'r';

//==== SERVO specific ====
Servo myservo;
const int servoPin = 10;  
const char servoKey1 = 'a';
const char servoKey2 = 's';
const char servoKey3 = 'd';
const char servoKey4 = 'f';

const char servoKey5 = 'g';  //test servos for loop

const char servoKey6 = 'z';  // wherever it is, smooth to close
const char servoKey7 = 'x';  // wherever it is, smooth to open


void setup()
{
  pinMode(ledPin, OUTPUT);  //sets LED pin to be output
  Serial.begin(9600);  //pour a bowl of serial
  
  //myservo, attach to pin ##
  myservo.attach(10);
  
  //run servo startup test script
  //servoTest();
  
  
  //set servo to zero on startup
  myservo.write(0);
}

void loop()
{
  serialEvaluation();  //execute serial listening
  delay(100);  //slow things down, baby.
}

// custom functions
void serialEvaluation()
{
  if( Serial.available() )  //if there's something coming in through serial...
  {
    val = Serial.read();  //store it in val
    if(val == key3)  //if data = the character H
    {
      digitalWrite(ledPin, HIGH);
      Serial.write("On!\r\n");
    }
    else if(val == key1)
    {
      fadeIn(); 
      Serial.write("Fade On!\r\n");
    }  
    else if(val == key2)
    {
      fadeOut(); 
      Serial.write("Fade Out!\r\n");
    }  
    else if(val == key4)
    {
      digitalWrite(ledPin, LOW);
      Serial.write("Off!\r\n");
    }
    else if(val == servoKey1)
    {
      myservo.write(0);
      Serial.write("servo at zero!\r\n");
      servoPos = 0;
    }
    else if(val == servoKey2)
    {
      myservo.write(90);
      Serial.write("servo at center!\r\n");
      servoPos = 90;
    }
    else if(val == servoKey3)
    {
      myservo.write(180);
      Serial.write("servo at max!\r\n");
      servoPos = 180;
    }
    else if(val == servoKey4)
    {
      myservo.write(20);
      Serial.write("servo at arbitrary position\r\n");
      servoPos = 20;
    }
    else if(val == servoKey5)
    {
      Serial.write("servo test running!\r\n");
      servoTest();
      Serial.write("servo test complete! \r\n");
    }
    else if(val == servoKey6)  //smooth to close position
    {
      servoSmoothMove(servoPos, 0, 10);
    }
    else if(val == servoKey7)  //smooth to open position
    {
      servoSmoothMove(servoPos, 180, 10);
    }
    else
    // wrong key? throw error
    {
      Serial.write("Invalid input!\r\n");
    }
  }
}

// CUSTOM SERVO METHODS
void trackServoPosition(int pos)
{
  servoPos = pos;
  Serial.print(servoPos,DEC);
  Serial.println();
}

void servoTest()
// tests the servo's functionality
{
  for (int i = 0; i < 180 ;i += 1 )
  {
    myservo.write(i);
    delay(10);
    trackServoPosition(i);
  }
  
  for (int i = 180; i > 0; i -= 1 )
  {
    myservo.write(i);
    delay(10);
    trackServoPosition(i);
  }
  
}

void servoSmoothMove(int from, int to, int speed)
{
  //if 'from' is less than 'to', increment
  if(from <= to)
  {
    for(int i = from; i < to; i += 1)
    {
      myservo.write(i);
      servoPos = i;  // update servo position
      delay(speed);

    }

  }
  //if opposite, increment
  else if(from > to)
  {
    for(int i = from; i > to; i-= 1)
    {
      myservo.write(i);
      servoPos = i;  // update servo position
      delay(speed);
    }
    
  }
  
}
// CUSTOM LED CONTROLLERS

void fadeIn()
// fuction to fade in LED on ledPin.
{
  for(int fadeValue = minBrightness; fadeValue <= maxBrightness; fadeValue += fadeSpeed)
  {
    analogWrite(ledPin, fadeValue);
    delay(fadeDelay);
  }
}

void fadeOut()
// function to fade out LED on ledPin
{
  for(int fadeValue = maxBrightness; fadeValue >= minBrightness; fadeValue -= fadeSpeed)
  {
    analogWrite(ledPin, fadeValue);
    delay(fadeDelay);
  }
}

