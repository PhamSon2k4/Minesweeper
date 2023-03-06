#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 10;

void printBoard(int board[MAX_SIZE][MAX_SIZE], bool revealed[MAX_SIZE][MAX_SIZE], int m, int n) {
    cout << endl;
    cout << "  ";
    for (int j = 0; j < n; ++j) {
        cout << j << " ";
    }
    cout << endl;
    for (int i = 0; i < m; ++i) {
        cout << i << " ";
        for (int j = 0; j < n; ++j) {
            if (revealed[i][j]) {
                if (board[i][j] == -1) {
                    cout << "* ";
                } else {
                    cout << board[i][j] << " ";
                }
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int countMines(int board[MAX_SIZE][MAX_SIZE], int x, int y, int m, int n) {
    int count = 0;
    for (int i = max(0, x - 1); i <= min(m - 1, x + 1); ++i) {
        for (int j = max(0, y - 1); j <= min(n - 1, y + 1); ++j) {
            if (board[i][j] == -1) {
                ++count;
            }
        }
    }
    return count;
}

void floodFill(int board[MAX_SIZE][MAX_SIZE], bool revealed[MAX_SIZE][MAX_SIZE], int x, int y, int m, int n) {
    if (x < 0 || x >= m || y < 0 || y >= n || revealed[x][y]) {
        return;
    }
    revealed[x][y] = true;
    if (board[x][y] != 0) {
        return;
    }
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            floodFill(board, revealed, i, j, m, n);
        }
    }
}

int main() {
    int m, n, k;
    cout << "Enter m, n, k: ";
    cin >> m >> n >> k;

    // Initialize board with all 0's
    int board[MAX_SIZE][MAX_SIZE] = {};
    bool revealed[MAX_SIZE][MAX_SIZE] = {};

    // Plant k mines randomly
    srand(time(NULL));
    int count = 0;
    while (count < k) {
        int i = rand() % m;
        int j = rand() % n;
        if (board[i][j] == 0) {
            board[i][j] = -1;
            ++count;
        }
    }

    bool gameover = false;
    while (!gameover) {
        printBoard(board, revealed, m, n);
        int x, y;
        cout << "Enter x, y: ";
        cin >> x >> y;
            if (board[x][y] == -1) {
        cout << "YOU'RE DEAD!" << endl;
        gameover = true;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                revealed[i][j] = true;
            }
        }
        printBoard(board, revealed, m, n);
        break;
    } else {
        revealed[x][y] = true;
        if (board[x][y] == 0) {
            floodFill(board, revealed, x, y, m, n);
        }
        int num_revealed = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (revealed[i][j]) {
                    ++num_revealed;
                }
            }
        }
        if (num_revealed == m * n - k) {
            cout << "YOU WIN!" << endl;
            gameover = true;
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    revealed[i][j] = true;
                }
            }
            printBoard(board, revealed, m, n);
            break;
        }
    }
}
    return 0;
}

               
