#include <Arduino.h>

void setup() {
    Serial.begin(9600);

    pinMode(INPUT,A0);
}

void loop() {

    int valueIn = analogRead(A0);

    //Serial.println(valueIn);
    
    if (valueIn >= 500){
        Serial.print("GO!!!");
    }
    
    
    delay(100);
}