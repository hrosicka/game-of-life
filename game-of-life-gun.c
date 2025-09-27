/*******************************************************************
 * Conway's Game of Life - Gosper Glider Gun Simulation (Windows)
 * 
 * Compile: gcc game-of-life-gun.c -o game-of-life-gun -lm
 * 
 * Author: hrosicka
 * Description:
 *   This program simulates Conway's Game of Life in the console,
 *   presenting the famous "Gosper Glider Gun" pattern. The glider
 *   gun continuously emits moving "gliders" across the grid, 
 *   demonstrating emergent behavior in cellular automata.
 * 
 * Simulation Details:
 *   - Runs on a fixed-size grid.
 *   - Animation uses a short delay for visualization.
 *   - The gun pattern is placed near the top-left of the grid.
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

#define WIDTH 100    // Number of columns in the grid
#define HEIGHT 40    // Number of rows in the grid
#define DELAY 1     // Delay in milliseconds for each generation

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
            printf("%c", grid[i][j] == 1 ? 'X' : ' ');
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
     * The Gosper Glider Gun is a well-known pattern that generates 
     * an endless stream of gliders. The pattern is defined as a set
     * of coordinate offsets relative to its starting position.
     */
    const int glider_gun[][2] = {
        {1, 25}, {2, 23}, {2, 25},
        {3, 13}, {3, 14}, {3, 21}, {3, 22}, {3, 35}, {3, 36},
        {4, 12}, {4, 16}, {4, 21}, {4, 22}, {4, 35}, {4, 36},
        {5, 1}, {5, 2}, {5, 11}, {5, 17}, {5, 21}, {5, 22},
        {6, 1}, {6, 2}, {6, 11}, {6, 15}, {6, 17}, {6, 18}, {6, 23}, {6, 25},
        {7, 11}, {7, 17}, {7, 25},
        {8, 12}, {8, 16},
        {9, 13}, {9, 14}
    };
    
    // Place the Glider Gun pattern onto the initial grid at position (5, 5)
    place_pattern(current_grid, glider_gun, sizeof(glider_gun) / sizeof(glider_gun[0]), 5, 5);
    
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