#include <LibRobus.h>

#include "avr8-stub.h"
#include "robotMovement.h"

void buzz();

void setup()
{
  BoardInit();
  
  
  // move(0.4, 150);
  // stop();

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
  if (ROBUS_IsBumper(3)) 
  {
    move(0.4, 250);
    stop();
  } else if (ROBUS_IsBumper(2))
  {
    move(0.1, 250);
    stop();
  } else if (ROBUS_IsBumper(1))
  {
    move(0.9, 250);
    stop();
  }
}

void buzz() 
{
  AX_BuzzerON();
  delay(100);
  AX_BuzzerOFF();
}