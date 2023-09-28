#include <LibRobus.h>

#ifdef ROBOT_B
    #define CORRECTION_REAR_WHEEL_RIGHT_TURN_DEG 1.5f
    #define CORRECTION_REAR_WHEEL_LEFT_TURN_DEG 1.75f
#else
    #ifdef ROBOT_A
        #define CORRECTION_REAR_WHEEL_RIGHT_TURN_DEG 100.0f
        #define CORRECTION_REAR_WHEEL_LEFT_TURN_DEG 100.0f
    #endif
#endif

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define MOTOR_BASE_SPEED 0.01f

#define WHEEL_CIRCONFERENCE_CM 23.93f
#define PULSES_PER_WHEEL_CYCLE 3200.0f

#define SELF_TURN_CIRCONFERENCE_CM 59.3761f

#define CORRECTION_MOTOR_SPEED_FACTOR 1.05f
// #define CORRECTION_MOTOR_SPEED_FACTOR 1.25f
// #define CORRECTION_REAR_WHEEL_DEGREE 1.75f

typedef enum {
    RightTurn = 1,
    LeftTurn = -1 
} turnDirection;

void move(float motorSpeed, int distance_cm);
void stop();
void sharpTurn(float motorSpeed, float degree, turnDirection direction);
void smoothTurn(float motorSpeed, float degree, turnDirection direction);
// void correctDirection(float motorSpeed);
void correctDirection(float* motorSpeed);
void correctTurnDirection(float motorSpeed);
void resetEncoders();