#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"

#define START_ROW 1
#define END_ROW 9

#define FIRST_COLUMN 1
#define SECOND_COLUMN 2
#define THIRD_COLUMN 3

int signal;
int add_degree;

void setup() {
  BoardInit();
  RobotMouvementInit();
  DetectionInit();
  signal = ON;
  add_degree = 0;
}

void loop() {
  
  if (detect_whistle() == 1)
    signal = ON;

  signal = (detect_wall() == 0) ? ON : OFF;
  
  if(signal == OFF){
        turn(0.2, 90 + add_degree, LEFT);
        add_degree = 90;
  }
    turn(0.2, 90, LEFT);
  
  if (signal == ON) {
    move(0.3, BOX_DIMENSION);
    Serial.print("X : ");
    Serial.println (robot.posX);
    Serial.print("Y : ");
    Serial.println(robot.posY); 
    add_degree = 0;
  } 
}
