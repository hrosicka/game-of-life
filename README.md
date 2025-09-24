# Game of Life — Welcome to the World of Cellular Automata

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Repo Size](https://img.shields.io/github/repo-size/hrosicka/game-of-life)
![Last Commit](https://img.shields.io/github/last-commit/hrosicka/game-of-life)
![Issues](https://img.shields.io/github/issues/hrosicka/game-of-life)
![Stars](https://img.shields.io/github/stars/hrosicka/game-of-life)

Welcome to this fun and interactive project — an implementation of the famous **Conway's Game of Life** in C! This repository allows you to dive into the fascinating world of cellular automata and observe how complex patterns emerge from simple rules.

---

## 🧬 What is the Game of Life?

[Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a simulation on a 2D grid, where each cell can be alive or dead. In each generation, the state of every cell is determined by a few simple rules based on the number of living neighbors. There are no players — just rules, and surprisingly rich behavior.

**What you'll find in this repository:**
- Simulations of basic patterns (toad, glider, etc.)
- Demonstrations of more advanced structures like the **Gosper’s Glider Gun**
- Terminal animation (for Windows) and an easy way to experiment with your own patterns

---

## ⚙️ How does it work?

- Each cell has eight neighbors.
- On each step (generation), the following rules are applied to every cell:
  1. **Survival:** Any live cell with two or three live neighbors survives.
  2. **Death:** Any live cell with fewer than two or more than three live neighbors dies (underpopulation or overpopulation).
  3. **Birth:** Any dead cell with exactly three live neighbors becomes a live cell.

---

## 🚀 How to run

> **Note:** The program is written in C and intended for Windows (uses `windows.h`).

### Basic Life (oscillators, toad, etc.)
```bash
gcc game-of-life.c -o game-of-life
./game-of-life
```

### Glider patterns
```bash
gcc game-of-life-glider.c -o game-of-life-glider
./game-of-life-glider
```

### Glider Gun (infinite stream of gliders!)
```bash
gcc game-of-life-gun.c -o game-of-life-gun -lm
./game-of-life-gun
```

---

## 🧩 Project Structure

- **game-of-life.c** — Basic implementation with several simple patterns
- **game-of-life-glider.c** — Simulation of the legendary "glider" pattern
- **game-of-life-gun.c** — Simulation of the "Gosper’s Glider Gun" which generates endless gliders
- **LICENSE** — MIT license, feel free to use and improve!

---

## ✨ Why is this interesting?

- Witness how complex patterns and behaviors arise from simple rules
- Perfect for demonstrating programming, algorithms, and automata theory
- Well-commented source code, ideal for self-study and experiments

---

## 💡 Ideas for improvement

- Add support for other platforms (Linux/macOS)
- Allow loading custom initial states from a text file
- Build a graphical interface (e.g., with SDL or another graphics library)

---

## 👩‍💻 Author

Repository maintained by [Hanka Robovska](https://github.com/hrosicka).

---

## 📄 License

This project is released under the MIT License — use it as you wish!
