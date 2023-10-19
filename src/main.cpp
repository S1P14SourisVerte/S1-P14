#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"
#include "matrice.h"

#define TURN_SPEED 0.2
#define FORWARD_SPEED 0.3

int active;

void setup() {
  BoardInit();
  RobotMouvementInit();
  DetectionInit();
  MatriceInit();
  active = NO;
}

// Initial: robot.posX = 1 (milieu) et robot.posY = 9 (première) en regardant le nord

void loop() {
  
  if(detect_whistle() == 1)
    active = YES;

  if(robot.posY == END_ROW){
      robot.posX = 1;
      robot.posY = 9;
      active = NO;
  }

  if(active == YES) {
    delay(500);

    /***    Robot is in the first column      ***/
    if(robot.posX == 0)
    {
      Serial.println(robot.posX);
      if (detect_wall() == 1)
      {
        path[robot.posY][robot.posX] = 1;
        turn(TURN_SPEED, RightTurn);
        move(FORWARD_SPEED, BOX_DIMENSION);

        if(detect_wall() == 1) 
        {
          turn(TURN_SPEED, LeftTurn);

          if(detect_wall() == 1 || path[robot.posY - 1][robot.posX] == 1) 
          {
            turn(TURN_SPEED, RightTurn, 180.0f);

            while (detect_wall() == 0 || robot.posY > END_ROW || path[robot.posY + 1][robot.posX] == 1)
             move(FORWARD_SPEED, BOX_DIMENSION);

            turn(TURN_SPEED, LeftTurn);
            move(FORWARD_SPEED, BOX_DIMENSION);
            turn(TURN_SPEED, LeftTurn);

            while (detect_wall() == 0 || robot.posY > END_ROW)
             move(FORWARD_SPEED, BOX_DIMENSION);
          }
        }
        else 
        {
          move(FORWARD_SPEED, BOX_DIMENSION);
          turn(TURN_SPEED, LeftTurn);
        }
      }
      else
        while (detect_wall() == 0 || robot.posY > END_ROW) {
          move(FORWARD_SPEED, BOX_DIMENSION); 
             

        }
    }

    /***    Robot is in the second column      ***/
    else if(robot.posX == 1)
    {

      if (path[robot.posY - 1][robot.posX] == 1)
      {
        if (path[robot.posY][robot.posX - 1] == 0)
        {
          turn(TURN_SPEED, LeftTurn);
          if(detect_wall() == 1)
          {
            turn(TURN_SPEED, LeftTurn, 180);
            move(FORWARD_SPEED, BOX_DIMENSION);
            turn(TURN_SPEED, LeftTurn);
          }
          else
          {
            move(FORWARD_SPEED, BOX_DIMENSION);
            turn(TURN_SPEED, RightTurn);
          }
        }
        else
        {
          turn(TURN_SPEED, RightTurn);
          move(FORWARD_SPEED, BOX_DIMENSION);
          turn(TURN_SPEED, LeftTurn);
        }
      }
      else 
        while (detect_wall() == 0 || robot.posY > END_ROW || path[robot.posY - 1][robot.posX] == 1)
          move(FORWARD_SPEED, BOX_DIMENSION);
    }

    /***    Robot is in the third column      ***/
    else if (robot.posX == 2)
    {
      if (detect_wall() == 1)
      {
        path[robot.posY][robot.posX] = 1;
        turn(TURN_SPEED, LeftTurn);
        move(FORWARD_SPEED, BOX_DIMENSION);

        if(detect_wall() == 1) 
        {
          turn(TURN_SPEED, RightTurn);

          if(detect_wall() == 1 || path[robot.posY - 1][robot.posX] == 1) 
          {
            turn(TURN_SPEED, LeftTurn, 180.0f);

            while (detect_wall() == 0 || robot.posY > END_ROW || path[robot.posY + 1][robot.posX] == 1)
             move(FORWARD_SPEED, BOX_DIMENSION);

            turn(TURN_SPEED, RightTurn);
            move(FORWARD_SPEED, BOX_DIMENSION);
            turn(TURN_SPEED, RightTurn);

            while (detect_wall() == 0 || robot.posY > END_ROW)
             move(FORWARD_SPEED, BOX_DIMENSION);
          }
        }
        else 
        {
          move(FORWARD_SPEED, BOX_DIMENSION);
          turn(TURN_SPEED, RightTurn);
        }
      }
      else
        while (detect_wall() == 0 || robot.posY > END_ROW)
          move(FORWARD_SPEED, BOX_DIMENSION);
    }
  }
}
