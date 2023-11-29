#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"
#include "matrice.h"

#define TURN_SPEED 0.10
#define FORWARD_SPEED 0.25

int active;

void setup() {
  BoardInit();
  RobotMouvementInit();
  DetectionInit();
  MatriceInit();
  active = YES;
}

// Initial: robot.posX = 1 (milieu) et robot.posY = 0 (première) en regardant le nord

void loop() {

  if (detect_whistle() == 1)
    active = YES;

  if(robot.posY == 0) {
    active = NO;
    // Serial.println(robot.posY);
  }

  if(active == YES) {
    delay(100);

    // SI LE ROBOT EST À GAUCHE
    if(robot.posX == 0)
    {
      if (detect_wall() == 1)
      {
        path[robot.posY][0] = 1;
        turn(TURN_SPEED, RightTurn, 90);
        move(FORWARD_SPEED, 50);
        delay(100);
        robot.posX = 1;
        turn(TURN_SPEED, LeftTurn, 90);
      }
      else
      {
        while (detect_wall() == 0)
        {
          move(FORWARD_SPEED, 50);
          delay(100);
          robot.posY--;
        }
      }
    }

  // SI LE ROBOT EST AU MILIEU DU PARCOURS
    else if(robot.posX == 1)
    {

      if (detect_wall() == 1)
      {
        if (path[robot.posY][0] == 0)
        {
          turn(TURN_SPEED, LeftTurn, 90);
          move(FORWARD_SPEED, 50);
          delay(100);
          // CHANGER POUR UN NÉGATIF 90 FONCTION MARCHE PAS ENCORE AVEC NEGATIF
          turn(TURN_SPEED, RightTurn, 90);
          robot.posX = 0;
        }

        else
        {
          turn(TURN_SPEED, RightTurn, 90);
          move(FORWARD_SPEED, 50);
          delay(100);
          turn(TURN_SPEED, LeftTurn, 90);
          robot.posX = 2;
        }
      }

      else 
      {
        while (detect_wall() == 0)
        {
          move(FORWARD_SPEED, 50);
          delay(100);
          robot.posY--;
        }
      }

    }

  // SI LE ROBOT EST À DROITE
    else if (robot.posX == 2)
    {
      if (detect_wall() == 1)
      {
        path[robot.posY][2] = 1;
        turn(TURN_SPEED, LeftTurn, 90);
        move(FORWARD_SPEED, 50);
        delay(100);
        robot.posX = 1;
        turn(TURN_SPEED, RightTurn, 90);
      }
      else
      {
        while (detect_wall() == 0)
        {
          move(FORWARD_SPEED, 50);
          delay(100);
          robot.posY--;
        }
      }
    }
  }
}


//   active = (detect_wall() == 0) ? YES : NO;

//   if (active == YES) { // There's no wall
//     path[robot.posY][robot.posX] = 1;
//     orientation = 0;

//     move(0.2, BOX_DIMENSION);
//     Serial.print("X : ");
//     Serial.println (robot.posX);
//     Serial.print("Y : ");
//     Serial.println(robot.posY);

//   } else { // There's a wall
//     if(robot.posY == 0) {
//       turn(0.2, 90);

//       Serial.println(robot.facing);
//     } 
//     else if(robot.posY % 2 == 0) {
//      turn(0.2, 90);
//     }
//   }
// }
