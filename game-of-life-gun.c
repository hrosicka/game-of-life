// Compile with: gcc game-of-life-gun.c -o game-of-life-gun -lm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // For Sleep and system("cls") on Windows

// Define grid dimensions and simulation speed
#define WIDTH 100
#define HEIGHT 40
#define DELAY 50 // Delay in milliseconds for each generation

/**
 * @brief Counts the number of living neighbors for a given cell.
 * @param grid The 2D array representing the game grid.
 * @param x The row index of the cell.
 * @param y The column index of the cell.
 * @return The number of living neighbors (0-8).
 */
int count_live_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    // Iterate over the 3x3 neighborhood centered on the cell (x, y)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Skip the cell itself
            if (i == 0 && j == 0) continue;

            // Calculate the neighbor's coordinates
            int neighbor_x = x + i;
            int neighbor_y = y + j;

            // Check if the neighbor is within the grid boundaries
            if (neighbor_x >= 0 && neighbor_x < HEIGHT &&
                neighbor_y >= 0 && neighbor_y < WIDTH) {
                
                // If the neighbor is alive, increment the count
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
 * @param grid The 2D array representing the game grid.
 */
void print_grid(int grid[HEIGHT][WIDTH]) {
    system("cls"); // Clear the console on Windows

    // Print each cell of the grid
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Use 'X' for living cells and a space for dead cells
            printf("%c", grid[i][j] == 1 ? 'X' : ' ');
        }
        printf("\n");
    }
}

/**
 * @brief Places a given pattern onto the grid at a specified starting position.
 * @param grid The 2D array representing the game grid.
 * @param pattern A 2D array of relative coordinates for the pattern's live cells.
 * @param size The number of cells in the pattern.
 * @param start_x The starting row for the pattern.
 * @param start_y The starting column for the pattern.
 */
void place_pattern(int grid[HEIGHT][WIDTH], const int pattern[][2], int size, int start_x, int start_y) {
    for (int i = 0; i < size; i++) {
        // Calculate absolute coordinates
        int x = start_x + pattern[i][0];
        int y = start_y + pattern[i][1];

        // Place the live cell if it's within the grid boundaries
        if (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH) {
            grid[x][y] = 1;
        }
    }
}

int main() {
    // Initialize two grids: one for the current generation, one for the next
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};
    
    // --- Game of Life Patterns ---
    
    // Gosper's Glider Gun pattern
    // This pattern produces a continuous stream of "gliders"
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
    
    // Place the pattern on the initial grid
    place_pattern(current_grid, glider_gun, sizeof(glider_gun) / sizeof(glider_gun[0]), 5, 5);
    
    // Main simulation loop
    while (1) {
        print_grid(current_grid);
        
        // Calculate the next generation based on Conway's rules
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int neighbors = count_live_neighbors(current_grid, i, j);

                if (current_grid[i][j] == 1) { // Rule for live cells
                    if (neighbors < 2 || neighbors > 3) {
                        next_grid[i][j] = 0; // Dies due to underpopulation or overpopulation
                    } else {
                        next_grid[i][j] = 1; // Survives
                    }
                } else { // Rule for dead cells
                    if (neighbors == 3) {
                        next_grid[i][j] = 1; // Becomes alive due to reproduction
                    } else {
                        next_grid[i][j] = 0; // Stays dead
                    }
                }
            }
        }

        // Copy the state from `next_grid` to `current_grid` for the next iteration
        memcpy(current_grid, next_grid, sizeof(current_grid));

        Sleep(DELAY); // Pause to control the simulation speed
    }

    return 0;
}