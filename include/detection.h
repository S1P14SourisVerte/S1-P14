#ifndef DETECTION_H
#define DETECTION_H

#define ON 1
#define OFF 0
#define GREEN 28
#define RED 26
#define PIN_WHISTLE A0

int detect_wall(void);
int detect_whistle(void);
void DetectionInit(void);
#endif