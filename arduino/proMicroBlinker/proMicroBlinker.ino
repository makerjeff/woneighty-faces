/* PRO MICRO BLINKER */
/* Serial Call Response */
int RXLED = 17; //RX is defined, but not TX. Use TXLED0, TXLED1 macros.
unsigned long prevMil = 0;
int interval = 250;
int interval2 = 100;
bool led1State = false;
bool led2State = false;

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
    
    int firstVal = Serial.parseInt();
    int secondVal = Serial.parseInt();
    int thirdVal = Serial.parseInt();

    if(Serial.read() == '\n') {
      Serial.print(firstVal);
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
