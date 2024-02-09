# Rat in Maze Game

## Overview
This C++ program simulates the classic "Rat in Maze" game with different difficulty levels. The player controls a rat navigating through a maze, encountering obstacles, and scoring points based on movements.

## Files
- `main.cpp`: Main code implementing the Rat in Maze game logic.
- `easy.txt`, `medium.txt`, `hard.txt`: Input files containing maze layouts for easy, medium, and hard difficulty levels.
- `record.txt`: Record file storing maximum scores.

## Features
1. **Rat Movement and Obstacle Handling:**
   - The player can move the rat in four directions: up, down, left, and right.
   - The maze contains obstacles represented by different characters.
   - Scoring mechanism based on successful moves and encounters.

2. **Display Functions:**
   - `display`: Prints the current state of the maze.
   - `show_complete_path`: Displays a sample of the rat's path with '*' marking the route.

3. **File Handling:**
   - `fill_array_from_file`: Reads maze data from a file into an array.
   - `write_on_file_full`: Writes the maze data to a file.

4. **Game Menus:**
   - `direction_menu`: Handles user menu selections for rat movements.
   - `game_menu`: Handles user menu selections for game difficulty (easy, medium, hard).

5. **Initialization:**
   - `initialize_twoD_array`: Initializes a two-dimensional array for the maze.

6. **Score Handling:**
   - `max_score`: Reads the maximum score from a file and displays relevant information.
   - `return_max_index`: Returns the index of the maximum value in an integer array.

7. **Miscellaneous Functions:**
   - `read_number_from_file`: Reads a single character from a file.
   - `write_on_file`: Writes a character to a file.

## How to Play
1. Compile the program using a C++ compiler.
   ```bash
   g++ main.cpp -o rat_in_maze
   ```
2. Run the executable.
   ```bash
   ./rat_in_maze
   ```
3. Select the desired difficulty level (easy, medium, or hard) and follow on-screen instructions to navigate the rat through the maze.

## Maze Input Files
- Customize the `easy.txt`, `medium.txt`, and `hard.txt` files for different maze layouts corresponding to the easy, medium, and hard difficulty levels.

## Record File
- `record.txt` stores maximum scores achieved by players.

## Notes
- Adjust the maze layouts in the input files for each difficulty level.
- The program reads and writes data to `record.txt` for score tracking.

## Contributing
Contributions are welcome! Feel free to fork the repository and submit pull requests.