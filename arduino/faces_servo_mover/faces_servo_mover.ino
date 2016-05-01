/*================================================
  ============= Faces Servo Mover ================
  ================================================
  Receive and react to a serial string.
  (for 180 faces)
  - MERGED FROM node_tut.ino. 2016.APR.20
  - adding LED tester for Pi

  Note:
  - nano resets when disconnected, micro keeps the connection alive.
  - copied from BT_Serial_Commander_v003
  - Serial.parseInt() only parses integer values, ignores keys.
  
*/

/*libraries*/
#include <Servo.h>

/*vars*/
// ==== LED ====
int ledPin = 13;
bool ledState = LOW;
int blinkRate = 100;

// ==== Servo ====
Servo myservo;
int delayInterval = 100; //servo smoothing via delay
int interval = 10; //servo smoothing via non delay
int servoPos = 0; //keep track of the servo position for smoothing
const int servoPin = 10;

// ==== L298N Motor Controller ====
//PWM pins: 3,5,6,9,10,11

// Motor 1
int dir1PinA = 3; //IN1
int dir2PinA = 4; //IN2
int speedPinA = 5;  //EN1

//motor 2
int dir1PinB = 7; //IN3
int dir2PinB = 8; //IN4
int speedPinB = 9;  //EN2


// ==== TIMERS ====
unsigned long previousMillis = 0;
unsigned long prevMil = 0;


void setup() {
  pinMode(ledPin, OUTPUT);  //set LED to output
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(speedPinB, OUTPUT);
  
  Serial.begin(9600);       //pour a bowl of serial
  Serial.setTimeout(10);   

  digitalWrite(ledPin, LOW);  //set lights off
  
  myservo.attach(servoPin); //attach servo to pin
  myservo.write(90);         //zero servo on startup

  Serial.print("initialized! \r\n");
}

void loop() {

  evaluateSerial();
  //blinky();

}



/*============= FUNCTIONS ============*/
/**
 * Evaluate Serial Input (keys)
 * TODO: do else-if instead.
 */
void evaluateSerial() {
  
  if (Serial.available() > 0) {

//    digitalWrite(ledPin, HIGH); //turn on the led when writing
    
    char input = Serial.read();

    if (input == 'q'){
      //myservo.write(0);
      smoothServo(servoPos, 0);

      Serial.write("servoPos 0 \r\n"); //sends a string, which is essential an array of bytes with null char.
    }
    else if (input == 'w') {
      //myservo.write(45);
      smoothServo(servoPos, 45);
      //Serial.write(48); //  ASCII 48 = 0

      Serial.write(115);  //ASCII 115 = SYMBOL 's'
      Serial.write(101);  //ASCII 101 = SYMBOL 'e'
      Serial.write(114);  //ASCII 115 = SYMBOL 'r'
      Serial.write(118);  //ASCII 115 = SYMBOL 'v'
      Serial.write(111);  //ASCII 115 = SYMBOL 'o'
      Serial.write(80);   //ASCII 115 = SYMBOL 'P'
      Serial.write(111);  //ASCII 115 = SYMBOL '0'
      Serial.write(115);  //ASCII 115 = SYMBOL 's'
      Serial.write(32);   //ASCII 32 = 'space'
      Serial.write(52);   //ASCII 52 = SYMBOL '4'
      Serial.write(53);   //ASCII 53 = SYMBOL '5'
      
      Serial.write(10); //  ASCII 10 = SYMBOL LF
      Serial.write(13); //  ASCII 13 = SYMBOL CR

      
    }
    else if (input == 'e') {
      //myservo.write(90);
      smoothServo(servoPos, 90);

      Serial.print("servoPos 90 \r\n");

    }
    else if (input == 'r') {
      //myservo.write(135);
      smoothServo(servoPos, 135);

      char myString[] = {'s','e','r','v','o','P','o','s', 32 , '1','3','5', '\r', '\n', '\0'};  //explicit null end char

      Serial.write(myString);

            

    }
    else if (input == 't') {
      //myservo.write(180);
      smoothServo(servoPos, 180);
      Serial.write("abcd");

    }
    else if (input == 'a') {
      digitalWrite(ledPin, HIGH);
      ledState = HIGH;
    }
    else if (input == 's') {
      digitalWrite(ledPin, LOW);
      ledState == LOW;
    }

    else if (input == 'd') {

      ledState = !ledState;

      digitalWrite(ledPin, ledState);
      Serial.print(ledState); //prints to 0 or 1, depending on or off

    }

    else if (input == 'x') {
      Serial.write("smoothing over to 180 \r\n");
      noDelaySmoothServo(0, 180);
    }

    else {
      Serial.write("invalid key!");
    }
  }

//  else {
//    digitalWrite(ledPin, LOW);  //turn off the led after writing
//  }
}

/**
 * Smooth Servo movements from-to using delay
 */
void smoothServo(int from, int to) {

  if(from <= to) {
    for(int i = from; i < to; i+=1) {
      myservo.write(i);
      servoPos = i;
      //delay(interval);
    }
  }
  else if(from > to) {
    for(int i = from; i > to; i-=1) {
      myservo.write(i);
      servoPos = i;
      //delay(interval);
      //no delay required, handled through non-blocking delay
    }
  }
}

void noDelaySmoothServo(int from, int to) {

  unsigned long curMil = millis();

/*  
 *   //MIGHT NOT BE NEEDED
    myservo.write(0); //debug, reset servo position
    servoPos = 0;
    */
  
  if(curMil - prevMil >= delayInterval) {

    for(int i = 0; i < 180; i++) {
      myservo.write(i);
    }
    
    curMil = prevMil;  //update checker
  }

  for (int i = from; i < to; i++){
    myservo.write(i);

  }

}

/**
 * CONSTANT BLINKER
 */
void blinky() {
  unsigned long curMil = millis();
  
  if(curMil - prevMil >= blinkRate) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    
    prevMil = curMil;  //update checker
  }
    
}

/*Blink without delay pseudo code:
 * 
 * interval = 100; (100 millisecond delay)
 * prevMil = 0; (set to 0)
 * curMil = millis() (milliseconds since program start)
 * 
 * if curMil minus prevMil is greater than or equal to interval, then run code:
 *    flip ledState
 *    write ledState
*  
*  update prevMil to curMil, which sets a checkpoint to check against. For instance:
*  
*  prevMil = 0; curMil = 250
*  prevMil = 250; curMil 750
*  prevMil = 750; curMil = 1250
*  prevMil = 1250; curMil = 2000

*/

