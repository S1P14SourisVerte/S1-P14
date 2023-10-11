#ifndef MATRICE_H
#define MATRICE_H

#define ROWS 10
#define COLUMNS 3

#define START_ROW 9
#define END_ROW 0

#define FIRST_COLUMN 0
#define SECOND_COLUMN 1
#define THIRD_COLUMN 2

extern int path[ROWS][COLUMNS];

void MatriceInit(void);
#endif