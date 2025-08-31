// src/main.cpp — recommended
#include <iostream>
#include <locale>
#include "tower_of_hanoi.hpp"

using HanoiTower::TowerOfHanoi;

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::setlocale(LC_ALL, "");

#ifdef _WIN32
    enableWindowsVT();
#endif

    TowerOfHanoi::Play();
    return 0;
}
