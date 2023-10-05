#include <Arduino.h>

#define PIN_WHISTLE A0
int detect_whistle();
void setup() {
    Serial.begin(9600);

    pinMode(INPUT,PIN_WHISTLE);
}

void loop() {

    

    //Serial.println(valueIn);
    Serial.print(String(detect_whistle()));
    
    
    
    delay(100);
}

int detect_whistle()
{
    int valueIn = analogRead(PIN_WHISTLE);
    //Serial.println(String(valueIn));
    if (valueIn >= 500)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}