//Game of Life - Multithreaded and single threaded versions
//By Brennan Ho - 06/26/2018

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define ROWS 50
#define COLS 75

typedef struct {
	char alive;
	int liveNeighbors;
	int x;
	int y;
} Cell;

Cell game[ROWS][COLS];
Cell game_buffer[ROWS][COLS];
clock_t t;
int generation = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//Returns number of live neighbors to cell
int get_num_neighbors(Cell cell) {
	cell.liveNeighbors = 0;
	if (cell.x-1 >= 0)
		if (game[cell.x-1][cell.y].alive == '#')
			cell.liveNeighbors++;
	if (cell.x+1 < COLS)
		if (game[cell.x+1][cell.y].alive == '#')
			cell.liveNeighbors++;	
	if (cell.y-1 >= 0)
		if (game[cell.x][cell.y-1].alive == '#')
			cell.liveNeighbors++;
	if (cell.y+1 < ROWS)
		if (game[cell.x][cell.y+1].alive == '#')
			cell.liveNeighbors++;
	if (cell.x-1 >= 0 && cell.y-1 >= 0)
		if (game[cell.x-1][cell.y-1].alive == '#')
			cell.liveNeighbors++;
	if (cell.x-1 >= 0 && cell.y+1 < ROWS)
		if (game[cell.x-1][cell.y+1].alive == '#')
			cell.liveNeighbors++;
	if (cell.x+1 < COLS && cell.y+1 < ROWS)
		if (game[cell.x+1][cell.y+1].alive == '#')
			cell.liveNeighbors++;
	if (cell.x+1 < COLS && cell.y-1 >= 0)
		if (game[cell.x+1][cell.y-1].alive == '#')
			cell.liveNeighbors++;
	return cell.liveNeighbors;
}

void init_game(void) {
	srand(time(NULL));
	generation++;
	printf("\ngeneration: %d\n\n", generation);

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			game[i][j].liveNeighbors = get_num_neighbors(game[i][j]);
		}
	}

	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			int random = rand() % COLS;
			if (random < COLS/5)
				game[i][j].alive = '#';
			else
				game[i][j].alive = '-';
			game[i][j].x = i;
			game[i][j].y = j;
			printf("%c ", game[i][j].alive);
		}
		printf("\n");
	}
	memcpy(&game_buffer, &game, sizeof (Cell) * ROWS * COLS);
	generation++;
}

void single_threaded_game(void) {
	while (1) {

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				game[i][j].liveNeighbors = get_num_neighbors(game[i][j]);
			}
		}

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (game[i][j].alive == '#') {
					if (game[i][j].liveNeighbors < 2 || game[i][j].liveNeighbors > 3)
						game[i][j].alive = '-';
				} else { //cell is dead
					if (game[i][j].liveNeighbors == 3)
						game[i][j].alive = '#';
				}
			}
		}

		printf("\ngeneration: %d\n\n", generation);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				printf("%c ", game[i][j].alive);
			}
			printf("\n");
		}
		printf("\n");
		generation++;
		sleep(1);

	}

}

void* update_game(void* Nothing) {
	while (1) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				game[i][j].liveNeighbors = get_num_neighbors(game[i][j]);
			}
		}
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (game[i][j].alive == '#') {
					if (game[i][j].liveNeighbors < 2 || game[i][j].liveNeighbors > 3) {
						pthread_mutex_lock(&mutex);
						game_buffer[i][j].alive = '-';
						pthread_mutex_unlock(&mutex);
					}
				} else { //cell is dead
					if (game[i][j].liveNeighbors == 3) {
						pthread_mutex_lock(&mutex);
						game_buffer[i][j].alive = '#';
						pthread_mutex_unlock(&mutex);
					}
				}
			}
		}
		pthread_mutex_lock(&mutex);
		memcpy(&game, &game_buffer, (sizeof(Cell)) * ROWS * COLS);
		generation++;
		pthread_mutex_unlock(&mutex);
	}
}

void* display_game(void* Nothing) {
	while (1) {
		pthread_mutex_lock(&mutex);
		printf("\ngeneration: %d, gen/sec %f\n\n", generation, generation/((double)(clock()-t)/CLOCKS_PER_SEC));
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				printf("%c ", game[i][j].alive);
			}
			printf("\n");
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void threaded_game(void) {
	pthread_t update_thread, display_thread;
	t = clock();
	pthread_create(&update_thread, NULL, update_game, NULL);
	pthread_create(&display_thread, NULL, display_game, NULL);
	pthread_join(update_thread, NULL);
	pthread_join(display_thread, NULL);
}

int main(void) {
	init_game();
	threaded_game();
	//single_threaded_game();

	return 0;
}