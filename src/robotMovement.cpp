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
  delay(100);
  Serial.print("X : ");
  Serial.println(robot.posX);
  Serial.print("Y : ");
  Serial.println(robot.posY);

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

#ifdef ROBOT_A
void turn(float motorSpeed, turnDirection direction, float angle = 90.0)
{
  resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction);
  MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction);
  float angleCorrectionFactor = 1.5;
  if (direction == LeftTurn) {
    angleCorrectionFactor = 0.45;
  }
  else {
    angleCorrectionFactor = 0.2;
  }
  float distance_cm = ((SELF_TURN_CIRCONFERENCE_CM / 360.0f) * (angle - angleCorrectionFactor));
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;
  while (abs((float)ENCODER_Read(LEFT_MOTOR)) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    correctTurnDirection(motorSpeed, direction);
  }
  stop();

  ChangeStatus(direction, angle);
  delay(100);
}
#endif

#ifdef ROBOT_B
void turn(float motorSpeed, turnDirection direction, float angle = 90.0f)
{
  resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction);
  MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction);
  float angleCorrectionFactor = 1.5;
  if (direction == LeftTurn) {
    angleCorrectionFactor = -1.15;
  }
  else {
    angleCorrectionFactor = -0.55;
  }
  float distance_cm = ((SELF_TURN_CIRCONFERENCE_CM / 360.0f) * (angle - angleCorrectionFactor));
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;
  while (abs((float)ENCODER_Read(LEFT_MOTOR)) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    correctTurnDirection(motorSpeed, direction);
  }
  stop();

  ChangeStatus(direction, angle);
  delay(100);
}
#endif

void correctTurnDirection(float motorSpeed, turnDirection direction)
{
  if (abs(ENCODER_Read(LEFT_MOTOR)) < abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(RIGHT_MOTOR, (-motorSpeed * direction) / CORRECTION_MOTOR_SPEED_FACTOR);
  }
  else if (abs(ENCODER_Read(LEFT_MOTOR)) > abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(LEFT_MOTOR, (motorSpeed * direction) / CORRECTION_MOTOR_SPEED_FACTOR);
  }
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
      robot.posY -= distance;
      break;
    case 's':
      robot.posY += distance;
      break;
    default:
      break;
  }
}

void ChangeStatus(turnDirection direction, float angle) {
  if(abs(angle) == 90)
    switch(robot.facing) {
      case 'n':
        robot.facing = (direction == LeftTurn) ? 'w' : 'e';
        break;
      case 'w':
        robot.facing = (direction == LeftTurn) ? 's' : 'n';
       break;
      case 'e':
       robot.facing = (direction == LeftTurn) ? 'n' : 's';
        break;
      case 's':
       robot.facing = (direction == LeftTurn) ? 'e' : 'w';
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