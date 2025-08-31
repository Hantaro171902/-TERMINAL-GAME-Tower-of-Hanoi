#include "tower_of_hanoi.hpp"
#include "game_service.hpp"
#include "log_service.hpp"
#include "design_char_constants.hpp"
#include "utils.hpp"
#include "color.hpp"

#include <iostream>
#include <cmath>
#include <stack>
#include <array>
#include <vector>
#include <string>

using namespace std;

namespace HanoiTower {

    // Static members
    int TowerOfHanoi::noDisks = 0;
    vector<string> TowerOfHanoi::moves = {};

    // ------------------- Play -------------------
    void TowerOfHanoi::Play() {
        clearScreen();
        Services::GameService::PrintHeader();

        // Ask user for number of disks
        while (true) {
            cout << "> Enter the number of disks: ";
            cin >> noDisks;

            if (!cin.fail() && noDisks > 0) break;

            // Reset bad input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive integer.\n";
        }

        TheGame();
    }

    // ------------------- The Game -------------------
    void TowerOfHanoi::TheGame() {
        clearScreen();
        moves.clear();
        Services::GameService::PrintHeader();

        // Init rods
        array<stack<int>, 3> rods;
        rods[0] = Services::GameService::FillRod(noDisks);
        rods[1] = stack<int>();
        rods[2] = stack<int>();

        // Initial state
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

        // Mode selection
        int mode = Services::GameService::SubMenu();

        clearScreen();
        Services::GameService::PrintHeader();
        Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

        if (mode == 0) {
            UserPlay(rods);
        } else {
            ComputerPlay(noDisks, rods[0], rods[1], rods[2]);
        }

        // Replay loop
        int playAgain = Services::GameService::SubMenuLoop();
        if (playAgain == 0) {
            Play(); // restart
        } else {
            clearScreen();
            cout << "Thanks for playing!\n";
            exit(0);
        }
    }

    // ------------------- User Play -------------------
    void TowerOfHanoi::UserPlay(array<stack<int>, 3>& rods) {
        int noSteps = 0;

        while (true) {
            char fromTower, toTower;

            cout << GameElements::DesignCharConstants::LineBreak << "\n";
            cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n\n";

            cout << "> Move disk from tower (A/B/C or 'exit'): ";
            cin >> fromTower;
            if (tolower(fromTower) == 'e') break;

            cout << "> Move disk to tower (A/B/C or 'exit'): ";
            cin >> toTower;
            if (tolower(toTower) == 'e') break;

            moves.push_back(string(1, fromTower) + " -> " + string(1, toTower));

            int in1 = Services::GameService::ReturnLabelIndex(fromTower);
            int in2 = Services::GameService::ReturnLabelIndex(toTower);

            clearScreen();
            Services::GameService::PrintHeader();

            string error;
            if (in1 == -1 || in2 == -1) {
                error = "!!! Invalid tower label !!!";
            }
            else if (in1 == in2) {
                error = "!!! Source and destination towers must be different !!!";
            }
            else if (rods[in1].empty()) {
                error = "!!! Source tower is empty !!!";
            }
            else {
                int topDisk = rods[in1].top();
                if (rods[in2].empty() || rods[in2].top() > topDisk) {
                    rods[in1].pop();
                    rods[in2].push(topDisk);
                } else {
                    error = "!!! Cannot place bigger disk on smaller one !!!";
                }
            }

            // Print rods
            Services::GameService::PrintRods(rods[0], rods[1], rods[2], noDisks);

            if (!error.empty()) {
                cout << GameElements::DesignCharConstants::LineBreak << "\n" << error << "\n";
                moves.push_back(error);
            }

            noSteps++;

            // Win check
            if ((int)rods[2].size() == noDisks) {
                cout << GameElements::DesignCharConstants::LineBreak << "\n";
                cout << "# " << noSteps << "\t No.Disks: " << noDisks << "\n";
                Services::GameService::YouWonText("Y O U");
                Services::LogService::ToFileShort(moves, "User", noDisks, noSteps);
                break;
            }
        }
    }

    // ------------------- Computer Play -------------------
    void TowerOfHanoi::ComputerPlay(int n, stack<int>& source, stack<int>& auxiliary, stack<int>& destination) {
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
            }
            else if (i % 3 == 2) {
                if (noDisks % 2 == 0) { step1 = 1; step2 = 3; }
                else { step1 = 1; step2 = 2; }
                MoveDisk(source, auxiliary, step1, step2);
            }
            else {
                if (noDisks % 2 == 0) { step1 = 2; step2 = 3; }
                else { step1 = 3; step2 = 2; }
                MoveDisk(destination, auxiliary, step1, step2);
            }

            Services::GameService::ClearPartOfConsole(4);

            if (noDisks % 2 == 0)
                Services::GameService::PrintRods(source, destination, auxiliary, noDisks);
            else
                Services::GameService::PrintRods(source, auxiliary, destination, noDisks);

            cout << GameElements::DesignCharConstants::LineBreak << "\n";
            cout << "# " << noSteps++ << "\t No.Disks: " << noDisks << "\n";
            sleep_ms(1000);
        }

        Services::GameService::YouWonText("T H E   C O M P U T E R");
        Services::LogService::ToFileShort(moves, "Computer", noDisks, noSteps - 1);
    }

    // ------------------- Move Disk -------------------
    void TowerOfHanoi::MoveDisk(stack<int>& source, stack<int>& destination, int s1, int s2) {
        if (!source.empty() && (destination.empty() || destination.top() > source.top())) {
            int disk = source.top(); source.pop();
            destination.push(disk);
            moves.push_back(to_string(s1) + " -> " + to_string(s2));
        }
        else if (!destination.empty() && (source.empty() || source.top() > destination.top())) {
            int disk = destination.top(); destination.pop();
            source.push(disk);
            moves.push_back(to_string(s2) + " -> " + to_string(s1));
        }
    }

} // namespace HanoiTower
