#include <LibRobus.h>

#include "math.h"

#ifdef ROBOT_B
    #define TURN_CORRECTION_FACTOR 3
    // #define CORRECTION_REAR_WHEEL_RIGHT_TURN_DEG 1.5f
    // #define CORRECTION_REAR_WHEEL_LEFT_TURN_DEG 1.75f
#else
    #ifdef ROBOT_A
        #define TURN_CORRECTION_FACTOR 3
        // #define CORRECTION_REAR_WHEEL_RIGHT_TURN_DEG 100.0f
        // #define CORRECTION_REAR_WHEEL_LEFT_TURN_DEG 100.0f
    #endif
#endif

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define MOTOR_BASE_SPEED 0.01f

#define WHEEL_CIRCONFERENCE_CM 23.93f
#define SELF_TURN_CIRCONFERENCE_CM 60.65f
#define PULSES_PER_WHEEL_CYCLE 3200.0f

#define CORRECTION_MOTOR_SPEED_FACTOR 1.25f
// #define CORRECTION_MOTOR_SPEED_FACTOR 1.25f
// #define CORRECTION_REAR_WHEEL_DEGREE 1.75f

typedef enum {
    RightTurn = 1,
    LeftTurn = -1 
} turnDirection;

void move(float motorSpeed, int distance_cm);
void turn(float motorSpeed, turnDirection direction, float angle = 90.0f);
void stop();
void correctDirection(float motorSpeed, float distance_pulses);
void correctTurnDirection(float motorSpeed, turnDirection direction);
void resetEncoders();