#pragma once

#include <array>
#include <stack>
#include <string>
#include <vector>

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
        static void ComputerPlay(int n, std::stack<int>& source, std::stack<int>& auxiliary, std::stack<int>& destination);

        // Automatic solver & helpers
        static void SolveAutomatically(int n, std::stack<int>& source, std::stack<int>& auxiliary, std::stack<int>& destination);
        static void MoveDisk(std::stack<int>& source, std::stack<int>& destination, int s1, int s2);
    };

} // namespace HanoiTower
