# 🎯 CodeAlpha Sudoku Solver

A C++ **Sudoku Solver** developed as part of the **CodeAlpha C++ Programming Internship**.

## 📌 Project Overview

This project is a 9×9 Sudoku Solver implemented in C++. It uses a **two-dimensional array**, **backtracking**, and **recursion** to solve Sudoku puzzles while validating the required Sudoku constraints.

An optional graphical interface is also included to provide an easier way to display and solve the puzzle.

## ✨ Key Features

- 9×9 Sudoku grid using a 2D array
- Backtracking algorithm for solving the puzzle
- Recursive solving approach
- Row constraint validation
- Column constraint validation
- 3×3 subgrid constraint validation
- Automatic Sudoku solution
- GUI for easier puzzle display and solving

## 📂 Project Files

### `Sudoku_Solver.cpp`

Console-based implementation of the Sudoku solving algorithm.

### `Sudoku_GUI.cpp`

Graphical interface for displaying and solving the Sudoku puzzle.

## 🔄 How the Solver Works

1. The Sudoku grid is represented as a 9×9 two-dimensional array.
2. Empty cells are identified.
3. Possible numbers from 1 to 9 are checked.
4. Row, column, and 3×3 subgrid constraints are validated.
5. A valid number is placed in the empty cell.
6. The algorithm recursively continues.
7. If a choice leads to an invalid state, the algorithm backtracks and tries another number.
8. The process continues until the Sudoku is solved.

## 🛠️ Technologies Used

- C++
- 2D Arrays
- Recursion
- Backtracking Algorithm
- Windows GUI

## 📌 CodeAlpha Internship

**Project: Sudoku Solver**

This project was completed as part of the **CodeAlpha C++ Programming Internship**.

## 🎥 Project Demonstration

The project includes a working demonstration showing the Sudoku puzzle being loaded and successfully solved.

## 📁 Repository Contents

- `Sudoku_Solver.cpp`
- `Sudoku_GUI.cpp`
