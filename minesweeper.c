#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 10
#define MINES 10

typedef enum
{
    FALSE,
    TRUE
} bool;

typedef enum
{
    CLOSED,
    OPENED,
    MINE
} Cell;

Cell board[WIDTH][HEIGHT];
bool game_end = FALSE;
int cells_opened;

bool isClosed(int x, int y)
{
    return board[x][y] == CLOSED;
}

bool isOpened(int x, int y)
{
    return board[x][y] == OPENED;
}

bool isMine(int x, int y)
{
    return board[x][y] == MINE;
}

int getMinesNumbers(int x, int y)
{
    int mines = 0;

    if (x == 0)
    {
        if (y == 0)
        {
            if (isMine(x + 1, y)) mines++; // Right.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x + 1, y + 1)) mines++; // Bottom Right.
        }
        else if (y == HEIGHT - 1)
        {
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x + 1, y - 1)) mines++; // Top Right.
            if (isMine(x + 1, y)) mines++; // Right.
        }
        else
        {
            if (isMine(x + 1, y)) mines++; // Right.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x + 1, y + 1)) mines++; // Bottom Right.
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x + 1, y - 1)) mines++; // Top Right.
        }
    }
    else if (x == WIDTH - 1)
    {
        if (y == 0)
        {
            if (isMine(x - 1, y)) mines++; // Left.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x - 1, y + 1)) mines++; // Bottom Left.
        }
        else if (y == HEIGHT - 1)
        {
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x - 1, y - 1)) mines++; // Top Left.
            if (isMine(x - 1, y)) mines++; // Left.
        }
        else
        {
            if (isMine(x - 1, y)) mines++; // Left.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x - 1, y + 1)) mines++; // Bottom Left.
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x - 1, y - 1)) mines++; // Top Left.
        }
    }
    else
    {
        if (y == 0)
        {
            if (isMine(x + 1, y)) mines++; // Right.
            if (isMine(x - 1, y)) mines++; // Left.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x + 1, y + 1)) mines++; // Bottom Right.
            if (isMine(x - 1, y + 1)) mines++; // Bottom Left.
        }
        else if (y == HEIGHT - 1)
        {
            if (isMine(x + 1, y)) mines++; // Right.
            if (isMine(x - 1, y)) mines++; // Left.
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x - 1, y - 1)) mines++; // Top Left.
            if (isMine(x + 1, y - 1)) mines++; // Top Right.
        }
        else
        {
            if (isMine(x, y - 1)) mines++; // Top.
            if (isMine(x - 1, y)) mines++; // Left.
            if (isMine(x, y + 1)) mines++; // Bottom.
            if (isMine(x + 1, y)) mines++; // Right.
            if (isMine(x + 1, y - 1)) mines++; // Top Right.
            if (isMine(x + 1, y + 1)) mines++; // Bottom Right.
            if (isMine(x - 1, y + 1)) mines++; // Bottom Left.
            if (isMine(x - 1, y - 1)) mines++; // Top Left.
        }
    }

    return mines;
}

char intToChar(int number)
{
    return (number < -9 || number > 9) ? '0' : number + '0';
}

void unlockCells(int x, int y)
{
    board[x][y] = OPENED;
    cells_opened++;

    if (getMinesNumbers(x, y) > 0) return;

    if (x == 0)
    {
        if (y == 0)
        {
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x + 1, y + 1)) unlockCells(x + 1, y + 1); // Bottom Right.
        }
        else if (y == HEIGHT - 1)
        {
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x + 1, y - 1)) unlockCells(x + 1, y - 1); // Top Right.
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
        }
        else
        {
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x + 1, y + 1)) unlockCells(x + 1, y + 1); // Bottom Right.
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x + 1, y - 1)) unlockCells(x + 1, y - 1); // Top Right.
        }
    }
    else if (x == WIDTH - 1)
    {
        if (y == 0)
        {
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x - 1, y + 1)) unlockCells(x - 1, y + 1); // Bottom Left.
        }
        else if (y == HEIGHT - 1)
        {
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x - 1, y - 1)) unlockCells(x - 1, y - 1); // Top Left.
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
        }
        else
        {
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x - 1, y + 1)) unlockCells(x - 1, y + 1); // Bottom Left.
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x - 1, y - 1)) unlockCells(x - 1, y - 1); // Top Left.
        }
    }
    else
    {
        if (y == 0)
        {
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x + 1, y + 1)) unlockCells(x + 1, y + 1); // Bottom Right.
            if (isClosed(x - 1, y + 1)) unlockCells(x - 1, y + 1); // Bottom Left.
        }
        else if (y == HEIGHT - 1)
        {
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x - 1, y - 1)) unlockCells(x - 1, y - 1); // Top Left.
            if (isClosed(x + 1, y - 1)) unlockCells(x + 1, y - 1); // Top Right.
        }
        else
        {
            if (isClosed(x, y - 1)) unlockCells(x, y - 1); // Top.
            if (isClosed(x - 1, y)) unlockCells(x - 1, y); // Left.
            if (isClosed(x, y + 1)) unlockCells(x, y + 1); // Bottom.
            if (isClosed(x + 1, y)) unlockCells(x + 1, y); // Right.
            if (isClosed(x + 1, y - 1)) unlockCells(x + 1, y - 1); // Top Right.
            if (isClosed(x + 1, y + 1)) unlockCells(x + 1, y + 1); // Bottom Right.
            if (isClosed(x - 1, y + 1)) unlockCells(x - 1, y + 1); // Bottom Left.
            if (isClosed(x - 1, y - 1)) unlockCells(x - 1, y - 1); // Top Left.
        }
    }
}

int getXPosition(void)
{
    int x;

    do
    {
        printf("Enter the X position from 1 to %d: ", HEIGHT);
        scanf("%d", &x);
    } while (x < 1 || x > HEIGHT);

    return --x;
}

int getYPosition(void)
{
    int y;

    do
    {
        printf("Enter the Y position from 1 to %d: ", WIDTH);
        scanf("%d", &y);
    } while (y < 1 || y > WIDTH);

    return --y;
}

void start(void)
{
    int start_x = getXPosition();
    int start_y = getYPosition();
    game_end = FALSE;
    cells_opened = 0;

    for (int i = 0; i < MINES;)
    {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        if (isMine(x, y) || (start_x == x && start_y == y)) continue;
        board[x][y] = MINE;

        i++;
    }

    unlockCells(start_x, start_y);
}

void fillBoard(Cell type)
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            board[x][y] = type;
        }
    }
}

void revealAll(void)
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            if (board[x][y] != MINE) board[x][y] = OPENED;
        }
    }
}

void draw(bool h_space)
{
    system("cls");

    printf("+");
    for (int x = 0; x < WIDTH; x++) printf((h_space) ? "--" : "-");
    printf((h_space) ? "-+\n" : "+\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        printf((h_space) ? "| " : "|");
        
        for (int x = 0; x < WIDTH; x++)
        {
            char ascii = (board[x][y] == CLOSED || board[x][y] == MINE) ? '#' : intToChar(getMinesNumbers(x, y));

            printf((h_space) ? "%c " : "%c", ascii);
        }

        printf((h_space) ? "| \n" : "|\n");
    }

    printf("+");
    for (int x = 0; x < WIDTH; x++) printf((h_space) ? "--" : "-");
    printf((h_space) ? "-+\n" : "+\n");
}

void drawMines(bool h_space)
{
    system("cls");
    
    printf("+");
    for (int x = 0; x < WIDTH; x++) printf((h_space) ? "--" : "-");
    printf((h_space) ? "-+\n" : "+\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        printf((h_space) ? "| " : "|");
        
        for (int x = 0; x < WIDTH; x++)
        {
            char ascii = (board[x][y] == MINE) ? 'M' : intToChar(getMinesNumbers(x, y));

            printf((h_space) ? "%c " : "%c", ascii);
        }

        printf((h_space) ? "| \n" : "|\n");
    }

    printf("+");
    for (int x = 0; x < WIDTH; x++) printf((h_space) ? "--" : "-");
    printf((h_space) ? "-+\n" : "+\n");
}

void logic(void)
{
    int x;
    int y;

    while (TRUE)
    {
        x = getXPosition();
        y = getYPosition();

        if (!isOpened(x, y)) break;

        printf("Select a cell that is closed.\n");
    };

    if (isMine(x, y))
    {
        revealAll();
        drawMines(TRUE);
        printf("Game Over.\n");
        game_end = TRUE;
        return;
    }

    unlockCells(x, y);

    if (cells_opened == WIDTH * HEIGHT - MINES)
    {
        drawMines(TRUE);
        printf("You Win.\n");
        game_end = TRUE;
        return;
    }
}

int main(void)
{
    srand(time(NULL));
    playAgain:;

    fillBoard(CLOSED);
    draw(TRUE);
    start();

    while (!game_end)
    {
        draw(TRUE);
        logic();
    }

    char play_again;

    while (TRUE)
    {
        printf("Play again? (Y - N): ");
        scanf(" %c", &play_again);

        if (play_again == 'y' || play_again == 'Y' || play_again == 'n' || play_again == 'N') break;
    }

    if (play_again == 'y' || play_again == 'Y') goto playAgain;

    return 0;
}