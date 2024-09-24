#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE 30

// 보드를 초기화하는 함수
void Board(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

// 보드를 출력하는 함수
void printBoard(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << setw(2) << board[i][j];
        }
        cout << '\n';
    }
}

// 사각형을 그리는 함수 (좌우로 넘어갈 때 wrap-around 처리)
void draw(char board[][SIZE], int x1, int y1, int x2, int y2) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            int wrapX = (j + SIZE) % SIZE; // x축을 보드 크기로 나눠서 wrap-around
            int wrapY = (i + SIZE) % SIZE; // y축도 마찬가지로 처리
            board[wrapY][wrapX] = '#'; // 사각형을 '#'로 그린다
        }
    }
}

// 사각형을 지우는 함수 (wrap-around 적용)
void clear(char board[][SIZE], int x1, int y1, int x2, int y2) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            int wrapX = (j + SIZE) % SIZE;
            int wrapY = (i + SIZE) % SIZE;
            board[wrapY][wrapX] = '.'; // 사각형을 지운다
        }
    }
}

int main() {
    char board[SIZE][SIZE];
    int x1, y1, x2, y2;
    char command;

    Board(board);

    cout << "사각형의 좌표 (x1, y1) (x2, y2)를 입력하세요: ";
    cin >> x1 >> y1 >> x2 >> y2;

    // 보드에 사각형 그리기
    draw(board, x1, y1, x2, y2);
    printBoard(board);

    while (true) {
        cout << "명령어 (x/X, y/Y, s/S, i/I, j/J, m, r, q): ";
        cin >> command;

        // 현재 사각형을 지움
        clear(board, x1, y1, x2, y2);

        switch (command) {
        case 'x':  // x 축을 오른쪽으로 이동
            x1 = (x1 + 1) % SIZE;
            x2 = (x2 + 1) % SIZE;
            break;
        case 'X':  // x 축을 왼쪽으로 이동
            x1 = (x1 - 1 + SIZE) % SIZE;
            x2 = (x2 - 1 + SIZE) % SIZE;
            break;
        case 'y':  // y 축을 아래로 이동
            y1 = (y1 + 1) % SIZE;
            y2 = (y2 + 1) % SIZE;
            break;
        case 'Y':  // y 축을 위로 이동
            y1 = (y1 - 1 + SIZE) % SIZE;
            y2 = (y2 - 1 + SIZE) % SIZE;
            break;
        case 's':  // 사각형 축소
            if (x1 < x2 && y1 < y2) {
                x2 = (x2 > 0) ? x2 - 1 : x2;
                y2 = (y2 > 0) ? y2 - 1 : y2;
            }
            break;
        case 'S':  // 사각형 확대
            x2 = (x2 < SIZE - 1) ? x2 + 1 : x2;
            y2 = (y2 < SIZE - 1) ? y2 + 1 : y2;
            break;
        case 'm':  // 현재 사각형의 좌표를 출력
            cout << "사각형 좌표: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")\n";
            break;
        case 'r':  // 새로운 좌표를 입력받아 사각형을 다시 그림
            cout << "새 좌표 (x1, y1) (x2, y2)를 입력하세요: ";
            cin >> x1 >> y1 >> x2 >> y2;
            break;
        case 'q':  // 프로그램 종료
            cout << "프로그램을 종료합니다.\n";
            return 0;
        default:
            cout << "유효하지 않은 명령어입니다.\n";
            continue;
        }

        // 새로운 위치에 사각형을 그리기
        draw(board, x1, y1, x2, y2);
        printBoard(board);
    }

    return 0;
}
