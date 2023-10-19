#include "matrice.h"

int path[ROWS][COLUMNS];

void MatriceInit(void) {
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLUMNS; j++)
            if(j == 1 && i % 2 == 0 && i != 4)
                path[i][j] = 1;
            else
                path[i][j] = 0;
}