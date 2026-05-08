// 05-mini-projects/ascii-animation/main.cpp
// terminal ascii animations -- windows compatible
// compile: g++ -std=c++11 main.cpp -o animation && animation

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void enableAnsi() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    if (GetConsoleMode(hOut, &mode)) {
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif
}

void hideCursor() {
    std::cout << "\033[?25l";
}

void showCursor() {
    std::cout << "\033[?25h";
}

void moveTo(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// 1. spinner

void spinnerDemo(int iterations = 40) {
    const std::string frames = "|/-\\";

    std::cout << "\n  loading ";

    for (int i = 0; i < iterations; i++) {
        std::cout << frames[i % 4] << std::flush;
        sleep_ms(80);
        std::cout << "\b";
    }

    std::cout << "done!\n\n";
}

// 2. progress bar

void progressBar(int total = 40) {
    const int width = 30;

    std::cout << "\n";

    for (int i = 0; i <= total; i++) {
        int filled = (i * width) / total;
        int pct = (i * 100) / total;

        std::cout << "\r  [";

        for (int j = 0; j < width; j++) {
            std::cout << (j < filled ? "#" : "-");
        }

        std::cout << "] " << pct << "%" << std::flush;

        sleep_ms(60);
    }

    std::cout << "\n  complete!\n\n";
}

// 3. bouncing ball

void bouncingBall(int frames = 100) {
    const int W = 50;
    const int H = 12;

    double bx = W / 2.0;
    double by = H / 2.0;
    double vx = 0.9;
    double vy = 0.5;

    clearScreen();
    hideCursor();

    for (int f = 0; f < frames; f++) {
        moveTo(1, 1);
        std::cout << "+" << std::string(W, '-') << "+";

        for (int r = 2; r < H + 2; r++) {
            moveTo(r, 1);
            std::cout << "|" << std::string(W, ' ') << "|";
        }

        moveTo(H + 2, 1);
        std::cout << "+" << std::string(W, '-') << "+";

        moveTo((int)by + 1, (int)bx + 1);
        std::cout << "O";

        bx += vx;
        by += vy;

        if (bx <= 1 || bx >= W - 1) {
            vx = -vx;
        }

        if (by <= 1 || by >= H - 1) {
            vy = -vy;
        }

        std::cout << std::flush;
        sleep_ms(40);
    }

    showCursor();
    moveTo(H + 4, 1);
    std::cout << "\n  finished.\n\n";
}

// 4. matrix rain

void matrixRain(int frames = 80) {
    const int COLS = 60;
    const int ROWS = 20;
    const std::string CHARS = "abcdefghijklmnopqrstuvwxyz0123456789@#$%&";

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> charDist(0, (int)CHARS.size() - 1);
    std::uniform_int_distribution<int> colDist(0, COLS - 1);

    std::vector<int> drops(COLS, -1);
    std::vector<std::vector<char>> screen(
        ROWS,
        std::vector<char>(COLS, ' ')
    );

    clearScreen();
    hideCursor();

    for (int f = 0; f < frames; f++) {
        if (rng() % 3 == 0) {
            int col = colDist(rng);

            if (drops[col] == -1) {
                drops[col] = 0;
            }
        }

        for (int c = 0; c < COLS; c++) {
            if (drops[c] >= 0) {
                if (drops[c] < ROWS) {
                    screen[drops[c]][c] = CHARS[charDist(rng)];
                    drops[c]++;
                }
                else {
                    for (int r = 0; r < ROWS; r++) {
                        screen[r][c] = ' ';
                    }

                    drops[c] = -1;
                }
            }
        }

        for (int r = 0; r < ROWS; r++) {
            moveTo(r + 1, 1);
            std::cout << "\033[32m";

            for (int c = 0; c < COLS; c++) {
                std::cout << screen[r][c];
            }

            std::cout << "\033[0m";
        }

        std::cout << std::flush;
        sleep_ms(80);
    }

    showCursor();
    moveTo(ROWS + 3, 1);
    std::cout << "\n  finished.\n\n";
}

// main

int main() {
    enableAnsi();

    std::cout << "\n  ascii-animation\n";
    std::cout << "  ----------------\n";
    std::cout << "  1. spinner\n";
    std::cout << "  2. progress bar\n";
    std::cout << "  3. bouncing ball\n";
    std::cout << "  4. matrix rain\n";
    std::cout << "\n  pick [1-4]: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        spinnerDemo();
        break;

    case 2:
        progressBar();
        break;

    case 3:
        bouncingBall();
        break;

    case 4:
        matrixRain();
        break;

    default:
        std::cout << "  invalid choice\n";
        break;
    }

    std::cout << "  press enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}