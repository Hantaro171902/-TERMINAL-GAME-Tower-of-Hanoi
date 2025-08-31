#include "tower_of_hanoi.hpp"
#include "game_service.hpp"
#include "log_service.hpp"
#include "design_char_constants.hpp"
#include "utils.hpp"
#include "color.hpp"
#include "cursor_input.hpp"

#include <iostream>
#include <cmath>
#include <stack>
#include <array>
#include <vector>
#include <string>
#include <limits>
#include <map>

using namespace std;

namespace HanoiTower {

    // Static members
    int TowerOfHanoi::noDisks = 0;
    vector<string> TowerOfHanoi::moves = {};

    // ------------------- Play -------------------
    void TowerOfHanoi::Play() {
        clearTerminal();
        clearScreen();
        Services::GameService::PrintHeader();

        // Ask user for number of disks
        while (true) {
            cout << "> Enter the number of disks: " << flush;
            cin >> noDisks;

            if (!cin.fail() && noDisks > 0) break;

            // Reset bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive integer.\n" << flush;
        }
        
        TheGame();
    }

    // ------------------- The Game -------------------
    void TowerOfHanoi::TheGame() {
        moves.clear();
        Services::GameService::PrintHeader();

        // Init rods
        array<stack<int>, 3> rods;
        rods[0] = Services::GameService::FillRod(noDisks);
        rods[1] = stack<int>();
        rods[2] = stack<int>();

        // Mode selection
        int mode = Services::GameService::SubMenu();

        if (mode == 0) {
            UserPlay(rods);
        } else {
            ComputerPlay(rods);
        }

        // Replay loop
        int playAgain = Services::GameService::SubMenuLoop();
        if (playAgain == 0) {
            Play(); // restart
        } else {
            // clearScreen();
            cout << "Thanks for playing!\n" << flush;
            exit(0);
        }
    }
    
    // ------------------- User Play -------------------
    void TowerOfHanoi::UserPlay(array<stack<int>, 3>& rods) {
        int noSteps = 0;
        int selectedRodIndex = 0;
        int fromRodIndex = -1;

        while (true) {
            Services::GameService::PrintHeader();
            Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks, selectedRodIndex);
            cout << GameElements::DesignCharConstants::LineBreak << "\n" << flush;
            cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n\n" << flush;

            if (fromRodIndex == -1) {
                cout << "> Select a source tower using LEFT/RIGHT arrows. Press ENTER to select.\n" << flush;
            } else {
                cout << "> Move disk from tower " << (fromRodIndex + 1) << ". Select a destination tower. Press ENTER to confirm.\n" << flush;
            }

            InputKey k = getInputKey();
            
            switch (k) {
                case InputKey::LEFT:
                    selectedRodIndex = (selectedRodIndex - 1 + 3) % 3;
                    break;
                case InputKey::RIGHT:
                    selectedRodIndex = (selectedRodIndex + 1) % 3;
                    break;
                case InputKey::ENTER:
                    if (fromRodIndex == -1) {
                        fromRodIndex = selectedRodIndex;
                    } else {
                        int toRodIndex = selectedRodIndex;
                        string error;
                        
                        if (fromRodIndex == toRodIndex) {
                            error = "!!! Source and destination towers must be different !!!";
                        } else if (rods[fromRodIndex].empty()) {
                            error = "!!! Source tower is empty !!!";
                        } else {
                            int topDisk = rods[fromRodIndex].top();
                            if (rods[toRodIndex].empty() || rods[toRodIndex].top() > topDisk) {
                                rods[fromRodIndex].pop();
                                rods[toRodIndex].push(topDisk);
                                noSteps++;
                                moves.push_back(to_string(fromRodIndex + 1) + " -> " + to_string(toRodIndex + 1));
                                fromRodIndex = -1; // Reset only after successful move
                            } else {
                                error = "!!! Cannot place a larger disk on a smaller one !!!";
                            }
                        }
                        
                        if (!error.empty()) {
                            cout << GameElements::DesignCharConstants::LineBreak << "\n" << error << "\n" << flush;
                            sleep_ms(2000);
                        }
                    }
                    break;
                case InputKey::Q:
                case InputKey::ESC:
                    cout << "Exiting game...\n" << flush;
                    return;
                default:
                    break;
            }

            // Win check
            if ((int)rods[2].size() == noDisks) {
                Services::GameService::PrintHeader();
                Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);
                cout << GameElements::DesignCharConstants::LineBreak << "\n" << flush;
                cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n" << flush;
                Services::GameService::YouWonText("Y O U");
                Services::LogService::ToFileShort(moves, "User", noDisks, noSteps);
                sleep_ms(3000);
                break;
            }
        }
    }


    // ------------------- Computer Play -------------------
    void TowerOfHanoi::ComputerPlay(array<stack<int>, 3>& rods) {
        Services::GameService::PrintHeader();
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

        cout << GameElements::DesignCharConstants::LineBreak << "\n" << flush;
        cout << "# 0\t No.Disks: " << noDisks << "\n" << flush;
        cout << "The computer will now play the game automatically.\n" << flush;
        sleep_ms(3000);

        int noSteps = 0;
        SolveAutomatically(noDisks, rods[0], rods[2], rods[1], noSteps, rods);
        
        Services::GameService::YouWonText("T H E   C O M P U T E R");
        Services::LogService::ToFileShort(moves, "Computer", noDisks, noSteps);
        sleep_ms(3000);
    }
    
    // ------------------- Recursive Solution -------------------
    void TowerOfHanoi::SolveAutomatically(int n, stack<int>& source, stack<int>& destination, stack<int>& auxiliary, int& noSteps, array<stack<int>, 3>& rods) {
        if (n > 0) {
            SolveAutomatically(n - 1, source, auxiliary, destination, noSteps, rods);

            moveDiskWithPrint(source, destination, noSteps, rods);
            
            SolveAutomatically(n - 1, auxiliary, destination, source, noSteps, rods);
        }
    }

    // ------------------- Move Disk with Print -------------------
    void TowerOfHanoi::moveDiskWithPrint(stack<int>& source, stack<int>& destination, int& noSteps, array<stack<int>, 3>& rods) {
        if (source.empty()) {
            return;
        }

        int disk = source.top(); source.pop();
        destination.push(disk);

        noSteps++;
        
        Services::GameService::PrintHeader();
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);
        
        // Find the correct labels for the moved disk based on the original rod positions.
        char sourceLabel = ' ';
        char destLabel = ' ';
        if (&source == &rods[0]) sourceLabel = GameElements::DesignCharConstants::RodLabels[0];
        else if (&source == &rods[1]) sourceLabel = GameElements::DesignCharConstants::RodLabels[1];
        else if (&source == &rods[2]) sourceLabel = GameElements::DesignCharConstants::RodLabels[2];

        if (&destination == &rods[0]) destLabel = GameElements::DesignCharConstants::RodLabels[0];
        else if (&destination == &rods[1]) destLabel = GameElements::DesignCharConstants::RodLabels[1];
        else if (&destination == &rods[2]) destLabel = GameElements::DesignCharConstants::RodLabels[2];

        moves.push_back("Move disk " + to_string(disk) + " from " + string(1, sourceLabel) + " to " + string(1, destLabel));

        cout << GameElements::DesignCharConstants::LineBreak << "\n" << flush;
        cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n" << flush;
        sleep_ms(500); // 500ms delay to make the moves visible
    }

} // namespace HanoiTower