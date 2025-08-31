#include "tower_of_hanoi.hpp"
#include "game_service.hpp"            // adjust include path to your layout
#include "log_service.hpp"
#include "design_char_constants.hpp"
#include "utils.hpp"                         // your utils: clearScreen, sleep_ms, getch, etc.
#include "color.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

namespace HanoiTower {

    // Static member definitions
    int TowerOfHanoi::noDisks = 0;
    vector<string> TowerOfHanoi::moves = {};

    void TowerOfHanoi::Play() {
        // Use UTF-8 output if needed on platforms that support it (no-op on many systems)
        // Clear and print header
        clearScreen();
        Services::GameService::PrintHeader();

        string input;
        // ask until we get a valid integer
        while (true) {
            cout << "> Please write the number of disks you want to start with: ";
            if (!getline(cin, input)) return; // EOF protection
            // trim leading/trailing whitespace
            istringstream iss(input);
            int parsed = 0;
            if ((iss >> parsed) && parsed > 0) {
                noDisks = parsed;
                break;
            }
            // otherwise loop again
        }

        TheGame();
    }

    void TowerOfHanoi::TheGame() {
        clearScreen();
        moves.clear();
        Services::GameService::PrintHeader();

        // Define the 3 rods
        array<stack<int>, 3> rods;
        rods[0] = Services::GameService::FillRod(noDisks);
        rods[1] = stack<int>();
        rods[2] = stack<int>();

        // Print initial state
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

        // Mode selection
        int mode = Services::GameService::SubMenu();

        clearScreen();
        Services::GameService::PrintHeader();
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

        if (mode == 0) {
            UserPlay(rods);
        } else {
            // Pass references so solver mutates the real rods
            ComputerPlay(noDisks, rods[0], rods[1], rods[2]);
        }

        // Play again?
        int playAgain = Services::GameService::SubMenuLoop();
        if (playAgain == 0) {
            Play(); // restart
        } else {
            // clean exit
            clearScreen();
            // On some systems you may want to flush output explicitly
            cout.flush();
            exit(0);
        }
    }

    void TowerOfHanoi::UserPlay(array<stack<int>, 3>& rods) {
        int noSteps = 0;
        string input;

        while (true) {
            char k1 = ' ';
            char k2 = ' ';
            cout << GameElements::DesignCharConstants::LineBreak << "\n";
            cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n\n";

            cout << "> Move disk from tower: ";
            if (!getline(cin, input)) break;
            if (input == "exit" || input == "EXIT") break;
            if (input.empty()) continue;
            k1 = input[0];

            cout << "> Move disk to tower: ";
            if (!getline(cin, input)) break;
            if (input == "exit" || input == "EXIT") break;
            if (input.empty()) continue;
            k2 = input[0];

            moves.push_back(string(1, k1) + " -> " + string(1, k2));

            int in1 = Services::GameService::ReturnLabelIndex(k1);
            int in2 = Services::GameService::ReturnLabelIndex(k2);

            // redraw
            clearScreen();
            Services::GameService::PrintHeader();

            string error;
            if (in1 == -1 || in2 == -1) {
                Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);
                error = "!!! Invalid input for tower !!!";
                cout << GameElements::DesignCharConstants::LineBreak << "\n";
                cout << error << "\n";
                moves.push_back(error);
                noSteps++;
            }
            else if (in1 == in2) {
                Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);
                error = "!!! You can't take and move disks from the same tower !!!";
                cout << GameElements::DesignCharConstants::LineBreak << "\n";
                cout << error << "\n";
                moves.push_back(error);
                noSteps++;
            }
            else {
                // valid indices
                if (rods[in1].size() > 0) {
                    int topDisk = rods[in1].top();
                    if (rods[in2].empty()) {
                        rods[in1].pop();
                        rods[in2].push(topDisk);
                    } else {
                        if (rods[in2].top() > topDisk) {
                            rods[in1].pop();
                            rods[in2].push(topDisk);
                        } else {
                            error = "!!! You can't move bigger on top of a smaller disk !!!";
                        }
                    }
                } else {
                    error = "!!! You can't take disk from an empty tower !!!";
                }

                Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);
                if (!error.empty()) {
                    cout << GameElements::DesignCharConstants::LineBreak << "\n";
                    cout << error << "\n";
                    moves.push_back(error);
                }

                noSteps++;

                // win condition: all disks on rod 3 (index 2)
                if ((int)rods[2].size() == noDisks) {
                    cout << GameElements::DesignCharConstants::LineBreak << "\n";
                    cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n";
                    Services::GameService::YouWonText("Y O U");
                    Services::LogService::ToFileShort(moves, "User", noDisks, noSteps);
                    break;
                }
            }
        } // end loop
    }

    void TowerOfHanoi::ComputerPlay(int n, stack<int>& source, stack<int>& auxiliary, stack<int>& destination) {
        // Choose algorithm variant based on parity to match original
        if (noDisks % 2 == 0) {
            SolveAutomatically(noDisks, source, destination, auxiliary);
        } else {
            SolveAutomatically(noDisks, source, auxiliary, destination);
        }
    }

    void TowerOfHanoi::SolveAutomatically(int n, stack<int>& source, stack<int>& auxiliary, stack<int>& destination) {
        int noSteps = 1;
        cout << GameElements::DesignCharConstants::LineBreak << "\n";
        cout << "# 0\t No.Disks: " << noDisks << "\n";
        sleep_ms(1000);

        int step1 = 0, step2 = 0;
        int totalMoves = (int)pow(2, n) - 1;
        for (int i = 1; i <= totalMoves; ++i) {
            if (i % 3 == 1) {
                if (noDisks % 2 == 0) { step1 = 1; step2 = 2; }
                else { step1 = 1; step2 = 3; }
                MoveDisk(source, destination, step1, step2);
            } else if (i % 3 == 2) {
                if (noDisks % 2 == 0) { step1 = 1; step2 = 3; }
                else { step1 = 1; step2 = 2; }
                MoveDisk(source, auxiliary, step1, step2);
            } else { // i % 3 == 0
                if (noDisks % 2 == 0) { step1 = 2; step2 = 3; }
                else { step1 = 3; step2 = 2; }
                MoveDisk(destination, auxiliary, step1, step2);
            }

            Services::GameService::ClearPartOfConsole(4);
            // Print in the needed order similar to original parity logic
            if (noDisks % 2 == 0)
                Services::GameService::PrintRods(source, destination, auxiliary, noDisks);
            else
                Services::GameService::PrintRods(source, auxiliary, destination, noDisks);

            cout << GameElements::DesignCharConstants::LineBreak << "\n";
            cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n";
            noSteps++;
            sleep_ms(1000);
        }

        Services::GameService::YouWonText("T H E   C O M P U T E R");
        Services::LogService::ToFileShort(moves, "Computer", noDisks, (int)noSteps - 1);
    }

    void TowerOfHanoi::MoveDisk(stack<int>& source, stack<int>& destination, int s1, int s2) {
        // follow the same rules as C# MoveDisk
        if (destination.empty()) {
            int disk = source.top(); source.pop();
            destination.push(disk);
            moves.push_back(to_string(s1) + " -> " + to_string(s2));
        }
        else if (source.empty()) {
            int disk = destination.top(); destination.pop();
            source.push(disk);
            moves.push_back(to_string(s2) + " -> " + to_string(s1));
        }
        else if (destination.top() < source.top()) {
            int disk = destination.top(); destination.pop();
            source.push(disk);
            moves.push_back(to_string(s2) + " -> " + to_string(s1));
        }
        else if (destination.top() > source.top()) {
            int disk = source.top(); source.pop();
            destination.push(disk);
            moves.push_back(to_string(s1) + " -> " + to_string(s2));
        }
    }

} // namespace HanoiTower
