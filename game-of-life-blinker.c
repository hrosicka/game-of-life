/*******************************************************************
 * Conway's Game of Life - Blinker Oscillator Simulation (Windows)
 * 
 * Compile: gcc game-of-life-blinker.c -o game-of-life-blinker
 * 
 * Author: hrosicka
 * Description:
 *   This program simulates Conway's Game of Life in the console,
 *   using a fixed-size grid. It supports wrap-around edges and
 *   features the classic BLINKER oscillator pattern. The simulation
 *   runs in an infinite loop, updating the grid and displaying
 *   each generation.
 * 
 * Rules:
 *   1. Any live cell with fewer than two live neighbors dies.
 *   2. Any live cell with two or three live neighbors lives.
 *   3. Any live cell with more than three live neighbors dies.
 *   4. Any dead cell with exactly three live neighbors becomes alive.
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For Sleep function to add delay between generations

#define WIDTH 15   // Number of columns in the grid
#define HEIGHT 7   // Number of rows in the grid

/**
 * @brief Counts the number of live neighbors for a given cell.
 * 
 * The function uses wrap-around logic (toroidal array) so that 
 * the grid edges are connected. This ensures continuity in the simulation.
 * 
 * @param grid The current game grid.
 * @param x The row index of the cell.
 * @param y The column index of the cell.
 * @return int The total number of living neighbors.
 */
int count_live_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Skip the current cell itself
            if (i == 0 && j == 0) continue;

            // Calculate neighbor positions with wrap-around
            int neighbor_x = (x + i + HEIGHT) % HEIGHT;
            int neighbor_y = (y + j + WIDTH) % WIDTH;

            if (grid[neighbor_x][neighbor_y] == 1) {
                count++;
            }
        }
    }
    return count;
}

/**
 * @brief Prints the current grid to the console.
 * 
 * Uses 'o' to represent live cells and spaces for dead cells.
 * The screen is cleared before each print for a smooth animation effect.
 * 
 * @param grid The grid to print.
 */
void print_grid(int grid[HEIGHT][WIDTH]) {
    system("cls"); // Clear the screen (Windows-specific)
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == 1) {
                printf("o ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

int main() {
    // Grids for current and next generation
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};

    /** 
     * @section Initialization
     * Set up the BLINKER pattern in the grid center.
     * The Blinker is a simple period-2 oscillator.
     */

    // BLINKER pattern (vertical line)
    current_grid[3][7] = 1;
    current_grid[3][8] = 1;
    current_grid[3][9] = 1;

    /**
     * @section Main Simulation Loop
     * The loop performs the following steps:
     *  1. Display the current grid.
     *  2. Compute the next generation based on the Game of Life rules.
     *  3. Copy the next generation into the current grid.
     *  4. Wait for 0.5 second before next iteration.
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
                        next_grid[i][j] = 1; // Becomes alive due to reproduction
                    } else {
                        next_grid[i][j] = 0; // Remains dead
                    }
                }
            }
        }

        // Copy next generation to current grid
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                current_grid[i][j] = next_grid[i][j];
            }
        }

        Sleep(5); // delay for visualization
    }

    return 0;
}