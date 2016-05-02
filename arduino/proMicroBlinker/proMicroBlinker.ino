// globals
int RXLED = 17; //RX is defined, but not TX. Use TXLED0, TXLED1 macros.

int prevMil = 0;
int interval = 150;
int interval2 = 100;

bool led1State = false;
bool led2State = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(RXLED, OUTPUT);

  // set baseline LED status
  digitalWrite(RXLED, led1State);
  TXLED0;

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long curMil = millis();

  if(curMil - prevMil >= interval) {
    led1State = !led1State;
    digitalWrite(RXLED, led1State);
    prevMil = curMil;
  } 


}
