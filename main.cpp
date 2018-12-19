#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

bool finished;
bool paused;
const int width = 20;
const int height = 20;
int x, y, fruitX,fruitY, score;
enum eDirection {STOP = 0, LEFT,RIGHT,UP,DOWN};
eDirection dir;
int tailX[100];
int tailY[100];
int nTail = 0;

void setup() {
    finished = false;
    paused = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand((int)time(0));
    fruitX = rand() % (width - 1);
    fruitY = rand() % (height - 1);
    score = 0;
}

void draw() {
    system("CLS");

    for (int i = 0; i < width + 1; i++){
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            if ((j == 0) || (j == width - 1)) {
                printf("#");
            }

            if (i == y && j == x) {
                printf("O");
            } else if (i == fruitY && j == fruitX) {
                printf("F");
            } else {
                bool tailPrinted = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        tailPrinted = true;
                    }
                }
                if (!tailPrinted) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    for (int i = 0; i < width + 1; i++){
        printf("#");
    }
    printf("\n");
    printf("Score: %d\n",score);
}

void input() {
    if (_kbhit()) {
        switch(_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            finished = true;
            break;
        case 'p':
            if (paused) {
                paused = false;
            } else {
                paused = true;
                printf("Game Paused");
            }
            break;
        }
    }
}

void logic() {
    //SETTING TAIL
    int prvX = tailX[0];
    int prvY = tailY[0];
    int prvX2, prvY2;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prvX2 = tailX[i];
        prvY2 = tailY[i];
        tailX[i] = prvX;
        tailY[i] = prvY;
        prvX = prvX2;
        prvY = prvY2;
    }

    //CHOOSING DIRECTION
    switch(dir) {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    //DEATH CHECKS
    if (x < 0 || x >= width - 1 || y < 0 || y >= height) {
        finished = true;
    }
    for (int i = 0;i < nTail;i++){
        if (x == tailX[i] && y == tailY[i]) {
            finished = true;
        }
    }

    //EAT FRUIT
    if (x == fruitX && y == fruitY) {
        nTail++;
        score += 1;
        fruitX = rand() % (width - 1);
        fruitY = rand() % (height - 1);
    }
}

int main() {
    setup();

    while (!finished) {
        input();
        while (paused) {
            input();
        }
        logic();
        draw();
        Sleep(100);
    }

}
