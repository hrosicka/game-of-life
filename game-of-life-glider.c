// gcc game-of-life.c -o game-of-life
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For the Sleep function

#define WIDTH 30
#define HEIGHT 15

// Function to count living neighbors
int count_live_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            // Handle wrap-around edges
            int neighbor_x = (x + i + HEIGHT) % HEIGHT;
            int neighbor_y = (y + j + WIDTH) % WIDTH;

            if (grid[neighbor_x][neighbor_y] == 1) {
                count++;
            }
        }
    }
    return count;
}

// Function to print the grid to the console
void print_grid(int grid[HEIGHT][WIDTH]) {
    system("cls"); // Clear the screen (for Windows)
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == 1) {
                printf("o ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    int current_grid[HEIGHT][WIDTH] = {0};
    int next_grid[HEIGHT][WIDTH] = {0};

    // Initialization: Creating a GLIDER1 pattern
    current_grid[1][2] = 1;
    current_grid[2][3] = 1;
    current_grid[3][1] = 1;
    current_grid[3][2] = 1;
    current_grid[3][3] = 1;

    // Initialization: Creating a GLIDER2 pattern
    current_grid[5][5] = 1;
    current_grid[6][6] = 1;
    current_grid[7][4] = 1;
    current_grid[7][5] = 1;
    current_grid[7][6] = 1;


    while (1) {
        print_grid(current_grid);
        
        // Process the next generation
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int neighbors = count_live_neighbors(current_grid, i, j);

                // The rules of the game
                if (current_grid[i][j] == 1) { // Live cell
                    if (neighbors < 2 || neighbors > 3) {
                        next_grid[i][j] = 0; // Dies
                    } else {
                        next_grid[i][j] = 1; // Survives
                    }
                } else { // Dead cell
                    if (neighbors == 3) {
                        next_grid[i][j] = 1; // Becomes alive
                    } else {
                        next_grid[i][j] = 0; // Stays dead
                    }
                }
            }
        }

        // Copy the next grid to the current one
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                current_grid[i][j] = next_grid[i][j];
            }
        }

        Sleep(1000); // 1-second delay (Note: you changed this to 1000, which is 1 second)
    }

    return 0;
}