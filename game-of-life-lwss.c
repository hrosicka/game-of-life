/*******************************************************************
 * Conway's Game of Life - Lightweight Spaceship (LWSS) Simulation
 * 
 * Compile: gcc game-of-life-lwss.c -o game-of-life-lwss
 * 
 * Author: Hana Robovska
 * Description:
 *   This program simulates Conway's Game of Life in the console,
 *   featuring the well-known "Lightweight Spaceship" (LWSS) pattern.
 *   LWSS is a small, mobile pattern that moves diagonally across the grid.
 *   The simulation uses a fixed-size grid and updates each generation
 *   with a delay for smooth visualization.
 * 
 * Game of Life Rules:
 *   1. Any live cell with fewer than two live neighbors dies.
 *   2. Any live cell with two or three live neighbors lives.
 *   3. Any live cell with more than three live neighbors dies.
 *   4. Any dead cell with exactly three live neighbors becomes alive.
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // For Sleep and system("cls") on Windows

#define WIDTH 40    // Number of columns in the grid
#define HEIGHT 20   // Number of rows in the grid
#define DELAY 1   // Delay in milliseconds for each generation

/**
 * @brief Counts the number of living neighbors for a given cell.
 * 
 * Iterates over the surrounding 3x3 neighborhood (excluding the
 * cell itself) to determine the number of living neighbors.
 * Neighbor coordinates outside the grid are ignored.
 * 
 * @param grid The 2D array representing the game grid.
 * @param x The row index of the cell.
 * @param y The column index of the cell.
 * @return int The number of living neighbors (0-8).
 */
int count_live_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself

            int neighbor_x = x + i;
            int neighbor_y = y + j;

            // Only count neighbors within grid bounds
            if (neighbor_x >= 0 && neighbor_x < HEIGHT &&
                neighbor_y >= 0 && neighbor_y < WIDTH) {
                if (grid[neighbor_x][neighbor_y] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 * @brief Clears the console and prints the current state of the grid.
 * 
 * Uses 'X' to represent live cells and space for dead cells.
 * The function clears the screen before each print for smooth animation.
 * 
 * @param grid The 2D array representing the game grid.
 */
void print_grid(int grid[HEIGHT][WIDTH]) {
    system("cls"); // Clear the console (Windows-specific)

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", grid[i][j] == 1 ? 'O' : ' ');
        }
        printf("\n");
    }
}

/**
 * @brief Places a given pattern onto the grid at a specified starting position.
 * 
 * Iterates over the pattern array, offsetting each cell by start_x and start_y,
 * and sets the cell as alive if the coordinates are within bounds.
 * 
 * @param grid The 2D array representing the game grid.
 * @param pattern Array of cell offsets representing the pattern.
 * @param size Number of cells in the pattern array.
 * @param start_x Starting row for the pattern.
 * @param start_y Starting column for the pattern.
 */
void place_pattern(int grid[HEIGHT][WIDTH], const int pattern[][2], int size, int start_x, int start_y) {
    for (int i = 0; i < size; i++) {
        int x = start_x + pattern[i][0];
        int y = start_y + pattern[i][1];

        if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
            grid[x][y] = 1;
        }
    }
}

int main() {
    // Two grids: one for the current generation, one for the next generation
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};
    
    /**
     * @section Pattern Initialization
     * The Lightweight Spaceship (LWSS) is a mobile pattern that moves
     * diagonally across the grid. This pattern is defined as a set
     * of coordinate offsets relative to its starting position.
     */
    const int lwss_pattern[][2] = {
        {0,1}, {0,4},
        {1,0}, {2,0}, {2,4},
        {3,0}, {3,1}, {3,2}, {3,3}
    };
    
    // Place the LWSS pattern near the top-left of the grid (row 2, col 2)
    place_pattern(current_grid, lwss_pattern, sizeof(lwss_pattern) / sizeof(lwss_pattern[0]), 15, 35);
    
    /**
     * @section Main Simulation Loop
     * The loop performs the following steps:
     *  1. Display the current grid.
     *  2. Compute the next generation according to the Game of Life rules.
     *  3. Copy the next generation into the current grid.
     *  4. Wait for DELAY milliseconds before the next update.
     */
    while (1) {
        print_grid(current_grid);

        // Compute next generation
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int neighbors = count_live_neighbors(current_grid, i, j);

                // Apply Conway's rules
                if (current_grid[i][j] == 1) { // Cell is alive
                    if (neighbors < 2 || neighbors > 3) {
                        next_grid[i][j] = 0; // Dies: under/overpopulation
                    } else {
                        next_grid[i][j] = 1; // Survives
                    }
                } else { // Cell is dead
                    if (neighbors == 3) {
                        next_grid[i][j] = 1; // Becomes alive (reproduction)
                    } else {
                        next_grid[i][j] = 0; // Remains dead
                    }
                }
            }
        }

        // Copy next generation to current grid
        memcpy(current_grid, next_grid, sizeof(current_grid));
        Sleep(DELAY); // Visualization delay
    }

    return 0;
}