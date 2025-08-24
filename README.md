# Conway's Game of Life

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Repo Size](https://img.shields.io/github/repo-size/hrosicka/game-of-life)
![Last Commit](https://img.shields.io/github/last-commit/hrosicka/game-of-life)
![Issues](https://img.shields.io/github/issues/hrosicka/game-of-life)
![Stars](https://img.shields.io/github/stars/hrosicka/game-of-life)

- Conway's Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970.
- It isn't a game in the traditional sense, as there are no players. Instead, it's a simulation governed by a simple set of rules.
---

## How the Game Works
- The game takes place on a two-dimensional grid where each cell can be in one of two states: alive (represented by 'o') or dead (represented by '.'). 
- During each generation, the state of a cell changes based on the state of its eight neighbors.
---

## The Rules
The following rules apply to every cell at each generation:

1. A live cell with fewer than two live neighbors dies (from underpopulation).
2. A live cell with two or three live neighbors survives to the next generation.
3. A live cell with more than three live neighbors dies (from overcrowding).
4. A dead cell with exactly three live neighbors becomes alive (birth).
---

## Code and How to Run
This project is an implementation of the Game of Life in C.

```bash
# Compile the program
gcc game-of-life.c -o game-of-life

# Run the program
./game-of-life
```
