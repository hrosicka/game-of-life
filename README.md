# Game of Life — Cellular Automata Playground

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Repo Size](https://img.shields.io/github/repo-size/hrosicka/game-of-life)
![Last Commit](https://img.shields.io/github/last-commit/hrosicka/game-of-life)
![Issues](https://img.shields.io/github/issues/hrosicka/game-of-life)
![Stars](https://img.shields.io/github/stars/hrosicka/game-of-life)

Welcome! This repository contains several interactive C implementations of **Conway’s Game of Life**. Study, experiment, and enjoy the fascinating emergence of complex behavior from simple rules.

---

## 🧭 Table of Contents
* [🧬 What is the Game of Life?](#-what-is-the-game-of-life)
* [🧩 Implemented Patterns & Features]((#pattern-link))
* [🚀 How to Run](#-how-to-run)
  * [Blinker Oscillator](#blinker-oscillator)
  * [Toad Oscillator](#toad-oscillator)
  * [Glider](#glider)
  * [Lightweight Spaceship (LWSS)](#lightweight-spaceship-lwss)


Lightweight Spaceship (LWSS)
Gosper Glider Gun
Pulsar Oscillator
Beacon
📁 Project Structure
✨ Why Use This Project?
💡 Possible Improvements
👩‍💻 Author
📄 License

---

## 🧬 What is the Game of Life?

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a cellular automaton played on a grid of cells, each of which is either alive or dead. At each time step ("generation"), cells update state according to their neighbors:

- **Survival:** A live cell with 2 or 3 live neighbors survives.
- **Death:** A live cell with fewer than 2 or more than 3 live neighbors dies.
- **Birth:** A dead cell with exactly 3 live neighbors becomes alive.

No players, just rules—and surprisingly rich behavior.

---

<a name="pattern-link"></a>
## 🧩 Implemented Patterns & Features

This repository provides ready-to-run simulations for several classic Game of Life patterns:

- **Blinker:** A simple period-2 oscillator.
- **Toad:** Another period-2 oscillator.
- **Glider:** The famous moving pattern.
- **Lightweight Spaceship (LWSS):** A mobile pattern that travels diagonally.
- **Gosper Glider Gun:** Emits endless gliders—demonstrating infinite growth.
- **Pulsar:** A period-3 oscillator.
- **Beacon:** One of the best-known and most frequently occurring simple patterns. Beacon alternates between only two different shapes.
- **Custom Patterns:** Easily experiment with your own initial states by editing the source.

All simulations feature animated terminal output (for Windows), wrap-around grid edges, and are well-commented for learning and modification.

---

## 🚀 How to Run

> **Note:** All programs are written in C for Windows (require `windows.h`). To compile and run, use GCC:

### Blinker Oscillator
```bash
gcc game-of-life-blinker.c -o game-of-life-blinker
./game-of-life-blinker
```

### Toad Oscillator
```bash
gcc game-of-life-toad.c -o game-of-life-toad
./game-of-life-toad
```

### Glider
```bash
gcc game-of-life-glider.c -o game-of-life-glider
./game-of-life-glider
```

### Lightweight Spaceship (LWSS)
```bash
gcc game-of-life-lwss.c -o game-of-life-lwss
./game-of-life-lwss
```

### Gosper Glider Gun
```bash
gcc game-of-life-gun.c -o game-of-life-gun -lm
./game-of-life-gun
```

### Pulsar Oscillator
```bash
gcc game-of-life-pulsar.c -o game-of-life-pulsar
./game-of-life-pulsar
```

## Beacon
```bash
 gcc game-of-life-beacon.c -o game-of-life-beacon
./game-of-life-beacon
```

---

## 📁 Project Structure

- **game-of-life-blinker.c** — Blinker oscillator
- **game-of-life-toad.c** — Toad oscillator
- **game-of-life-glider.c** — Glider
- **game-of-life-lwss.c** — Lightweight Spaceship
- **game-of-life-gun.c** — Gosper Glider Gun
- **game-of-life-pulsar.c** — Pulsar oscillator
- **game-of-life-beacon.c** - Beacon
- **LICENSE** — MIT License

---

## ✨ Why Use This Project?

- Visualize how simple rules lead to complex, emergent behavior.
- Study classic cellular automata patterns.
- Source code is beginner-friendly and well-commented for self-study.
- Quick experimentation: modify source to try your own patterns.

---

## 💡 Possible Improvements

- Add support for Linux/macOS (replace `windows.h` functionality).
- Load custom starting states from text files.
- Build a graphical interface (e.g., with SDL).
- More patterns and user interaction.

---

## 👩‍💻 Author

Repository maintained by [Hanka Robovska](https://github.com/hrosicka).

---

## 📄 License

Released under the MIT License—use, modify, and share freely!
