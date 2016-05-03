const int ledPin = 3;  //for nano

void setup() {
  Serial.begin(9600);
}

void loop() {

    
    while(Serial.available() > 0) {

        int val1 = Serial.parseInt();   //grabs first value
        //int val2 = Serial.parseInt();   //grabs second value
        //int val3 = Serial.parseInt();   //grabs third value

        if(Serial.read() == 59) {
            Serial.print(val1);
//            Serial.print(", ");
//            Serial.print(val2);
//            Serial.print(", ");
//            Serial.print(val3);
            Serial.print(". ");
            Serial.print("\r\n");

//            if(val1 > 255 || val2 > 255 || val3 > 255) {
//                Serial.print("a value was too high");
//            } else {
//                analogWrite(ledPin,val1);
//            }

                if(val1 > 255) {
                    Serial.print("a value was too high \r\n");
                } else {
                    analogWrite(ledPin, val1);
                }

        }
        
    
    }

}
