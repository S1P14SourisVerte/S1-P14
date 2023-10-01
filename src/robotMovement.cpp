#include "robotMovement.h"

void move(float motorSpeed, int distance_cm)
{
  // resetEncoders();
  MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * 0.9);
  MOTOR_SetSpeed(RIGHT_MOTOR, motorSpeed);
  // delay(50);

  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;
  // float accelerationSpeed = 0.15f;

  while ((float)ENCODER_Read(LEFT_MOTOR) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    // if (accelerationSpeed < motorSpeed) 
    // {
    //   accelerationSpeed += MOTOR_BASE_SPEED / 20;
    // }
    // correctDirection(&motorSpeed);
    correctDirection(motorSpeed, PULSES_PER_WHEEL_CYCLE * distance_wheelCycles);
  }
  //stop();
}

void smoothMove(float motorSpeed, int distance_cm)
{
  resetEncoders();

  // float gearChangeDelay_ms = 20;
  float x = -5;
  // float startSpeed = motorSpeed / 10;

  // MOTOR_SetSpeed(LEFT_MOTOR, startSpeed * 0.9);
  // MOTOR_SetSpeed(RIGHT_MOTOR, startSpeed);

  // float currentSpeed = startSpeed;
  float currentSpeed = 0;
  float distance_wheelCycles = (float)distance_cm / WHEEL_CIRCONFERENCE_CM;

  while ((float)ENCODER_Read(LEFT_MOTOR) <= PULSES_PER_WHEEL_CYCLE * distance_wheelCycles)
  {
    // if (accelerationSpeed < motorSpeed)
    // {
    //   accelerationSpeed += MOTOR_BASE_SPEED / 20;
    // }
    // correctDirection(&motorSpeed);

    if (currentSpeed < motorSpeed)
    {
      currentSpeed = motorSpeed * exp(x);
      // Serial.print("x: ");
      // Serial.print(x);
      // Serial.print(", speed: ");
      // Serial.println(currentSpeed);
      x += 0.1;
      // currentSpeed += 0.01;
      MOTOR_SetSpeed(LEFT_MOTOR, currentSpeed);
      MOTOR_SetSpeed(RIGHT_MOTOR, currentSpeed);
      // delay(gearChangeDelay_ms);
    }
    else if (currentSpeed > motorSpeed)
    {
      currentSpeed = motorSpeed;
      MOTOR_SetSpeed(LEFT_MOTOR, currentSpeed * 0.9);
      MOTOR_SetSpeed(RIGHT_MOTOR, currentSpeed);
    }
    correctDirection(currentSpeed, PULSES_PER_WHEEL_CYCLE * distance_wheelCycles);
  }
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

/*void correctDirection(float motorSpeed)
{
  Serial.print("1: ");
  Serial.print(ENCODER_Read(LEFT_MOTOR));
  Serial.print(", 2: ");
  Serial.println(ENCODER_Read(RIGHT_MOTOR));

  // float correctionMotorSpeedFactor = 0;

  // if (motorSpeed <= 0.2) {
  //   correctionMotorSpeedFactor = 1.5;
  // } else if (motorSpeed <= 0.5) {
  //   correctionMotorSpeedFactor = 1.25;
  // } else if (motorSpeed <= 0.7) {
  //   correctionMotorSpeedFactor = 1.1;
  // } else {
  //   correctionMotorSpeedFactor = 1.05;
  // }

  // 0.9 = 1.05
  // 0.4 = 1.25
  // float correctionMotorSpeedFactor = CORRECTION_MOTOR_SPEED_FACTOR;
  // correctionMotorSpeedFactor

  if (abs(ENCODER_Read(LEFT_MOTOR)) > abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    // MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed / correctionMotorSpeedFactor);
    MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed / CORRECTION_MOTOR_SPEED_FACTOR);
  }
  else if (abs(ENCODER_Read(LEFT_MOTOR)) < abs(ENCODER_Read(RIGHT_MOTOR)))
  {
    // MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * correctionMotorSpeedFactor);
    MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed * CORRECTION_MOTOR_SPEED_FACTOR);
  }
}*/

void correctDirection_t1(float *motorSpeed)
{
  // 3200/3100 = 1 - 1.05 = -0.05
  // 3100/3200 = 1 - 0.95 = 0.05

  Serial.print("LP: ");
  Serial.print(ENCODER_Read(LEFT_MOTOR));
  Serial.print(", RP: ");
  Serial.print(ENCODER_Read(RIGHT_MOTOR));

  if (ENCODER_Read(LEFT_MOTOR) == 0 && ENCODER_Read(RIGHT_MOTOR) == 0)
  {
    Serial.println("");
    return;
  }

  // float pulsesRatio = 1.0f - ((float)ENCODER_Read(LEFT_MOTOR) / (float)ENCODER_Read(RIGHT_MOTOR));
  float pulsesRatio = ((float)ENCODER_Read(LEFT_MOTOR) / (float)ENCODER_Read(RIGHT_MOTOR));
  // *motorSpeed = *motorSpeed * (1.0 + pulsesRatio);
  // *motorSpeed = *motorSpeed * pulsesRatio;
  // *motorSpeed = pulsesRatio >= 1 ? *motorSpeed / pulsesRatio : *motorSpeed * pulsesRatio;
  *motorSpeed = *motorSpeed / pulsesRatio;

  Serial.print(", ratio: ");
  Serial.print(pulsesRatio);
  Serial.print(", power: ");
  Serial.println(*motorSpeed);

  MOTOR_SetSpeed(LEFT_MOTOR, *motorSpeed);
}

void correctDirection(float motorSpeed, float distance_pulses)
{
  // Serial.print("LP: ");
  // Serial.print(ENCODER_Read(LEFT_MOTOR));
  // Serial.print(", RP: ");
  // Serial.print(ENCODER_Read(RIGHT_MOTOR));

  if (ENCODER_Read(LEFT_MOTOR) == 0 && ENCODER_Read(RIGHT_MOTOR) == 0)
  {
    // Serial.println("");
    return;
  }

  if (motorSpeed < 0.1)
  {
    return;
  }

  float expectedPulses = (float)ENCODER_Read(LEFT_MOTOR);
  float currentPulses = (float)ENCODER_Read(RIGHT_MOTOR);
  Serial.print("expec: ");
  Serial.print(expectedPulses);
  Serial.print(", cur: ");
  Serial.print(currentPulses);

  float pulsesDifference = expectedPulses - currentPulses;
  Serial.print(", diff: ");
  Serial.print(pulsesDifference);
  // Marche pour le left avec 0.0005
  float newSpeedLeft = motorSpeed - (0.0005 * pulsesDifference);
  float newSpeedRight = motorSpeed + (0.0001 * pulsesDifference);
  Serial.print(", nspeedL: ");
  Serial.print(newSpeedLeft);
  Serial.print(", nspeedR: ");
  Serial.println(newSpeedRight);

  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
  // MOTOR_SetSpeed(RIGHT_MOTOR, newSpeedRight);

  // float pulsesRatio = ((float)ENCODER_Read(LEFT_MOTOR) / (float)ENCODER_Read(RIGHT_MOTOR));
  // *motorSpeed = *motorSpeed * (1.0 + pulsesRatio);
  // *motorSpeed = *motorSpeed * pulsesRatio;
  // *motorSpeed = pulsesRatio >= 1 ? *motorSpeed / pulsesRatio : *motorSpeed * pulsesRatio;
  // motorSpeed = motorSpeed / pulsesRatio;

  // Serial.print(", ratio: ");
  // Serial.print(pulsesRatio);
  // Serial.print(", power: ");
  // Serial.println(newSpeed);

  // MOTOR_SetSpeed(LEFT_MOTOR, motorSpeed);
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