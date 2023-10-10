#include "matrice.h"

float orientation;
int path[ROWS][COLUMNS];

void MatriceInit(void) {
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
            path[i][j] = 0;
    /***					Forbidden boxes						***/
	//path[][] = 1; If there's any
    orientation = 0;
}