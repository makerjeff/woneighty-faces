/*libraries*/
#include <Servo.h>

//const int ledPin = 3;  //for nano
int ledVal = 0;

//---- servo ----
Servo myservo;
int servoPos = 0;
const int servoPin = 3;


void setup() {
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  
  Serial.begin(9600);
  Serial.setTimeout(10);

  myservo.write(90);
}

void loop() {

  while (Serial.available() > 0) {

    int val1 = Serial.parseInt();   //grabs first value

    if (Serial.read() == '\n') {
      Serial.print(val1);
      Serial.print(". ");
      Serial.print("\r\n");

      if (val1 > 180) {
        Serial.print("a value was too high \r\n");
      } else {
        //analogWrite(ledPin, val1);
        myservo.write(val1);

      }
    }
  }
}
