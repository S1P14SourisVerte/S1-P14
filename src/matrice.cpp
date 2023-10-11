#include "matrice.h"

int path[ROWS][COLUMNS];

void MatriceInit(void) {
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
            path[i][j] = 0;
}