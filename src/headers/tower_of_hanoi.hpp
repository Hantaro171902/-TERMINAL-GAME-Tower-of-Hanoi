#pragma once

#include <array>
#include <stack>
#include <string>
#include <vector>
#include <map>

namespace HanoiTower {

    class TowerOfHanoi {
    public:
        // Entry point
        static void Play();

    private:
        // State
        static int noDisks;
        static std::vector<std::string> moves;

        // Flow
        static void TheGame();

        // User flow
        static void UserPlay(std::array<std::stack<int>, 3>& rods);

        // Computer flow
        static void ComputerPlay(std::array<std::stack<int>, 3>& rods);

        // Automatic solver & helpers
        static void SolveAutomatically(int n, std::stack<int>& source, std::stack<int>& destination, std::stack<int>& auxiliary, int& noSteps, std::array<std::stack<int>, 3>& rods);
        static void moveDiskWithPrint(std::stack<int>& source, std::stack<int>& destination, int& noSteps, std::array<std::stack<int>, 3>& rods);
    };

} // namespace HanoiTower