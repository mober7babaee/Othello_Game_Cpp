# ♟️ Othello (Reversi) Command-Line Game

This repository contains the source code for a complete **command-line implementation** of the classic two-player strategy game **Othello (Reversi)**.

Developed in **C++20** as an advanced programming final project, this implementation emphasizes **object-oriented design**, **modular architecture**, and **robust game logic**.

---

## ✨ Project Highlights

- **Modular OOP Design** → Structured with distinct classes (`Game`, `Board`, `Player`) to ensure separation of concerns and maintainability.  
- **Complete Game Logic** → Implements full Othello rules including eight-directional flipping, move validation, and end-game detection.  
- **Persistence** → Includes save/load functionality to store and restore game states from disk using a readable text file format.  
- **Time Travel (Undo/Redo)** → Implements board state history tracking using history stacks (`boardHistory`, `redoBoardHistory`) to support both undo and redo features.  
- **Command-Line Interface** → User-friendly text-based input system for interacting directly with the game using simple commands.

---

## 📐 Architecture and Design

The project follows a **top-down, object-oriented** design using dedicated classes to manage complexity and maintain clear separation of responsibilities.

### 1. Board Class (`board.hpp`, `board.cpp`)
The **engine** of the game — responsible for managing the grid state and executing Othello rules.

- **Internal State:** Uses `std::vector<std::vector<char>>` to represent the board, storing `'B'`, `'W'`, or `'.'` (empty).  
- **Core Logic:** Implements flipping algorithms across eight directions (horizontal, vertical, and diagonals) via `isValidFlip` and `flipPieces`.  
- **Validation:** Checks valid coordinates and possible moves using `getValidMoves`.

### 2. Player Class (`game.hpp`)
Defines the entities participating in the game.

- **Responsibility:** Stores the piece color (`'B'` or `'W'`) and manages player turn logic.

### 3. Game Class (`game.hpp`, `game.cpp`)
Acts as the **controller and command processor**, managing lifecycle and history.

- **Game Flow:** Encapsulates the `Board` object and manages the `currentPlayer` to alternate turns and check for game-end conditions.  
- **Command Handling:** Parses user input using `std::stringstream` to extract commands and arguments.  
- **History System:** Maintains `boardHistory` and `redoBoardHistory` stacks to implement Undo/Redo functionality.  
- **Persistence:** Handles file I/O (`std::fstream`) to save and load board states and turn data.

---

## 🛠️ Build and Usage

The project is built using a **standard Makefile** and a C++20-compatible compiler (e.g., `g++`).

### 🧩 Compilation
```bash
# Compile all source files into the 'othello' executable
make
```
### 🧹 Clean Up
# Command to remove the executable and temporary object files (.o)
```bash 
make clean
```
## 🎮 Game Commands

Once compiled, run the executable and use one of the following commands to play the game:

| **Command** | **Usage Example** | **Description** |
|--------------|------------------|-----------------|
| `new` | `new` | Starts a new game, initializing the board and clearing the move history. |
| `place` | `place D6` | Attempts to place the current player's piece at the specified coordinate (Column Letter, Row Number). |
| `save` | `save match_1.oth` | Saves the current board state and player turn to a text file. |
| `load` | `load match_1.oth` | Loads a saved game state from the specified file. |
| `undo` | `undo` | Reverts the game to the previous move by popping the last state from history. |
| `redo` | `redo` | Reapplies the most recently undone move (Bonus feature). |
| `exit` | `exit` | Exits the program cleanly. |


## 🧱 Error Handling & Robustness

- Robust error handling ensures smooth user experience and stability.

- Invalid Input: Detects incorrect command formats or unknown commands.

- Move Rule Violations: Prevents illegal moves (e.g., out of bounds, occupied square, or invalid flip).

- Persistence Errors: Displays errors for missing or corrupted save files.
## 🧩 Example Gameplay

```text
> new
> place D3
> place C3
> undo
> redo
> save game_1.oth
> load game_1.oth
> exit
``` 
**Language:** C++20  

**Author:** Mober

**Project Type:** Advanced Programming Final Project
