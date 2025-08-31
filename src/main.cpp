// src/main.cpp — recommended
#include <iostream>
#include <locale>
#include "utils.hpp"
#include "tower_of_hanoi.hpp"

using HanoiTower::TowerOfHanoi;
using namespace std;

#ifdef _WIN32
#include <windows.h>
static void enableWindowsVT() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

void show_help() {
    cout << "Tower of Hanoi is a classic puzzle game where you move disks between rods!\n\n";
    cout << "Usage: ./hanoi [options]\n\n";
    cout << "Options:\n";
    cout << "  -h, --help     Show this help message\n\n";
    cout << "Controls:\n";
    cout << "  LEFT/RIGHT Arrows - Select a tower\n";
    cout << "  ENTER - Confirm source or destination tower\n";
    cout << "  Q/ESC - Quit the game\n\n";
    cout << "Game Modes:\n";
    cout << "  - User Mode: Manually move disks using arrow keys\n";
    cout << "  - Computer Mode: Watch the computer solve the puzzle automatically\n\n";
    cout << "I hope you're enjoying the game! Have a great day!\n\n";
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setlocale(LC_ALL, "");

#ifdef _WIN32
    enableWindowsVT();
#endif
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            show_help();
            return 0;
        }
    }

    TowerOfHanoi::Play();
    return 0;
}
