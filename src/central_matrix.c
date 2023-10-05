/********
File: central_matrix.c
Autor: Félix Malhaire (malf1902)
Date: Saturday, September 30, 2023
Description: Robot movement algorithm in the central matrix of "Défi du parcours". 
********/
#define CENTER_COL 1
#define LEFT_COL 0
#define RIGHT_COL 2
#define LEFT_TURN 0
#define RIGHT_TURN 1
#define SPEED 0.2

int start_column_pos(void);
int wall(void);
void move(float motorSpeed, int distance_cm); 
void turn(float speed, float angle, int direction);

void loop(){
	int cur_row_pos;
	int cur_column_pos, pre_column_pos;
	cur_column_pos = start_column_pos();
	pre_column_pos = start_column_pos();
	cur_row_pos = 2;
	while (cur_row_pos != 8){
		if (cur_column_pos == CENTER_COL){
			if (pre_column_pos == CENTER_COL){
				if (wall() == 0){ 
					move(SPEED, 100);
					cur_row_pos += 2;
				}
				if (wall() == 1){
					turn(SPEED, 90, LEFT_TURN);
					if (wall() == 0){
						move(SPEED, 50);
						pre_column_pos = CENTER_COL;
						cur_column_pos = LEFT_COL;
						turn(SPEED, 90, RIGHT_TURN);
						move(SPEED, 100);
						cur_row_pos += 2;
					}
					if (wall() == 1){
						turn(SPEED, 180, RIGHT_TURN);
						move(SPEED, 50);
						pre_column_pos = CENTER_COL;
						cur_column_pos = LEFT_COL;
						turn(SPEED, 90, LEFT_TURN);
						move(SPEED, 100);
					}
				}
			}
			if (pre_column_pos == LEFT_COL){
				if (wall() == 0){ 
					move(SPEED, 50);
					pre_column_pos = CENTER_COL;
					cur_column_pos = RIGHT_COL;
					turn(SPEED, 90, LEFT_TURN);
					move(SPEED, 100);
					cur_row_pos += 2;
				}
				if (wall() == 1){
					turn(SPEED, 90, LEFT_TURN);
					if (wall() == 0)
						move(SPEED, 100);
						cur_row_pos += 2;
					if (wall() == 1){
						turn(SPEED, 180, RIGHT_TURN);
						move(SPEED, 100);
						cur_row_pos -= 2; //RETOUR ARRIÈRE
						while (wall() == 0){
							move (SPEED, 100);
							cur_row_pos -=2;
						}
						if(wall() == 1){
							if (pre_column_pos == LEFT_COL){
								turn(SPEED, 90, LEFT_TURN);
								move (SPEED, 50);
								pre_column_pos = CENTER_COL;
								cur_column_pos = RIGHT_COL;
								turn(SPEED, 90, LEFT_TURN);
								move (SPEED, 100);
								cur_row_pos += 2;
							}
							else{
								turn(SPEED, 90, RIGHT_TURN);
								move (SPEED, 50);
								pre_column_pos = CENTER_COL;
								cur_column_pos = LEFT_COL;
								turn(SPEED, 90, RIGHT_TURN);
								move (SPEED, 100);
								cur_row_pos += 2;
							}
						}
					}
				}
			}
			if (pre_column_pos == RIGHT_COL){
				if (wall() == 0){
					move(SPEED, 50);
					pre_column_pos = CENTER_COL;
					cur_column_pos = LEFT_COL;
					turn(SPEED, 90, RIGHT_TURN);
					move(SPEED, 100);
					cur_row_pos += 2;
				}
				if (wall() == 1){
					turn(SPEED, 90, RIGHT_TURN);
					if (wall() == 0){
						move(SPEED, 100);
						cur_row_pos += 2;
					}
					if (wall() == 1){
						turn(SPEED, 180, RIGHT_TURN);
						move(SPEED, 100);
						cur_row_pos -= 2; //RETOUR ARRIÈRE
						while (wall() == 0){
							move (SPEED, 100);
							cur_row_pos -=2;
						}
						if(wall() == 1){
							if (pre_column_pos == LEFT_COL){
								turn(SPEED, 90, LEFT_TURN);
								move (SPEED, 50);
								pre_column_pos = CENTER_COL;
								cur_column_pos = RIGHT_COL;
								turn(SPEED, 90, LEFT_TURN);
								move (SPEED, 100);
								cur_row_pos += 2;
							}
							else{
								turn(SPEED, 90, RIGHT_TURN);
								move (SPEED, 50);
								pre_column_pos = CENTER_COL;
								cur_column_pos = LEFT_COL;
								turn(SPEED, 90, RIGHT_TURN);
								move (SPEED, 100);
								cur_row_pos += 2;
							}
						}
					}
				}
			}
		}
		if (cur_column_pos == LEFT_COL){
			if (wall() == 0){
				move(SPEED, 100);
				cur_row_pos += 2;
			}
			if (wall() == 1){
				turn(SPEED, 90, RIGHT_TURN);
				move(SPEED, 50);
				pre_column_pos = LEFT_COL;
				cur_column_pos = CENTER_COL;
			}
		}
		if (cur_column_pos == RIGHT_COL){
			if (wall() == 0){
				move(SPEED, 100);
				cur_row_pos += 2;
			}
			if (wall() == 1){
				turn(SPEED, 90, LEFT_TURN);
				move(SPEED, 50);
				pre_column_pos = RIGHT_COL;
				cur_column_pos = CENTER_COL;
			}
		}
	}
}
