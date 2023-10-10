#ifndef MATRICE_H
#define MATRICE_H

#define ROWS 10
#define COLUMNS 3

#define START_ROW 1
#define END_ROW 9

#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define THIRD_COLUMN 2

extern float orientation;
extern int path[ROWS][COLUMNS];

void MatriceInit(void);
#endif