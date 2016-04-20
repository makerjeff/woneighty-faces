/*================================================
  ============= Faces Servo Mover ================
  ================================================
  Receive and react to a serial string.
  (for 180 faces)
  - MERGED FROM node_tut.ino. 2016.APR.20

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

// ==== Servo ====
Servo myservo;
int servoPos = 0; //keep track of the servo position for smoothing
const int servoPin = 10;

void setup() {
  pinMode(ledPin, OUTPUT);  //set LED to output
  Serial.begin(9600);       //pour a bowl of serial
  Serial.setTimeout(10);   
  
  myservo.attach(servoPin); //attach servo to pin
  myservo.write(90);         //zero servo on startup

  Serial.print("initialized! \r\n");
}

void loop() {
  evaluateSerial();
  delay(100);
}


/*============= FUNCTIONS ============*/
/**
 * Evaluate Serial Input (keys)
 * TODO: do else-if instead.
 */
void evaluateSerial() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == 'q'){
      myservo.write(0);
    }
    if (input == 'w') {
      myservo.write(45);
    }
    if (input == 'e') {
      myservo.write(90);
    }
    if (input == 'r') {
      myservo.write(135);
    }
    if (input == 't') {
      myservo.write(180);
    }
  }
}

