#include <Arduino.h>

#define GREEN 28
#define RED 26

int detection_mur();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(GREEN, INPUT);
  pinMode(RED, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(String(detection_mur()));
  delay(500);

}

int detection_mur()
{
  int green = digitalRead(GREEN);
  int red = digitalRead(RED);

  if(green == 0 && red == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}