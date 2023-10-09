#include "detection.h"

int detect_wall(void) {
    int green = digitalRead(GREEN);
    int red = digitalRead(RED);
    return((green == 0 && red == 0) ? 1 : 0);
}

int detect_whistle(void) {
    int valueIn = analogRead(PIN_WHISTLE);
    return((valueIn >= 500) ? 1 : 0);
}

void DetectionInit(void) {
    Serial.begin(9600);
    pinMode(GREEN, INPUT);
    pinMode(RED, INPUT);
    pinMode(PIN_WHISTLE, INPUT);
}