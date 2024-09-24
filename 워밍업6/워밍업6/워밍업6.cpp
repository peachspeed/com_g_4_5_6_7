#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

#define SIZE 30
#define MAX_OBSTACLES 30
#define MAX_STEPS_IN_ONE_DIRECTION 5

char board[SIZE][SIZE];
int path[SIZE][SIZE]; // 경로 표시용
int playerX, playerY; // 플레이어 위치

// 콘솔 색상을 설정하는 함수
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeBoard() {
    // 보드를 배경(1)으로 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '1';
            path[i][j] = 1; // 경로는 배경으로 초기화
        }
    }
}

// 장애물을 경로 근처에 배치
void placeObstacles() {
    int placedObstacles = 0;
    while (placedObstacles < MAX_OBSTACLES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        // 장애물은 경로 바로 옆에만 배치되도록
        if (path[y][x] == 0) continue; // 경로 위에는 장애물 배치하지 않음

        bool nearPath = false;
        // 경로 근처(좌/우/상/하에 경로가 있으면)에만 장애물 배치
        if (x > 0 && path[y][x - 1] == 0) nearPath = true;
        if (x < SIZE - 1 && path[y][x + 1] == 0) nearPath = true;
        if (y > 0 && path[y - 1][x] == 0) nearPath = true;
        if (y < SIZE - 1 && path[y + 1][x] == 0) nearPath = true;

        if (nearPath) {
            board[y][x] = 'X';
            placedObstacles++;
        }
    }
}

// 좌측 상단에서 우측 하단까지 경로를 한 줄로 생성
void generatePath() {
    int x = 0, y = 0;
    int direction = rand() % 2; // 0: 우, 1: 하
    int stepCount = 0; // 현재 방향으로 이동한 칸 수

    board[y][x] = '0';
    path[y][x] = 0;

    while (x != SIZE - 1 || y != SIZE - 1) {
        if (stepCount >= MAX_STEPS_IN_ONE_DIRECTION) {
            // 5칸 이상 같은 방향으로 이동했으면 방향 전환
            direction = (direction == 0) ? 1 : 0;
            stepCount = 0;
        }

        if (direction == 0 && x < SIZE - 1) {
            // 오른쪽으로 이동
            x++;
        }
        else if (direction == 1 && y < SIZE - 1) {
            // 아래로 이동
            y++;
        }
        else {
            // 만약 위 조건을 만족하지 못하면 나머지 방향으로 이동
            direction = (direction == 0) ? 1 : 0; // 방향 전환
            stepCount = 0;
            continue; // 바로 다음 이동으로 넘어감
        }

        board[y][x] = '0';
        path[y][x] = 0;
        stepCount++;
    }
}

void printBoard() {
    system("CLS");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == playerY && j == playerX) {
                setColor(4); // 빨간색으로 플레이어 위치 출력
                cout << "* ";
                setColor(7); // 기본 색상으로 복귀
            }
            else if (board[i][j] == 'X') {
                setColor(1); // 파란색으로 장애물 출력
                cout << "X ";
                setColor(7); // 기본 색상으로 복귀
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void movePlayer(char command) {
    int newX = playerX, newY = playerY;

    switch (command) {
    case 'w': newY--; break; // 상
    case 's': newY++; break; // 하
    case 'a': newX--; break; // 좌
    case 'd': newX++; break; // 우
    }

    // 경로 위에서만 이동 가능
    if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE && path[newY][newX] == 0) {
        playerX = newX;
        playerY = newY;
    }
}

int main() {
    srand(time(0));

    initializeBoard();
    generatePath();
    placeObstacles();

    // 초기 플레이어 위치 설정 (좌측 상단)
    playerX = 0;
    playerY = 0;

    char command;
    bool isPlaying = true;

    while (isPlaying) {
        printBoard();

        command = _getch();

        switch (command) {
        case 'r': // 객체 생성 (이미 좌측 상단에 있음)
            playerX = 0;
            playerY = 0;
            break;
        case 'w': case 'a': case 's': case 'd': // 이동
            movePlayer(command);
            break;
        case '\r': // Enter: 새로운 경로 생성
            initializeBoard();
            generatePath();
            placeObstacles();
            playerX = 0;
            playerY = 0;
            break;
        case 'q': // 종료
            isPlaying = false;
            break;
        }
    }

    return 0;
}

