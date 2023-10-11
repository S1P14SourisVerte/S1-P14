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
}

// #ifdef ROBOT_B
// void turn(float motorSpeed,  turnDirection direction, float angle = 90.0f) 
// {
//   resetEncoders();

//   int distance_pulses = 
//     (((angle / 360) * SELF_TURN_CIRCONFERENCE_CM) / WHEEL_CIRCONFERENCE_CM) * PULSES_PER_WHEEL_CYCLE;

//   int currentLeftPulses = abs(ENCODER_Read(LEFT_MOTOR));
//   int currentRightPulses = abs(ENCODER_Read(RIGHT_MOTOR));
//   int pulsesDifference = currentLeftPulses - currentRightPulses;

//   while (currentLeftPulses < distance_pulses) {
    
//     #ifdef DEBUG
//       Serial.print("lp: ");
//       Serial.print(currentLeftPulses);
//       Serial.print(", rp: ");
//       Serial.print(currentRightPulses);
//       Serial.print(", pd: ");
//       Serial.println(pulsesDifference);
//     #endif

//     if (pulsesDifference > 0) {
//       MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction / (1 + (TURN_CORRECTION_FACTOR * (0.001 * pulsesDifference))));
//       MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction);
//     } else if (pulsesDifference < 0) {
//       MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction);
//       MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction / (1 + (TURN_CORRECTION_FACTOR * (0.001 * pulsesDifference))));
//     } else {
//       MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction);
//       MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction);
//     }
    
//     currentLeftPulses = abs(ENCODER_Read(LEFT_MOTOR));
//     currentRightPulses = abs(ENCODER_Read(RIGHT_MOTOR));
//     pulsesDifference = currentLeftPulses - currentRightPulses;
//   }
//   MOTOR_SetSpeed(LEFT_MOTOR, 0);
//   MOTOR_SetSpeed(RIGHT_MOTOR, 0);
// }
// #endif

#ifdef ROBOT_A
void turnA(float motorSpeed, turnDirection direction, float angle = 90.0)
{
  resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * direction);
  MOTOR_SetSpeed(RIGHT_MOTOR, -motorSpeed * direction);
  float angleCorrectionFactor = 1.5;
  if (direction == LeftTurn) {
    angleCorrectionFactor = 1.5;
  }
  else {
    angleCorrectionFactor = 0.5;
  }
  float distance_cm = ((SELF_TURN_CIRCONFERENCE_CM / 360.0f) * (angle - angleCorrectionFactor));
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;
  while (abs((float)ENCODER_Read(LEFT_MOTOR)) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    correctTurnDirection(motorSpeed, direction);
  }
  stop();
}
#endif

#ifdef ROBOT_B
void turn(float motorSpeed, turnDirection direction, float angle = 90.0)
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

  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
}

void resetEncoders()
{
  ENCODER_ReadReset(LEFT_MOTOR);
  ENCODER_ReadReset(RIGHT_MOTOR);
}