#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"
#include "matrice.h"

int active;

void setup() {
  BoardInit();
  RobotMouvementInit();
  DetectionInit();
  MatriceInit();
  active = YES;
}

void loop() {

  if (detect_whistle() == 1)
    active = YES;

  if(robot.posY == 9) {
    active = NO;
    Serial.println(robot.posY);
  }

  active = (detect_wall() == 0) ? YES : NO;

  if (active == YES) { // There's no wall
    path[robot.posY][robot.posX] = 1;
    orientation = 0;

    move(0.2, BOX_DIMENSION);
    Serial.print("X : ");
    Serial.println (robot.posX);
    Serial.print("Y : ");
    Serial.println(robot.posY);

  } else { // There's a wall
    if(robot.posY == 0) {
      turn(0.2, 90);
    } 
    else if(robot.posY % 2 == 0) {
     turn(0.2, 90);
    }
  }
}
