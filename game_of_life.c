/*
 * A simple implementation of John Conway's Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GRID_SIZE 32

void render_env(char grid[GRID_SIZE][GRID_SIZE]) {
    system("clear");
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[x][y] == 1) {
                printf("■ ");
            } else {
                printf("´ ");
            }
        }
        printf("\n");
    }
}

void step(char grid[GRID_SIZE][GRID_SIZE]) {
    char grid_next_step[GRID_SIZE][GRID_SIZE];

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            // populating the neighbors array with the current cell's neighbors
            char neighbors[8] = {
                x != 0 && y != 0 ? grid[x-1][y-1] : 0,
                y != 0 ? grid[x][y-1] : 0,
                y != GRID_SIZE-1 ? grid[x][y+1] : 0,
                x != 0 ? grid[x-1][y] : 0,
                x != GRID_SIZE-1 ? grid[x+1][y] : 0,
                x != GRID_SIZE-1 && y != GRID_SIZE-1 ? grid[x+1][y+1] : 0,
                x != GRID_SIZE-1 && y != 0 ? grid[x+1][y-1] : 0,
                x != 0 && y != GRID_SIZE-1 ? grid[x-1][y+1] : 0,
            };

            int alive_neighbors_cnt = 0;
            for (int n = 0; n < 8; ++n) {
                if (neighbors[n] == 1)
                    alive_neighbors_cnt++;
            }

            // checking whether the cell will live or die according to the rules
            if (grid[x][y] == 1) {
                if (alive_neighbors_cnt <= 1 || alive_neighbors_cnt >= 4) {
                    grid_next_step[x][y] = 0;
                } else {
                    grid_next_step[x][y] = 1;
                }
            } else {
                if (alive_neighbors_cnt == 3) {
                    grid_next_step[x][y] = 1;
                } else {
                    grid_next_step[x][y] = 0;
                }
            }   
        }
    }

    // setting the grid to its updated state
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            grid[x][y] = grid_next_step[x][y];
        }
    }
}

int main() {
    char grid[GRID_SIZE][GRID_SIZE];

    // populating the grid, setting a random initial state (0 = no life; 1 = life)
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            int val = rand()%10 > 3 ? 1 : 0;
            grid[x][y] = val;
        }
    }

    // "game loop"
    while (1) {
        render_env(grid);
        step(grid);
        usleep(100000);
    }
}