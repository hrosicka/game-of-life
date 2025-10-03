/*******************************************************************
 * Conway's Game of Life - Beacon Oscillator Simulation
 * * Compile: gcc game-of-life-beacon.c -o game-of-life-beacon
 * * Author: Hana Robovska
 * Description:
 * This program simulates Conway's Game of Life in the console,
 * featuring the well-known "Beacon" pattern.
 * The Beacon is a period-2 oscillator, alternating between two states.
 * The simulation uses a fixed-size grid and updates each generation
 * with a delay for smooth visualization.
 * * Game of Life Rules:
 * 1. Any live cell with fewer than two live neighbors dies (underpopulation).
 * 2. Any live cell with two or three live neighbors lives on (survival).
 * 3. Any live cell with more than three live neighbors dies (overpopulation).
 * 4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // For Sleep and system("cls") on Windows

#define WIDTH 30    // Number of columns in the grid
#define HEIGHT 10   // Number of rows in the grid
#define DELAY 500  // Delay in milliseconds for each generation (Increased for Beacon visibility)

/**
 * @brief Counts the number of living neighbors for a given cell.
 * * Iterates over the surrounding 3x3 neighborhood (excluding the
 * cell itself) to determine the number of living neighbors.
 * Neighbor coordinates outside the grid are ignored.
 * * @param grid The 2D array representing the game grid.
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
 * * Uses 'O' to represent live cells and space for dead cells.
 * The function clears the screen before each print for smooth animation.
 * * @param grid The 2D array representing the game grid.
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
 * * Iterates over the pattern array, offsetting each cell by start_x and start_y,
 * and sets the cell as alive if the coordinates are within bounds.
 * * @param grid The 2D array representing the game grid.
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

// Beacon Pattern Simulation

int main() {
    // Two grids: one for the current generation, one for the next generation
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};
    
    /**
     * @section Pattern Initialization
     * The **Beacon** is a period-2 oscillator. It consists of two 2x2 blocks
     * that alternately connect and disconnect every generation.
     * This pattern is defined as a set of coordinate offsets relative
     * to its starting position.
     */
    const int beacon_pattern[][2] = {
        {0,0},{0,1},{1,0},{1,1}, // Top-left block
        {2,2},{2,3},{3,2},{3,3}  // Bottom-right block
    };
    
    // Place the Beacon pattern near the center of the grid.
    // The starting position (3, 3) is a good spot for a small grid.
    place_pattern(current_grid, beacon_pattern, sizeof(beacon_pattern) / sizeof(beacon_pattern[0]), 3, 3);
    
    /**
     * @section Main Simulation Loop
     * The loop performs the following steps:
     * 1. Display the current grid.
     * 2. Compute the next generation according to the Game of Life rules.
     * 3. Copy the next generation into the current grid.
     * 4. Wait for DELAY milliseconds before the next update.
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