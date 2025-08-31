#pragma once

#include <stack>
#include <string>
#include <vector>

namespace HanoiTower {
    namespace Services {
        class GameService {
        public:
            static void PrintRods(std::stack<int> stack1, std::stack<int> stack2, std::stack<int> stack3, int noDisks);
            static void ClearPartOfConsole(int rowIndex);
            static int SubMenu();
            static int SubMenuLoop();
            static void ClearCurrentConsoleLine();
            static void ClearToEndOfCurrentLine();
            static int ReturnLabelIndex(char l);
            static std::stack<int> FillRod(int n);
            static void YouWonText(const std::string& role);
            static void PrintHeader();

        private:
            static std::string ConstructLine(const std::string& space, const std::string& el);
            static std::string Space(int size);
        };
    }
}
