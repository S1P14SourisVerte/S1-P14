#include <Arduino.h>
#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"

#define START_ROW 1
#define END_ROW 9

#define FIRST_COLUMN 1
#define SECOND_COLUMN 2
#define THIRD_COLUMN 3

#define BOX_DIMENSION 50

int signal;

void setup() {
  BoardInit();
  RobotMouvementInit();
  DetectionInit();
  signal = ON;
}

void loop() {
  if (detect_whistle() == 1)
    signal = ON;

  if (rob.posY == END_ROW)
    signal = OFF;

  if (signal == ON){
      if(detect_wall() == 1)
        signal = OFF;
    move(0.2, BOX_DIMENSION);
  } 
}
