#include <windows.h>
#include <string>
#include <sstream>

using namespace std;

#define GRID_SIZE 9
#define CELL_SIZE 50
#define GRID_X 40
#define GRID_Y 50

HWND cells[GRID_SIZE][GRID_SIZE];
HWND statusLabel;
HFONT cellFont;
HFONT titleFont;
HBRUSH fixedBrush;

int sudoku[GRID_SIZE][GRID_SIZE] =
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

int originalGrid[GRID_SIZE][GRID_SIZE] =
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

void setStatus(const char* text)
{
    SetWindowTextA(statusLabel, text);
}

bool isSafe(int row, int col, int number)
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        if (sudoku[row][x] == number)
            return false;
    }

    for (int x = 0; x < GRID_SIZE; x++)
    {
        if (sudoku[x][col] == number)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (sudoku[startRow + i][startCol + j] == number)
                return false;
        }
    }

    return true;
}

bool findEmptyCell(int &row, int &col)
{
    for (row = 0; row < GRID_SIZE; row++)
    {
        for (col = 0; col < GRID_SIZE; col++)
        {
            if (sudoku[row][col] == 0)
                return true;
        }
    }

    return false;
}

bool solveSudoku()
{
    int row, col;

    if (!findEmptyCell(row, col))
        return true;

    for (int number = 1; number <= 9; number++)
    {
        if (isSafe(row, col, number))
        {
            sudoku[row][col] = number;

            if (solveSudoku())
                return true;

            sudoku[row][col] = 0;
        }
    }

    return false;
}

void updateGrid()
{
    char buffer[10];

    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (sudoku[row][col] == 0)
            {
                SetWindowTextA(cells[row][col], "");
            }
            else
            {
                sprintf_s(buffer, "%d", sudoku[row][col]);
                SetWindowTextA(cells[row][col], buffer);
            }
        }
    }
}

bool readUserGrid()
{
    char buffer[20];

    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (originalGrid[row][col] != 0)
            {
                sudoku[row][col] = originalGrid[row][col];
                continue;
            }

            GetWindowTextA(cells[row][col], buffer, sizeof(buffer));

            string value = buffer;

            if (value.empty())
            {
                sudoku[row][col] = 0;
                continue;
            }

            if (value.length() != 1 ||
                value[0] < '1' ||
                value[0] > '9')
            {
                return false;
            }

            sudoku[row][col] = value[0] - '0';
        }
    }

    return true;
}

void loadOriginalPuzzle()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            sudoku[row][col] = originalGrid[row][col];
        }
    }

    updateGrid();
    setStatus("Demo Sudoku loaded.");
}

void clearBoard()
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            sudoku[row][col] = originalGrid[row][col];

            if (originalGrid[row][col] == 0)
            {
                SetWindowTextA(cells[row][col], "");
            }
        }
    }

    setStatus("Board cleared. Enter values in empty cells.");
}

void solveBoard()
{
    if (!readUserGrid())
    {
        MessageBoxA(
            NULL,
            "Please enter only numbers from 1 to 9.",
            "Invalid Input",
            MB_OK | MB_ICONWARNING
        );

        setStatus("Invalid input detected.");
        return;
    }

    int backup[GRID_SIZE][GRID_SIZE];

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            backup[i][j] = sudoku[i][j];
        }
    }

    if (solveSudoku())
    {
        updateGrid();
        setStatus("Sudoku solved successfully!");
        MessageBoxA(
            NULL,
            "Sudoku solved successfully!",
            "Success",
            MB_OK | MB_ICONINFORMATION
        );
    }
    else
    {
        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                sudoku[i][j] = backup[i][j];
            }
        }

        updateGrid();
        setStatus("No solution exists for this puzzle.");

        MessageBoxA(
            NULL,
            "No solution exists for the current Sudoku.",
            "No Solution",
            MB_OK | MB_ICONERROR
        );
    }
}

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            titleFont = CreateFontA(
                26, 0, 0, 0,
                FW_BOLD,
                FALSE, FALSE, FALSE,
                ANSI_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                "Arial"
            );

            cellFont = CreateFontA(
                22, 0, 0, 0,
                FW_BOLD,
                FALSE, FALSE, FALSE,
                ANSI_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                "Arial"
            );

            CreateWindowA(
                "STATIC",
                "CodeAlpha - Sudoku Solver",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                40, 10, 450, 35,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            HWND title = FindWindowExA(
                hwnd,
                NULL,
                "STATIC",
                "CodeAlpha - Sudoku Solver"
            );

            if (title)
                SendMessage(title, WM_SETFONT, (WPARAM)titleFont, TRUE);

            fixedBrush = CreateSolidBrush(RGB(225, 225, 225));

            for (int row = 0; row < GRID_SIZE; row++)
            {
                for (int col = 0; col < GRID_SIZE; col++)
                {
                    int x = GRID_X + col * CELL_SIZE;
                    int y = GRID_Y + row * CELL_SIZE;

                    cells[row][col] = CreateWindowExA(
                        WS_EX_CLIENTEDGE,
                        "EDIT",
                        "",
                        WS_VISIBLE |
                        WS_CHILD |
                        ES_CENTER |
                        ES_NUMBER,
                        x,
                        y,
                        CELL_SIZE - 2,
                        CELL_SIZE - 2,
                        hwnd,
                        (HMENU)(1000 + row * 9 + col),
                        NULL,
                        NULL
                    );

                    SendMessage(
                        cells[row][col],
                        WM_SETFONT,
                        (WPARAM)cellFont,
                        TRUE
                    );

                    if (originalGrid[row][col] != 0)
                    {
                        char value[5];
                        sprintf_s(
                            value,
                            "%d",
                            originalGrid[row][col]
                        );

                        SetWindowTextA(
                            cells[row][col],
                            value
                        );

                        EnableWindow(
                            cells[row][col],
                            FALSE
                        );
                    }
                }
            }

            HWND solveButton = CreateWindowA(
                "BUTTON",
                "SOLVE SUDOKU",
                WS_VISIBLE | WS_CHILD,
                40, 525, 140, 40,
                hwnd,
                (HMENU)2001,
                NULL,
                NULL
            );

            HWND clearButton = CreateWindowA(
                "BUTTON",
                "CLEAR",
                WS_VISIBLE | WS_CHILD,
                195, 525, 100, 40,
                hwnd,
                (HMENU)2002,
                NULL,
                NULL
            );

            HWND demoButton = CreateWindowA(
                "BUTTON",
                "LOAD DEMO",
                WS_VISIBLE | WS_CHILD,
                310, 525, 120, 40,
                hwnd,
                (HMENU)2003,
                NULL,
                NULL
            );

            SendMessage(
                solveButton,
                WM_SETFONT,
                (WPARAM)cellFont,
                TRUE
            );

            SendMessage(
                clearButton,
                WM_SETFONT,
                (WPARAM)cellFont,
                TRUE
            );

            SendMessage(
                demoButton,
                WM_SETFONT,
                (WPARAM)cellFont,
                TRUE
            );

            statusLabel = CreateWindowA(
                "STATIC",
                "Ready - Enter values or press SOLVE SUDOKU.",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                40, 580, 450, 30,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            SendMessage(
                statusLabel,
                WM_SETFONT,
                (WPARAM)cellFont,
                TRUE
            );

            break;
        }

        case WM_COMMAND:
        {
            int controlId = LOWORD(wParam);

            if (controlId == 2001)
            {
                solveBoard();
            }
            else if (controlId == 2002)
            {
                clearBoard();
            }
            else if (controlId == 2003)
            {
                loadOriginalPuzzle();
            }

            break;
        }

        case WM_CTLCOLORSTATIC:
        {
            return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
        }

        case WM_DESTROY:
        {
            DeleteObject(titleFont);
            DeleteObject(cellFont);
            DeleteObject(fixedBrush);

            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProcA(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow)
{
    const char CLASS_NAME[] = "SudokuGUIWindow";

    WNDCLASSA wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        CLASS_NAME,
        "CodeAlpha Sudoku Solver",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        560,
        680,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}