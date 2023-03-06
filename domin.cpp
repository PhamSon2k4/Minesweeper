#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX_SIZE = 10;

void initBoard(bool board[][MAX_SIZE], int m, int n, int k) {
    // Khởi tạo bản đồ với tất cả các ô không có mìn
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = false;
        }
    }
    
    // Đặt ngẫu nhiên K quả mìn trên bản đồ
    int placed = 0;
    while (placed < k) {
        int x = rand() % m;
        int y = rand() % n;
        if (!board[x][y]) {
            board[x][y] = true;
            placed++;
        }
    }
}

void printBoard(bool board[][MAX_SIZE], bool revealed[][MAX_SIZE], int m, int n) {
    cout << endl;
    
    // In đầu dòng
    cout << "   ";
    for (int j = 0; j < n; j++) {
        cout << j << " ";
    }
    cout << endl;
    
    // In bản đồ và các số
    for (int i = 0; i < m; i++) {
        cout << i << "  ";
        for (int j = 0; j < n; j++) {
            if (!revealed[i][j]) {
                cout << "- ";
            } else if (board[i][j]) {
                cout << "* ";
            } else {
                int count = 0;
                if (i > 0 && j > 0 && board[i-1][j-1]) count++;
                if (i > 0 && board[i-1][j]) count++;
                if (i > 0 && j < n-1 && board[i-1][j+1]) count++;
                if (j > 0 && board[i][j-1]) count++;
                if (j < n-1 && board[i][j+1]) count++;
                if (i < m-1 && j > 0 && board[i+1][j-1]) count++;
                if (i < m-1 && board[i+1][j]) count++;
                if (i < m-1 && j < n-1 && board[i+1][j+1]) count++;
                cout << count << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Khởi tạo random seed

    int m, n, k;
    cout << "Enter board size (m n) and number of mines (k): ";
    cin >> m >> n >> k;
    
    bool board[MAX_SIZE][MAX_SIZE];
    bool revealed[MAX_SIZE][MAX_SIZE] = {false};
    
    initBoard(board, m, n, k);
    printBoard(board, revealed, m, n);
    
    int x, y;
    while (true) {
        cout << "Enter a coordinate (x y): ";
        cin >> x >> y;
        
        if (board[x][y]) {
            cout << "YOU'RE DEAD!" << endl;
            revealed[x][y] = true;
            printBoard(board, revealed, m, n);
            break;
        } else {
            revealed[x][y] = true;
        	printBoard(board, revealed, m, n);
        
        // Kiểm tra xem đã mở hết các ô không có mìn chưa
        bool allRevealed = true;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!board[i][j] && !revealed[i][j]) {
                    allRevealed = false;
                }
            }
        }
        if (allRevealed) {
            cout << "Congratulations, you won!" << endl;
            break;
        }
    }
}

return 0;
}
