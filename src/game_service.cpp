#include "game_service.hpp"
#include "disk.hpp"
#include "rod.hpp"
#include "design_char_constants.hpp"
#include "utils.hpp"
#include "color.hpp"

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <conio.h>   // for _getch() on Windows
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace HanoiTower {
    namespace Services {

        // Helper to convert stack to vector (since C++ stack has no ElementAt)
        static vector<int> stackToVector(stack<int> s) {
            vector<int> v;
            while (!s.empty()) {
                v.push_back(s.top());
                s.pop();
            }
            reverse(v.begin(), v.end()); // so bottom is first
            return v;
        }

        void GameService::PrintRods(stack<int> stack1, stack<int> stack2, stack<int> stack3, int noDisks) {
            using namespace HanoiTower::GameElements;

            Rod rod1(noDisks, 0);
            Rod rod2(noDisks, 1);
            Rod rod3(noDisks, 2);

            vector<int> v1 = stackToVector(stack1);
            vector<int> v2 = stackToVector(stack2);
            vector<int> v3 = stackToVector(stack3);

            int s1 = 0, s2 = 0, s3 = 0;

            for (int i = 1; i <= noDisks; i++) {
                string line;

                // Rod 1
                if (v1.empty() || i <= (noDisks - (int)v1.size())) {
                    line += ConstructLine(Space(noDisks * 2), DesignCharConstants::RodChar);
                } else {
                    Disk disk(v1[s1]);
                    line += ConstructLine(Space((noDisks * 2) - v1[s1]), disk.GetDisk());
                    s1++;
                }
                line += DesignCharConstants::SpaceBetweenTowers;

                // Rod 2
                if (v2.empty() || i <= (noDisks - (int)v2.size())) {
                    line += ConstructLine(Space(noDisks * 2), DesignCharConstants::RodChar);
                } else {
                    Disk disk(v2[s2]);
                    line += ConstructLine(Space((noDisks * 2) - v2[s2]), disk.GetDisk());
                    s2++;
                }
                line += DesignCharConstants::SpaceBetweenTowers;

                // Rod 3
                if (v3.empty() || i <= (noDisks - (int)v3.size())) {
                    line += ConstructLine(Space(noDisks * 2), DesignCharConstants::RodChar);
                } else {
                    Disk disk(v3[s3]);
                    line += ConstructLine(Space((noDisks * 2) - v3[s3]), disk.GetDisk());
                    s3++;
                }

                cout << line << endl;
            }

            // Print rod bases
            cout << rod1.RodBase() << DesignCharConstants::SpaceBetweenTowers
                      << rod2.RodBase() << DesignCharConstants::SpaceBetweenTowers
                      << rod3.RodBase() << endl;

            // Print rod labels (rough alignment)
            cout << rod1.Label() << DesignCharConstants::SpaceBetweenTowers
                      << rod2.Label() << DesignCharConstants::SpaceBetweenTowers
                      << rod3.Label() << endl;
        }

        void GameService::ClearPartOfConsole(int rowIndex) {
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD pos = { 0, (SHORT)rowIndex };
            SetConsoleCursorPosition(hConsole, pos);
            cout << string(120, ' ');
#endif
        }

        string GameService::ConstructLine(const string& space, const string& el) {
            return space + el + space;
        }

        string GameService::Space(int size) {
            return string(size, ' ');
        }

        int GameService::ReturnLabelIndex(char l) {
            for (size_t i = 0; i < DesignCharConstants::RodLabels.size(); i++) {
                if (DesignCharConstants::RodLabels[i] == l) return (int)i;
            }
            return -1;
        }

        stack<int> GameService::FillRod(int n) {
            stack<int> stack;
            for (int i = n; i > 0; i--) {
                stack.push(i);
            }
            return stack;
        }

        void GameService::YouWonText(const string& role) {
            cout << DesignCharConstants::LineBreak << endl << endl;
            cout << "> > > !!! " << role << "   W O N !!! < < <" << endl << endl;
        }

        void GameService::PrintHeader() {
            for (const auto& s : DesignCharConstants::Header) {
                cout << s << endl;
            }
            cout << endl << endl;
        }

        // TODO: SubMenu & SubMenuLoop → will require arrow key reading (_getch)
        int GameService::SubMenu() {
            cout << "\n\n> Please choose who do you want to play the game:\n";
            vector<string> items = { "○ The user", "○ The computer" };
            int selectedItemIndex = 0;
            int cursorY = 5; // You’d track where you started printing

            while (true) {
                move_cursor(0, cursorY);

                // Print menu
                for (int i = 0; i < items.size(); i++) {
                    if (i == selectedItemIndex) {
                        setTextColor(30); // black text
                        cout << BG_WHITE; // white background
                        items[i].replace(0, 1, "•");
                    } else {
                        items[i].replace(0, 1, "○");
                        setTextColor(37); // white text (default)
                        cout << BG_BLACK; // black background
                    }
                    cout << items[i] << endl;
                    cout << DEFAULT; // reset
                }

                // Input handling
                int key = getch();
                if (key == 72) { // up arrow
                    selectedItemIndex--;
                    if (selectedItemIndex < 0) selectedItemIndex = items.size() - 1;
                } else if (key == 80) { // down arrow
                    selectedItemIndex++;
                    if (selectedItemIndex >= items.size()) selectedItemIndex = 0;
                } else if (key == 13) { // Enter
                    return selectedItemIndex;
                }
            }
        }

        int GameService::SubMenuLoop() {
            cout << "Play again (stubbed)" << endl;
            return 0;
        }

        void GameService::ClearCurrentConsoleLine() {
            cout << "\r" << string(120, ' ') << "\r";
        }

        void GameService::ClearToEndOfCurrentLine() {
            cout << string(80, ' ');
        }
    }
}
