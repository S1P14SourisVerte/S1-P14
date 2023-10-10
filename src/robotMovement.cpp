#include <LibRobus.h>

#include "math.h"
#include "robotMovement.h"

Status robot;

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
  
  ChangeStatus(distance_cm/BOX_DIMENSION);
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
  /*
  #ifdef DEBUG
    Serial.print("expec: ");
    Serial.print(expectedPulses);
    Serial.print(", cur: ");
    Serial.print(currentPulses);
    Serial.print(", diff: ");
    Serial.print(pulsesDifference);
    Serial.print(", nspeedL: ");
    Serial.println(newSpeedLeft);
  #endif
  */
  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
}

void resetEncoders()
{
  ENCODER_ReadReset(LEFT_MOTOR);
  ENCODER_ReadReset(RIGHT_MOTOR);
}

void turn(float speed, float angle) {

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

  if (angle > 0) {
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

  ChangeStatus(angle); // Positive angle : LEFT   Negative angle : RIGHT
}

void ChangeStatus(int distance) {
  switch (robot.facing) {
    case 'e':
      robot.posX += distance;
        break;
    case 'w':
      robot.posX -= distance;
      break;
    case 'n':
      robot.posY += distance;
      break;
    case 's':
      robot.posY -= distance;
      break;
    default:
      break;
  }
}

void ChangeStatus(float angle) {
  if(abs(angle) == 90)
    switch(robot.facing) {
      case 'n':
        robot.facing = (angle > 0) ? 'w' : 'e';
        break;
      case 'w':
        robot.facing = (angle > 0) ? 's' : 'n';
       break;
      case 'e':
       robot.facing = (angle > 0) ? 'n' : 's';
        break;
      case 's':
       robot.facing = (angle > 0) ? 'e' : 'w';
         break;
      default:
         break;
    }
  else if(abs(angle) == 180)
    switch(robot.facing) {
      case 'n':
        robot.facing = 's';
        break;
      case 'w':
        robot.facing = 'e';
        break;
      case 'e':
        robot.facing = 'w';
        break;
      case 's':
        robot.facing = 'n';
        break;
      default:
        break;
    }
}

void RobotMouvementInit(void) {
  robot.facing = 'n';
  robot.posX = 1;
  robot.posY = 9;
}