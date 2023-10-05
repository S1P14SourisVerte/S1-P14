#include <Arduino.h>
#include <librobus.h>

#define ROW 21
#define COLUMN 7

int boxPossibility[ROW][COLUMN];
bool signal;

struct Status {
  char facing;  // Robus can face north, east and west
  int posX;
  int posY;
} robus;

void MatriceInit() {

  //Filling the matrice with the possible route
  for (int i = 0; i < ROW; i++)
    for (int j = 0; j < COLUMN; j++)
      if (j == 0 || j == 6 || i == 0 || i == 20 || ((i + 1) % 4 != 0 && j % 2 == 0))
        boxPossibility[i][j] = 0;
      else
        boxPossibility[i][j] = 1;

  /***					Forbidden boxes						***/
  //boxPossibility[][] = 0; If there's any
}

/*void ErasePath() {

  //Replace impossible path with 0
  if (robus.facing == 'n')
    for (int i = 1; i <= 3; i++)
      boxPossibility[robus.posY - i][robus.posX] = 0;
  else if (robus.facing == 'w')
    boxPossibility[robus.posY][robus.posX - 1] = 0;
  else if (robus.facing == 'e')
    boxPossibility[robus.posY][robus.posX + 1] = 0;
}*/

void Forward(int distance) {
  if (robus.facing == 'e')
    robus.posX += (distance * 2);
  else if (robus.facing == 'w')
    robus.posX -= (distance * 2);
  else
    robus.posY += (distance * 2);

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

void RotateLeft() {
  if (robus.facing == 'n')
    robus.facing = 'w';
  else
    robus.facing = 'n';

  Rotation(0.2, 90, 1)
}

void RotateRight() {
  if (robus.facing == 'n')
    robus.facing = 'e';
  else
    robus.facing = 'n';

  Rotation(0.2, 90, 0)
}

void Beginning() {
  if (/*IR Sensor sends positive output*/) {
    // Goes left to check if it's the right path
    RotateLeft();
    Forward(1);
    RotateRight();

    if (/*IR Sensor sends positive output*/) {
      // Goes right to check if it's the right path
      RotateRight();
      Forward(2);
      RotateLeft();
    }
  }
  Forward(2);
}

int CheckSurrounding() {
  for (int i = -1; i < 2; i++)
    if (boxPossibility[robus.posY][robus.posX + i] == 0)
      return i;
}

int FindPath() {
  if ((robus.posY + 1) % 4 == 0)
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

  signal = false;
  robus.facing = 'n';
  robus.posX = 3;
  robus.posY = 19;
}

void loop() {
  if (/*The buzzer has been activated*/)
    signal = true;

  if (signal == true)
    if (robus.posY == 19 && robus.posX == 3)
      Beginning();
    else
      FindPath();
}
