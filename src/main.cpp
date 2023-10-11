#include "LibRobus.h"

#include "robotMovement.h"

void buzz();

void setup()
{
  BoardInit();

  // move(0.3, 500);
  // stop();

}

void loop()
{
  // move(0.2, 50);
  // delay(50);
  // move(0.3, 250);
  turn(0.2, RightTurn);
  // turn(0.2, RightTurn);
  // turn2(0.2, 90, 0);
  // buzz();
  delay(1000);
  // turn(0.2, LeftTurn);
  // buzz();
  // delay(1000);
  // turn(0.1, RightTurn);
  // delay(1000);
  // if (ROBUS_IsBumper(3))
  // {
  //   move(0.2, 500);
  //   stop();
  // } else if (ROBUS_IsBumper(2))
  // {
  //   move(0.1, 250);
  //   stop();
  // } else if (ROBUS_IsBumper(1))
  // {
  //   move(0.9, 250);
  //   stop();
  // }
}

void buzz() 
{
  AX_BuzzerON();
  delay(100);
  AX_BuzzerOFF();
}