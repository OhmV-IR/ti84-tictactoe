#include <ti/screen.h>
#include <ti/getkey.h>
#include <stdlib.h>
#include "BlockState.h"
#include <ti/info.h>
#include <time.h>

#define X_CHOICE k_1
#define O_CHOICE k_2
#define GRID_SIZE 3

int GetRandCoord()
{
    return rand() % (GRID_SIZE + 1);
}

void PrintGrid(BlockState (&grid)[GRID_SIZE][GRID_SIZE])
{
    os_ClrHome();
    time_t rawtime;
    time(&rawtime);
    srand(rawtime);
    for (int row = 0; row < GRID_SIZE; row++)
    {
        // No PutChar function so I have to do this which makes my hyperoptimization brain very sad
        char rowBuf[GRID_SIZE + 1];
        // Enum members of BlockState are the int conversions of the characters we want to display, so we just reinterpret the grid as characters and tada
        for (int col = 0; col < GRID_SIZE; col++)
        {
            rowBuf[col] = (char)grid[row][col];
        }
        rowBuf[GRID_SIZE] = '\0';
        os_PutStrFull(rowBuf);
        os_NewLine();
    }
}

void PlayerTurn(BlockState (&grid)[GRID_SIZE][GRID_SIZE], BlockState playerBlock)
{
    while (true)
    {
        PrintGrid(grid);
        os_PutStrFull("Enter row then col using numpad(top-left is 1,1)");
        os_NewLine();
        int16_t key1 = os_GetKey();
        int16_t key2 = os_GetKey();
        int row;
        int col;
        if (key1 == k_1)
        {
            row = 0;
        }
        else if (key1 == k_2)
        {
            row = 1;
        }
        else if (key1 == k_3)
        {
            row = 2;
        }
        else
        {
            os_PutStrFull("Invalid input");
            os_NewLine();
            continue;
        }
        if (key2 == k_1)
        {
            col = 0;
        }
        else if (key2 == k_2)
        {
            col = 1;
        }
        else if (key2 == k_3)
        {
            col = 2;
        }
        else
        {
            os_PutStrFull("Invalid input");
            os_NewLine();
            continue;
        }
        if (grid[row][col] != BlockState::OPEN)
        {
            os_PutStrFull("Already a piece there");
            os_NewLine();
            continue;
        }
        grid[row][col] = playerBlock;
        PrintGrid(grid);
        return;
    }
}

// WARNING: Will hang if no valid place to put square
void ComputerTurn(BlockState (&grid)[GRID_SIZE][GRID_SIZE], BlockState computerBlock)
{
    while (true)
    {
        int x = GetRandCoord();
        int y = GetRandCoord();
        if (grid[x][y] == BlockState::OPEN)
        {
            grid[x][y] = computerBlock;
            PrintGrid(grid);
            return;
        }
    }
}

Winner GetWinner(BlockState (&grid)[GRID_SIZE][GRID_SIZE]) {
    // Check rows and columns
    for (int i = 0; i < GRID_SIZE; i++) {
        // Row check
        if (grid[i][0] != BlockState::OPEN) {
            bool isMatch = true;
            for (int col = 1; col < GRID_SIZE; col++) {
                if (grid[i][col] != grid[i][0]) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch)
                return (Winner)grid[i][0];
        }

        // Column check
        if (grid[0][i] != BlockState::OPEN) {
            bool isMatch = true;
            for (int row = 1; row < GRID_SIZE; row++) {
                if (grid[row][i] != grid[0][i]) {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch)
                return (Winner)grid[0][i];
        }
    }

    // Diagonal check
    if (grid[0][0] != BlockState::OPEN) {
        bool isMatch = true;
        for (int i = 1; i < GRID_SIZE; i++) {
            if (grid[i][i] != grid[0][0]) {
                isMatch = false;
                break;
            }
        }
        if (isMatch)
            return (Winner)grid[0][0];
    }

    // Anti-diagonal check
    if (grid[0][GRID_SIZE - 1] != BlockState::OPEN) {
        bool isMatch = true;
        for (int i = 1; i < GRID_SIZE; i++) {
            if (grid[i][GRID_SIZE - 1 - i] != grid[0][GRID_SIZE - 1]) {
                isMatch = false;
                break;
            }
        }
        if (isMatch)
            return (Winner)grid[0][GRID_SIZE - 1];
    }

    for (int a = 0; a < GRID_SIZE; a++) {
        for (int b = 0; b < GRID_SIZE; b++) {
            if (grid[a][b] == BlockState::OPEN) {
                return Winner::NONE;
            }
        }
    }

    return Winner::TIE;
}

bool GameEnded(BlockState (&grid)[GRID_SIZE][GRID_SIZE], BlockState playerBlock)
{
    Winner winner = GetWinner(grid);
    if (winner == Winner::NONE)
        return false;
    if (winner == (Winner)playerBlock)
    {
        os_PutStrFull("You win!");
        os_NewLine();
    }
    else if (winner == Winner::TIE)
    {
        os_PutStrFull("Tie!");
        os_NewLine();
    }
    else
    {
        os_PutStrFull("Computer wins!");
        os_NewLine();
    }
    os_PutStrFull("Press any key to exit");
    os_NewLine();
    return true;
}

/* Main function, called first */
int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Print a string */
    os_PutStrFull("Select player");
    os_NewLine();
    os_PutStrFull("1: Play as X(go first)");
    os_NewLine();
    os_PutStrFull("2: Play as O(go second)");
    os_NewLine();

    uint16_t playerChoice;
    do
    {
        playerChoice = os_GetKey();
    } while (playerChoice != X_CHOICE && playerChoice != O_CHOICE);
    BlockState grid[GRID_SIZE][GRID_SIZE];
    for (int a = 0; a < GRID_SIZE; a++)
    {
        for (int b = 0; b < GRID_SIZE; b++)
        {
            grid[a][b] = BlockState::OPEN;
        }
    }
    if (playerChoice == X_CHOICE)
    {
        while (true)
        {
            PlayerTurn(grid, BlockState::X);
            if (GameEnded(grid, BlockState::X))
            {
                break;
            }
            ComputerTurn(grid, BlockState::O);
            if (GameEnded(grid, BlockState::X))
            {
                break;
            }
        }
    }
    else
    {
        while (true)
        {
            ComputerTurn(grid, BlockState::X);
            if (GameEnded(grid, BlockState::O))
            {
                break;
            }
            PlayerTurn(grid, BlockState::O);
            if (GameEnded(grid, BlockState::O))
            {
                break;
            }
        }
    }
    (void)os_GetKey();
    return 0;
}