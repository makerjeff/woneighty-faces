 /*================================================
  ============= Faces Servo Mover ================
  ================================================
  Receive and react to a serial string.
  (for 180 faces)
  - MODIFIED FOR NODE_TUT, TODO: update faces_servo_mover when done

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
// ==== Serial ====
char val; //holds data from serial port
int intVal; //holds integer from serial port

// ==== Servo ====
Servo myservo;
int servoPos = 0; //keep track of the servo position for smoothing
const int servoPin = 10;
const char servoKey1 = 'a'; //zero position
const char servoKey2 = 's'; //center position
const char servoKey3 = 'd'; //max position
const char servoKey4 = 'f'; //arbitrary position

const char servoKey5 = 'g'; //test servos for-loop
const char servoKey6 = 'z'; //smooth to close from any position
const char servoKey7 = 'x'; //smooth to open from any position



void setup() {
  pinMode(ledPin, OUTPUT);  //set LED to output
  Serial.begin(9600);       //pour a bowl of serial
  Serial.setTimeout(10);  
  
  myservo.attach(servoPin); //attach servo to pin
  myservo.write(90);         //zero servo on startup

  Serial.print("initialized! Input a value. \r\n");
}

void loop() {
  //nodeTut2();
  nodeTut();
  //serialInput();
  //serialEvaluation();
  delay(100);
}



/*============= FUNCTIONS ============*/

void noteTut3(){
  
}

void nodeTut2(){
  if(Serial.available() > 0){
    char input = Serial.parseInt();
    myservo.write(input);
  }
}

void nodeTut() {
  if(Serial.available() > 0){
    char input = Serial.read();

    if(input == 'q'){
      myservo.write(0);
    }
    if(input == 'w'){
      myservo.write(45);
    }
    if(input == 'e'){
      myservo.write(90);
    }
    if(input == 'r'){
      myservo.write(135);
    }
    if(input == 't'){
      myservo.write(180);
    }
  }
  
}

void serialInput() {
  while(Serial.available() > 0) {
    
    int value = Serial.parseInt();

    //end of line...
    if(Serial.read() == '\n'){

      

      //move servo
      if(value < 0) {
        Serial.print("value too low! \r\n");
      }
      else if(value > 180){
        Serial.print("value too high! \r\n");
      }
      else {
        //write back to console
        Serial.print("input value: ");
        Serial.print(value);
        Serial.print("\r\n");
        
        myservo.write(value);

      }
    }
  }
}

/**
 * Evaluate Serial Input (keys)
 */
void serialEvaluation() {
  
  if(Serial.available()){ //if there's something coming through the serial port
    val = Serial.read();  //buffer it

    if(val == servoKey1){
      myservo.write(0);
      Serial.write("servo at zero!\r\n");
    }
    else if (val == servoKey2){
      myservo.write(90);
      Serial.write("servo at center!\r\n");
    }
    else if (val == servoKey3){
      myservo.write(180);
      Serial.write("servo at max!\r\n");
    }
    else if (val == servoKey4){
      myservo.write(20);
      Serial.write("servo at arbitrary position. \r\n");  
    }
    else {
      Serial.write("Invalid input!\r\n");
    }
  }
}

