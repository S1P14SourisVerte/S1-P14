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

void Beginning() {

}

int FindPath() {

}

void setupStatus() {
  BoardInit();

  signal = OFF;
  robus.facing = 'n';
  robus.posX = 1;
  robus.posY = 9;
}

void loopPathfinder() {
  if (1/*The buzzer has been activated*/)
    signal = ON;

  if (robus.posY == END_ROW)
    signal = OFF;

  if (signal == ON){
    move(0.2, BOX_DIMENSION);

  } 
}
