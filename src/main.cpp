#include <LibRobus.h>

#include "robotMovement.h"

void buzz();

void setup()
{
  BoardInit();
  // move(0.15f, 3);
  // move(0.20f, 3);
  // move(0.25f, 3);
  // move(0.30f, 3);
  // move(0.35f, 3);
  // move(0.40f, 120); 
  // move(0.35f, 3);
  // move(0.30f, 3);
  // move(0.25f, 3);
  // move(0.20f, 3);
  // move(0.15f, 3);
  // stop();
  // sharpTurn(0.25f, 180, LeftTurn);
  // move(0.40f, 150);
  // sharpTurn(0.25f, 180, RightTurn);
  // move(0.40f, 150);
}

void loop()
{
  if (ROBUS_IsBumper(3)) {
    move(0.8f, 150);
    stop();
  }
}

void buzz() 
{
  AX_BuzzerON();
  delay(100);
  AX_BuzzerOFF();
}