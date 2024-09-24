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
int path[SIZE][SIZE]; // ��� ǥ�ÿ�
int playerX, playerY; // �÷��̾� ��ġ

// �ܼ� ������ �����ϴ� �Լ�
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeBoard() {
    // ���带 ���(1)���� �ʱ�ȭ
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '1';
            path[i][j] = 1; // ��δ� ������� �ʱ�ȭ
        }
    }
}

// ��ֹ��� ��� ��ó�� ��ġ
void placeObstacles() {
    int placedObstacles = 0;
    while (placedObstacles < MAX_OBSTACLES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        // ��ֹ��� ��� �ٷ� ������ ��ġ�ǵ���
        if (path[y][x] == 0) continue; // ��� ������ ��ֹ� ��ġ���� ����

        bool nearPath = false;
        // ��� ��ó(��/��/��/�Ͽ� ��ΰ� ������)���� ��ֹ� ��ġ
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

// ���� ��ܿ��� ���� �ϴܱ��� ��θ� �� �ٷ� ����
void generatePath() {
    int x = 0, y = 0;
    int direction = rand() % 2; // 0: ��, 1: ��
    int stepCount = 0; // ���� �������� �̵��� ĭ ��

    board[y][x] = '0';
    path[y][x] = 0;

    while (x != SIZE - 1 || y != SIZE - 1) {
        if (stepCount >= MAX_STEPS_IN_ONE_DIRECTION) {
            // 5ĭ �̻� ���� �������� �̵������� ���� ��ȯ
            direction = (direction == 0) ? 1 : 0;
            stepCount = 0;
        }

        if (direction == 0 && x < SIZE - 1) {
            // ���������� �̵�
            x++;
        }
        else if (direction == 1 && y < SIZE - 1) {
            // �Ʒ��� �̵�
            y++;
        }
        else {
            // ���� �� ������ �������� ���ϸ� ������ �������� �̵�
            direction = (direction == 0) ? 1 : 0; // ���� ��ȯ
            stepCount = 0;
            continue; // �ٷ� ���� �̵����� �Ѿ
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
                setColor(4); // ���������� �÷��̾� ��ġ ���
                cout << "* ";
                setColor(7); // �⺻ �������� ����
            }
            else if (board[i][j] == 'X') {
                setColor(1); // �Ķ������� ��ֹ� ���
                cout << "X ";
                setColor(7); // �⺻ �������� ����
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
    case 'w': newY--; break; // ��
    case 's': newY++; break; // ��
    case 'a': newX--; break; // ��
    case 'd': newX++; break; // ��
    }

    // ��� �������� �̵� ����
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

    // �ʱ� �÷��̾� ��ġ ���� (���� ���)
    playerX = 0;
    playerY = 0;

    char command;
    bool isPlaying = true;

    while (isPlaying) {
        printBoard();

        command = _getch();

        switch (command) {
        case 'r': // ��ü ���� (�̹� ���� ��ܿ� ����)
            playerX = 0;
            playerY = 0;
            break;
        case 'w': case 'a': case 's': case 'd': // �̵�
            movePlayer(command);
            break;
        case '\r': // Enter: ���ο� ��� ����
            initializeBoard();
            generatePath();
            placeObstacles();
            playerX = 0;
            playerY = 0;
            break;
        case 'q': // ����
            isPlaying = false;
            break;
        }
    }

    return 0;
}

