#include <Arduino.h>
#include <LibRobus.h>

#define ROW 10
#define COLUMN 3
#define BOX_DIMENSION 50

int boxPossibility[ROW][COLUMN];
int signal;

struct Status {
  char facing;  // Robus can face north, east and west
  int posX;
  int posY;
} robus;

void MatriceInit() {

  //Filling the matrice with the possible route
  for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COLUMN; j++)
      boxPossibility[i][j] = 1

  /***					Forbidden boxes						***/
  //boxPossibility[][] = 0; If there's any
}

void Forward(int distance) {
  if (robus.facing == 'e')
    robus.posX += distance;
  else if (robus.facing == 'w')
    robus.posX -= distance;
  else
    robus.posY += distance);

  // code to make Robus go forward
}

void Rotation(float speed, float angle, int direction) {
  float ratio_p_a;
  float ratio_a_c;
  float circonferenceTrajectory = 47;
  float circonferenceWheel = 9.4247;
  float pulses;
  float pulseEncoder1;
  float pulseEncoder2;

  ratio_a_c = (angle / 360) * circonferenceTrajectory;
  ratio_p_a = (ratio_a_c / circonferenceWheel);
  pulses = (ratio_p_a * 3200);

  // Encoder variable
  pulseEncoder1 = ENCODER_Read(0);
  pulseEncoder2 = ENCODER_Read(1);

  if (direction == 0) {
    while ((pulses >= pulseEncoder1) && (pulses >= pulseEncoder2)) {
      MOTOR_SetSpeed(0, (0.9721 * speed));
      MOTOR_SetSpeed(1, -speed);
      pulseEncoder1 = ENCODER_Read(0);
      pulseEncoder2 = ENCODER_Read(1);
    }
  } else
    while ((pulses >= pulseEncoder1) && (pulses >= pulseEncoder2)) {
      MOTOR_SetSpeed(0, (-0.988 * speed));
      MOTOR_SetSpeed(1, speed);
      pulseEncoder1 = ENCODER_Read(0);
      pulseEncoder2 = ENCODER_Read(1);
    }

  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}

void RotateLeft(float angle) {
  if (robus.facing == 'n')
    robus.facing = 'w';
  else
    robus.facing = 'n';

  Rotation(0.2, angle, 1)
}

void RotateRight(float angle) {
  if (robus.facing == 'n')
    robus.facing = 'e';
  else
    robus.facing = 'n';

  Rotation(0.2, angle, 0)
}

void Beginning() {
  if (/*IR Sensor sends positive output*/) {
    
    RotateLeft(90);
    if (/*IR Sensor sends positive output*/){
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
    if (boxPossibility[robus.posY][i] == robus.posX)
      return i;
}

int FindPath() {
  if ((robus.posY) % 2 == 0)
    if (/*IR Sensor sends positive output*/)
      switch (CheckSurounding()) {
        case -1:  //Tape on the right

          break;
        case 0:  //In the middle

          break;
        case 1:  //Tape on the left

          break;
        default:
          break;
      }
  Forward(2);
}

void setup() {
  BoardInit();
  MatriceInit();

  signal = 0;
  robus.facing = 'n';
  robus.posX = 1;
  robus.posY = 9;
}

void loop() {
  if (/*The buzzer has been activated*/)
    signal = 1;

  if (signal == 1)
    if (robus.posY == 0)
      Beginning();
    else if (robus.posY == 9)
      Stop();
    else
      FindPath();
}
