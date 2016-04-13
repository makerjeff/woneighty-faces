/*===========================
  = Simple Serial Generator =
  ===========================
  Generate a single simple serial value.

*/

const int ledPin = 13;  //debug LED pin
const long interval = 1000;  //how often to update (in milliseconds)
unsigned long previousMillis = 0;  //initialize previous millis
int inByte = 0;

//iterator vars
unsigned long iteration = 0;  //keeps track of # of pulses


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  //pour a bowl of serial

  //leonardo + micro prereq
  while(!Serial) {;}
  
  Serial.println("initialized!");  //print a recognizable string
  Serial.flush();  //clear out the outgoing buffer

}

void loop() {
  
  //INPUT:
  //read serial if there's something in the input buffer
  if(Serial.available() > 0) {

    int ex = Serial.parseInt();  //parse first value
    int why = Serial.parseInt();  //parse second value
    int zee = Serial.parseInt();  //parse third value
    
    //once newline character detected, print out to console
    //(omit this for actual deployment)
    if(Serial.read() == '\n') {
      Serial.print(ex, DEC);  //print first value
      Serial.print("x");
      Serial.print(why, DEC);  //print second value
      Serial.print("x");
      Serial.print(zee, DEC);  //print third value
      Serial.print("\r\n");
    }
  }
  
  //OUTPUT:
  
  //============================
  // non blocking delay pattern
  //============================
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    //-- PUT YOUR FUNCTION HERE --
    RandomSerial();
    //-- PUT YOUR FUNCTION HERE <end> --
    previousMillis = currentMillis;  //checkpoint
  }
  //============================
}

void RandomSerial() {
  int rand0 = random(0, 255);
  int rand1 = random(0, 255);
  int rand2 = random(0, 255);
  
  Serial.print(iteration);  //print the iteration number
  Serial.print(", ");
  Serial.print(rand0);
  Serial.print(", ");
  Serial.print(rand1);
  Serial.print(", ");
  Serial.print(rand2);
  Serial.print("\r\n");
  
  iteration ++;  //
}

