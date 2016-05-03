/* PRO MICRO BLINKER */
/* Serial Call Response */
int RXLED = 17; //RX is defined, but not TX. Use TXLED0, TXLED1 macros.
unsigned long prevMil = 0;
int interval = 250;
int interval2 = 100;
bool led1State = false;
bool led2State = false;

int inByte = 0;

void setup() {
    // put your setup code here, to run once:
    pinMode(RXLED, OUTPUT);

  // set baseline LED status
  digitalWrite(RXLED, led1State);
  TXLED0;

  // setup serial
  Serial.begin(9600);

  while(!Serial) {
    ; // wait for serial port connection, leonardo + micro 
  }

  //establishContact(); //this gets repeated until something comes into the serial buffer.

}

void loop() {
  // put your main code here, to run repeatedly:

  blinky();

  while (Serial.available() > 0) {

    //inByte = Serial.read(); //this is grabbing the first char

    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();

//      Serial.print(inByte); //prints the ASCII
//      Serial.print("\r\n");

//      USE THIS:
//      Serial.write(inByte); // individually prints out each value, not ASCII.
//      Serial.write("\r\n");

    if(val1 > 255 || val2 > 255 || val3 > 255) {
      Serial.print("values too high! try again \r\n");
    } 

    //';' = 59
    else if(Serial.read() == ';') {
      Serial.print(val1);
      Serial.print(", ");
      Serial.print(val2);
      Serial.print(", ");
      Serial.print(val3);
      Serial.print(". ");
      Serial.print("\r\n");
    }
  }
    
}

// ===== FUNCTIONS =====
void blinky(){
  unsigned long curMil = millis();

  if(curMil - prevMil >= interval) {
    
    led1State = !led1State;
    digitalWrite(RXLED, led1State);

    if(led1State == true) {
      TXLED0;  
    } else {
      TXLED1;
    }
    prevMil = curMil;
  } 
}

void establishContact() {
  while(Serial.available() <= 0) {
    Serial.println("awaiting first message");
    delay(300);
  }
}
