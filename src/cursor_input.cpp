#include "cursor_input.h"
#include "ultils.h"
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

    // Set read() to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    InputKey key = InputKey::NONE;
    char ch;

    while (true)
    {
        if (read(STDIN_FILENO, &ch, 1) == 1) { // Arrow key escape sequence
            if (ch == '\033') {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) == 1 && 
                    read(STDIN_FILENO, &seq[1], 1) == 1) {
                    switch (seq[1]) {
                        case 'A': return InputKey::UP;
                        case 'B': return InputKey::DOWN;
                        case 'C': return InputKey::RIGHT;
                        case 'D': return InputKey::LEFT;
                    }
                }
            } else {
                switch (ch) {
                    case 'w': case 'W': return InputKey::UP;
                    case 's': case 'S': return InputKey::DOWN;
                    case 'a': case 'A': return InputKey::LEFT;
                    case 'd': case 'D': return InputKey::RIGHT;
                    case '\n': return InputKey::ENTER;
                    case 27:   return InputKey::ESC; // Escape
                    case 'q': case 'Q': return InputKey::Q; // Quit to menu
                    case 'r': case 'R': return InputKey::R; // Restart game
                    case '[': return InputKey::LEFT_BRACKET; // '[' key
                    case ']': return InputKey::RIGHT_BRACKET; // ']' key
                    default:   return InputKey::NONE;
                }
            }

            if (key != InputKey::NONE) {
                break;
            }

        }
        usleep(1000); // Sleep for a short time to avoid busy waiting
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original settings
    fcntl(STDIN_FILENO, F_SETFL, 0); // Restore blocking mode
    
    return key;
}

void playSound(SoundEffect effect) {
    switch (effect) {
        case CLICK:   system("aplay sounds/click.wav &"); break;
        case VICTORY: system("aplay sounds/victory.wav &"); break;
        case DEFEAT:  system("aplay sounds/defeat.wav &"); break;
    }
}

