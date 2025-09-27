/*******************************************************************
 * Conway's Game of Life - Pulsar Oscillator Simulation (Windows)
 * 
 * Compile: gcc pulsar.c -o pulsar
 * 
 * Author: hrosicka
 * Description:
 *   This program simulates Conway's Game of Life in the console,
 *   displaying the evolution of the "Pulsar" oscillator pattern.
 *   The simulation runs on a large grid and updates each generation
 *   with a short delay for smooth visualization.
 * 
 * Rules:
 *   1. Any live cell with fewer than two live neighbors dies.
 *   2. Any live cell with two or three live neighbors lives.
 *   3. Any live cell with more than three live neighbors dies.
 *   4. Any dead cell with exactly three live neighbors becomes alive.
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // For Sleep and system("cls") on Windows

#define WIDTH 60     // Number of columns in the grid
#define HEIGHT 30     // Number of rows in the grid
#define DELAY 0       // Delay in milliseconds for each generation

/**
 * @brief Counts the number of live neighbors for a given cell.
 * 
 * The function checks all adjacent cells (excluding itself) within
 * the grid bounds to determine the number of living neighbors.
 * 
 * @param grid The current grid.
 * @param x The row index of the cell.
 * @param y The column index of the cell.
 * @return int The total number of living neighbors.
 */
int count_live_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Skip the cell itself
            if (i == 0 && j == 0) continue;

            int neighbor_x = x + i;
            int neighbor_y = y + j;

            // Check bounds
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
 * @brief Prints the current grid to the console.
 * 
 * Live cells are displayed as 'X', dead cells as space.
 * The console is cleared before each print for smooth animation.
 * 
 * @param grid The grid to print.
 */
void print_grid(int grid[HEIGHT][WIDTH]) {
    system("cls"); // Clear the console (Windows-specific)

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", grid[i][j] == 1 ? 'X' : ' ');
        }
        printf("\n");
    }
}

/**
 * @brief Places a given pattern onto the grid at a specified location.
 * 
 * The function iterates over the pattern array, offsetting each cell
 * by start_x and start_y, and sets the cell to alive if within bounds.
 * 
 * @param grid The grid to modify.
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
    // Initialize grids for current and next generation
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};
    
    /**
     * @section Pulsar Pattern
     * The pulsar is a classic oscillator in Conway's Game of Life,
     * with a period of 3 generations. The pattern is defined as a
     * set of coordinate offsets, placed in the grid at (30, 60).
     */
    const int pulsar_pattern[][2] = {
        {1, 3}, {1, 4}, {1, 5},
        {1, 9}, {1, 10}, {1, 11},
        {3, 1}, {3, 6}, {3, 8}, {3, 13},
        {4, 1}, {4, 6}, {4, 8}, {4, 13},
        {5, 1}, {5, 6}, {5, 8}, {5, 13},
        {6, 3}, {6, 4}, {6, 5},
        {6, 9}, {6, 10}, {6, 11},
        {8, 3}, {8, 4}, {8, 5},
        {8, 9}, {8, 10}, {8, 11},
        {9, 1}, {9, 6}, {9, 8}, {9, 13},
        {10, 1}, {10, 6}, {10, 8}, {10, 13},
        {11, 1}, {11, 6}, {11, 8}, {11, 13},
        {13, 3}, {13, 4}, {13, 5},
        {13, 9}, {13, 10}, {13, 11},
    };
    
    // Place the Pulsar pattern on the grid
    place_pattern(current_grid, pulsar_pattern, sizeof(pulsar_pattern) / sizeof(pulsar_pattern[0]), 10, 20);
    
    /**
     * @section Main Simulation Loop
     * The loop performs:
     *  1. Display the current grid.
     *  2. Compute the next generation by applying the Game of Life rules.
     *  3. Copy the next generation to the current grid.
     *  4. Wait for DELAY milliseconds before the next update.
     */
    while (1) {
        print_grid(current_grid);

        // Calculate next generation
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int neighbors = count_live_neighbors(current_grid, i, j);

                // Apply Conway's rules
                if (current_grid[i][j] == 1) { // Cell is alive
                    if (neighbors < 2 || neighbors > 3) {
                        next_grid[i][j] = 0; // Dies due to under/overpopulation
                    } else {
                        next_grid[i][j] = 1; // Continues living
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

        // Update the current grid for the next generation
        memcpy(current_grid, next_grid, sizeof(current_grid));
        Sleep(DELAY); // Visualization delay
    }
    return 0;
}