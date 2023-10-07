#include <Arduino.h>
#include <LibRobus.h>

#include "robotMovement.h"
#include "detection.h"

#define ROW 10
#define COLUMN 3
#define BOX_DIMENSION 50

int signal;

void Forward(int distance) {
  move(0.2, 50);
}

void RotateLeft(float angle) {
  turn(0.2, angle, 1);
}

void RotateRight(float angle) {
  turn(0.2, angle, 0);
}

void Beginning() {
  if (1/*IR Sensor sends positive output*/) {
    
    RotateLeft(90);
    if (1/*IR Sensor sends positive output*/){
       RotateRight(180);
       Forward(2);
       RotateLeft(90);
    }else{
        Forward(1);
        RotateRight(90);
    }
  }
  Forward(2);
}

int CheckSurrounding() {
  for (int i = 0; i < COLUMN; i++)
    if (i == robus.posX)
      return i;
}

int FindPath() {
  if ((robus.posY) % 2 == 0)
    if (1/*IR Sensor sends positive output*/) {
      switch (1/*CheckSurounding()*/) {
        case -1:  //Tape on the right

          break;
        case 0:  //In the middle

          break;
        case 1:  //Tape on the left

          break;
        default:
          break;
      }
    }
  Forward(2);
}

void setupPathfinder() {
  BoardInit();

  signal = 0;
  robus.facing = 'n';
  robus.posX = 1;
  robus.posY = 9;
}

void loopPathfinder() {
  if (1/*The buzzer has been activated*/)
    signal = 1;

  if (signal == 1){
    


  }
    
    else if (robus.posY == 9)
      signal = 0;
   
}
