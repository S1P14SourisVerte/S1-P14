#include "robotMovement.h"

void move(float motorSpeed, int distance_cm)
{
  resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * 0.9);
  MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed);
  // sigmoid logistic
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;

  while ((float)ENCODER_Read(LEFT_MOTOR) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    correctDirection(motorSpeed, PULSES_PER_WHEEL_CYCLE * distance_wheelCycles);
  }
  stop();
  
  ChangeStatus(distance_cm);
}

void stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

void correctDirection(float motorSpeed, float distance_pulses)
{
  if (ENCODER_Read(LEFT_MOTOR) == 0 && ENCODER_Read(RIGHT_MOTOR) == 0)
  {
    return;
  }

  if (motorSpeed < 0.1)
  {
    return;
  }

  float expectedPulses = (float)ENCODER_Read(LEFT_MOTOR);
  float currentPulses = (float)ENCODER_Read(RIGHT_MOTOR);

  float pulsesDifference = expectedPulses - currentPulses;
  if (pulsesDifference == 0)
  {
    return;
  }
  float newSpeedLeft = motorSpeed - (0.0005 * pulsesDifference);
  /*#ifdef DEBUG
    Serial.print("expec: ");
    Serial.print(expectedPulses);
    Serial.print(", cur: ");
    Serial.print(currentPulses);
    Serial.print(", diff: ");
    Serial.print(pulsesDifference);
    Serial.print(", nspeedL: ");
    Serial.println(newSpeedLeft);
  #endif*/

  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
}

void resetEncoders()
{
  ENCODER_ReadReset(LEFT_MOTOR);
  ENCODER_ReadReset(RIGHT_MOTOR);
}

void turn(float speed, float angle, int direction) {

  resetEncoders();

  float ratio_p_a;
  float ratio_a_c;
  float circonferenceTrajectory = 23.88;
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

  ChangeStatus(angle, direction); // 0: Right   1:Left
}

void ChangeStatus(int distance) {
  switch (rob.facing) {
    case 'e':
      rob.posX += distance;
        break;
    case 'w':
      rob.posX -= distance;
      break;
    case 'n':
      rob.posY += distance;
      break;
    case 's':
      rob.posY -= distance;
      break;
    default:
      break;
  }
}

void ChangeStatus(float angle, int direction) {
  if(angle == 90)
    switch(rob.facing) {
      case 'n':
        rob.facing = (direction == 1) ? 'w' : 'e';
        break;
      case 'w':
        rob.facing = (direction == 1) ? 's' : 'n';
       break;
      case 'e':
       rob.facing = (direction == 1) ? 'n' : 's';
        break;
      case 's':
       rob.facing = (direction == 1) ? 'e' : 'w';
         break;
      default:
         break;
    }
  else
    switch(rob.facing) {
      case 'n':
        rob.facing = 's';
        break;
      case 'w':
        rob.facing = 'e';
        break;
      case 'e':
        rob.facing = 'w';
        break;
      case 's':
        rob.facing = 'n';
        break;
      default:
        break;
    }
}

void RobotMouvementInit(void) {
  rob.facing = 'n';
  rob.posX = 1;
  rob.posY = 9;
}