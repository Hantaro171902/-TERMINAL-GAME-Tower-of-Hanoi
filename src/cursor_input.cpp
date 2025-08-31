#include "cursor_input.hpp"
#include "utils.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>     // for read()
#include <fcntl.h>      // for fcntl()

using namespace std;

InputKey getInputKey() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    InputKey key = InputKey::NONE;
    char ch;

    // Use a single blocking read to wait for a keypress
    read(STDIN_FILENO, &ch, 1);

    if (ch == '\033') {
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);
        switch (seq[1]) {
            case 'A': key = InputKey::UP; break;
            case 'B': key = InputKey::DOWN; break;
            case 'C': key = InputKey::RIGHT; break;
            case 'D': key = InputKey::LEFT; break;
        }
    } else {
        switch (ch) {
            case 'w': case 'W': key = InputKey::UP; break;
            case 's': case 'S': key = InputKey::DOWN; break;
            case 'a': case 'A': key = InputKey::LEFT; break;
            case 'd': case 'D': key = InputKey::RIGHT; break;
            case '\n': key = InputKey::ENTER; break;
            case 27:   key = InputKey::ESC; break;
            case 'q': case 'Q': key = InputKey::Q; break;
            case 'r': case 'R': key = InputKey::R; break;
            case '[': key = InputKey::LEFT_BRACKET; break;
            case ']': key = InputKey::RIGHT_BRACKET; break;
            default:   key = InputKey::NONE; break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    return key;
}

// void playSound(SoundEffect effect) {
//     switch (effect) {
//         case CLICK:   system("aplay sounds/click.wav &"); break;
//         case VICTORY: system("aplay sounds/victory.wav &"); break;
//         case DEFEAT:  system("aplay sounds/defeat.wav &"); break;
//     }
// }