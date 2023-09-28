#include "robotMovement.h"

void move(float motorSpeed, int distance_cm)
{
  resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed);
  MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed);

  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;
  float accelerationSpeed = 0.15f;

  while ((float)ENCODER_Read(LEFT_MOTOR) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    if (accelerationSpeed < motorSpeed) 
    {
      accelerationSpeed += MOTOR_BASE_SPEED / 20;
    }
    correctDirection(motorSpeed);
  }
  //stop();
}

void stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

void sharpTurn(float motorSpeed, float degree, turnDirection direction)
{
  // You're breaking the car Samir!
  resetEncoders();

  motorSpeed *= direction;

  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed);
  MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed);

  if (direction == LeftTurn)
    degree -= CORRECTION_REAR_WHEEL_LEFT_TURN_DEG;
  else if (direction == RightTurn)
    degree -= CORRECTION_REAR_WHEEL_RIGHT_TURN_DEG;

  float distance_cm = ((SELF_TURN_CIRCONFERENCE_CM / 360.0f) * degree);
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;

  while (abs((float)ENCODER_Read(LEFT_MOTOR)) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    correctTurnDirection(motorSpeed);
  }
  stop();
}

void smoothTurn(float motorSpeed, float degree, turnDirection direction)
{

}

void correctDirection(float motorSpeed)
{
  if (abs(ENCODER_Read(LEFT_MOTOR)) < abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed / CORRECTION_MOTOR_SPEED_FACTOR);
  }
  else if (abs(ENCODER_Read(LEFT_MOTOR)) > abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed * CORRECTION_MOTOR_SPEED_FACTOR);
  }
}

// void correctDirection(float motorSpeed)
// {
//   if (abs(ENCODER_Read(LEFT_MOTOR)) < abs(ENCODER_Read(RIGHT_MOTOR)))
//   {
//     MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed / CORRECTION_MOTOR_SPEED_FACTOR);
//   }
//   else if (abs(ENCODER_Read(LEFT_MOTOR)) > abs(ENCODER_Read(RIGHT_MOTOR)))
//   {
//     MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed * CORRECTION_MOTOR_SPEED_FACTOR);
//   }
// }

void correctTurnDirection(float motorSpeed)
{
  if (abs(ENCODER_Read(LEFT_MOTOR)) < abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed / CORRECTION_MOTOR_SPEED_FACTOR);
  }
  else if (abs(ENCODER_Read(LEFT_MOTOR)) > abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * CORRECTION_MOTOR_SPEED_FACTOR);
  }
}

void resetEncoders()
{
  ENCODER_ReadReset(LEFT_MOTOR);
  ENCODER_ReadReset(RIGHT_MOTOR);
}