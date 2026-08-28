#include <iostream>
using namespace std;

#define SIZE 9

// Display Sudoku grid
void printGrid(int grid[SIZE][SIZE])
{
    cout << "\n=========================================\n";
    cout << "             SUDOKU SOLVER\n";
    cout << "=========================================\n";

    for (int row = 0; row < SIZE; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            cout << "-----------+-----------+-----------\n";
        }

        for (int col = 0; col < SIZE; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                cout << "| ";
            }

            cout << grid[row][col] << " ";
        }

        cout << endl;
    }

    cout << "=========================================\n";
}

// Check whether a number can be placed safely
bool isSafe(int grid[SIZE][SIZE], int row, int col, int number)
{
    // Check row
    for (int x = 0; x < SIZE; x++)
    {
        if (grid[row][x] == number)
        {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < SIZE; x++)
    {
        if (grid[x][col] == number)
        {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[startRow + i][startCol + j] == number)
            {
                return false;
            }
        }
    }

    return true;
}

// Find an empty cell
bool findEmptyCell(int grid[SIZE][SIZE], int &row, int &col)
{
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (grid[row][col] == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Sudoku solving function using backtracking
bool solveSudoku(int grid[SIZE][SIZE])
{
    int row;
    int col;

    // If there are no empty cells, Sudoku is solved
    if (!findEmptyCell(grid, row, col))
    {
        return true;
    }

    // Try numbers from 1 to 9
    for (int number = 1; number <= 9; number++)
    {
        if (isSafe(grid, row, col, number))
        {
            // Place number
            grid[row][col] = number;

            // Recursively solve remaining cells
            if (solveSudoku(grid))
            {
                return true;
            }

            // Backtracking: remove number
            grid[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    // 0 represents an empty cell
    int grid[SIZE][SIZE] =
    {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "\nOriginal Sudoku:";
    printGrid(grid);

    if (solveSudoku(grid))
    {
        cout << "\nSudoku solved successfully!\n";
        printGrid(grid);
    }
    else
    {
        cout << "\nNo solution exists for this Sudoku puzzle.\n";
    }

    return 0;
}
