#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

int height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int nTail;
int a = 20;
int delay = 300;
int HighScore = 0;

int sleep_time(int *delay, int *a)
{
    if(score > *a && *delay > 10)
    {
        *delay = *delay - 10;
        *a = *a + 20;
        return *delay;
    }
    else
    {
        return *delay;
    }
}



void setup() {
    gameover = 0;
    x = height / 2;
    y = width / 2;
    flag = 0;
    label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
        goto label1;
    label2:
    fruity = rand() % 20;
    if (fruity == 0)
        goto label2;
    score = 0;
}

void input() {
    if (_kbhit()) {
        char keyPressed = _getch();
        switch (keyPressed) {
            case 'a':
                if (flag != 3)
                    flag = 1;
                break;
            case 's':
                if (flag != 4)
                    flag = 2;
                break;
            case 'd':
                if (flag != 1)
                    flag = 3;
                break;
            case 'w':
                if (flag != 2)
                    flag = 4;
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

void draw() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
                printf("#");
            else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx && j == fruity)
                    printf("*");
                else {
                    bool printTail = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == i && tailY[k] == j)
                        {
                            printf("o");
                            printTail = true;
                        }
                    }
                    if (!printTail)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score = %d", score);
    printf("High score: %d", highscore);
    printf("\n");
    printf("Press X to quit the game");
}

void logic() {
    Sleep(sleep_time(&delay, &a));
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
    }

    if (x < 0 || x > height-1 || y < 0 || y > width-1)
    {
        printf("\nGame over: Hit the boundary\n");
        gameover = 1;
        score, nTail = 0;
        delay = 300;

    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
        {
            printf("\nGame over: Collided with yourself\n");
            if(HighScore < score){
            HighScore = score;
            }
            gameover = 1;
            score, nTail = 0;
            delay = 300;

        }
    }

    if (x == fruitx && y == fruity) {
        label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;
        label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        score += 10;
        nTail++;
    }
}

int main() {
    char ch;
    do {
        setup();
        while (!gameover) {
            input();
            draw();
            logic();
        }
        
        printf("\nDo you want to continue (y/n) ? ");
            scanf("%c", &ch);
            while (getchar() != '\n');
    }
    while (ch == 'y');
    return 0;
}
