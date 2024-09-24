#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE 30

// ���带 �ʱ�ȭ�ϴ� �Լ�
void Board(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

// ���带 ����ϴ� �Լ�
void printBoard(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << setw(2) << board[i][j];
        }
        cout << '\n';
    }
}

// �簢���� �׸��� �Լ� (�¿�� �Ѿ �� wrap-around ó��)
void draw(char board[][SIZE], int x1, int y1, int x2, int y2) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            int wrapX = (j + SIZE) % SIZE; // x���� ���� ũ��� ������ wrap-around
            int wrapY = (i + SIZE) % SIZE; // y�൵ ���������� ó��
            board[wrapY][wrapX] = '#'; // �簢���� '#'�� �׸���
        }
    }
}

// �簢���� ����� �Լ� (wrap-around ����)
void clear(char board[][SIZE], int x1, int y1, int x2, int y2) {
    for (int i = y1; i <= y2; i++) {
        for (int j = x1; j <= x2; j++) {
            int wrapX = (j + SIZE) % SIZE;
            int wrapY = (i + SIZE) % SIZE;
            board[wrapY][wrapX] = '.'; // �簢���� �����
        }
    }
}

int main() {
    char board[SIZE][SIZE];
    int x1, y1, x2, y2;
    char command;

    Board(board);

    cout << "�簢���� ��ǥ (x1, y1) (x2, y2)�� �Է��ϼ���: ";
    cin >> x1 >> y1 >> x2 >> y2;

    // ���忡 �簢�� �׸���
    draw(board, x1, y1, x2, y2);
    printBoard(board);

    while (true) {
        cout << "��ɾ� (x/X, y/Y, s/S, i/I, j/J, m, r, q): ";
        cin >> command;

        // ���� �簢���� ����
        clear(board, x1, y1, x2, y2);

        switch (command) {
        case 'x':  // x ���� ���������� �̵�
            x1 = (x1 + 1) % SIZE;
            x2 = (x2 + 1) % SIZE;
            break;
        case 'X':  // x ���� �������� �̵�
            x1 = (x1 - 1 + SIZE) % SIZE;
            x2 = (x2 - 1 + SIZE) % SIZE;
            break;
        case 'y':  // y ���� �Ʒ��� �̵�
            y1 = (y1 + 1) % SIZE;
            y2 = (y2 + 1) % SIZE;
            break;
        case 'Y':  // y ���� ���� �̵�
            y1 = (y1 - 1 + SIZE) % SIZE;
            y2 = (y2 - 1 + SIZE) % SIZE;
            break;
        case 's':  // �簢�� ���
            if (x1 < x2 && y1 < y2) {
                x2 = (x2 > 0) ? x2 - 1 : x2;
                y2 = (y2 > 0) ? y2 - 1 : y2;
            }
            break;
        case 'S':  // �簢�� Ȯ��
            x2 = (x2 < SIZE - 1) ? x2 + 1 : x2;
            y2 = (y2 < SIZE - 1) ? y2 + 1 : y2;
            break;
        case 'm':  // ���� �簢���� ��ǥ�� ���
            cout << "�簢�� ��ǥ: (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")\n";
            break;
        case 'r':  // ���ο� ��ǥ�� �Է¹޾� �簢���� �ٽ� �׸�
            cout << "�� ��ǥ (x1, y1) (x2, y2)�� �Է��ϼ���: ";
            cin >> x1 >> y1 >> x2 >> y2;
            break;
        case 'q':  // ���α׷� ����
            cout << "���α׷��� �����մϴ�.\n";
            return 0;
        default:
            cout << "��ȿ���� ���� ��ɾ��Դϴ�.\n";
            continue;
        }

        // ���ο� ��ġ�� �簢���� �׸���
        draw(board, x1, y1, x2, y2);
        printBoard(board);
    }

    return 0;
}
