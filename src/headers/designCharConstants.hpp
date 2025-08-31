#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <array>

namespace HanoiTower {
    namespace GameElements {
        class DesignCharConstants {
        public:
            static const std::vector<std::string> Header;
            static const std::string DiskStartChar;
            static const std::string DiskMiddleChar;
            static const std::string DiskStructureChar;
            static const std::string DiskEndChar;
            static const std::string RodBaseChar;
            static const std::string RodChar;
            static const std::array<char, 3> RodLabels;
            static const std::string SpaceBetweenTowers;
            static const std::string LineBreak;
        };
    }
}
