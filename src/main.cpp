#include <Arduino.h>

void setup() {
    Serial.begin(9600);

    pinMode(OUTPUT,A0);
}

void loop() {

    int valueOut = analogRead(A0);

    if (valueOut >= 500){
        Serial.print("GO!!!");
    }
    
    delay(100);
}