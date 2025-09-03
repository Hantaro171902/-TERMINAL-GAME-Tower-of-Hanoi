#include "design_char_constants.hpp"
#include "color.hpp"
#include <iostream>

using namespace std;

namespace HanoiTower {
    namespace GameElements {

        const vector<string> DesignCharConstants::Header = {
            "\t _______  _____  _  _  _ _______  ______       _____  _______      _     _ _______ __   _  _____  _____",
            "\t    |    |     | |  |  | |______ |_____/      |     | |______      |_____| |_____| | \\  | |     |   |  ",
            "\t    |    |_____| |__|__| |______ |    \\_      |_____| |            |     | |     | |  \\_| |_____| __|__"
        };

        const string DesignCharConstants::DiskStartChar      = "«";
        const string DesignCharConstants::DiskMiddleChar     = "¦";
        const string DesignCharConstants::DiskStructureChar  = "=";
        const string DesignCharConstants::DiskEndChar        = "»";
        const string DesignCharConstants::RodBaseChar        = "▀";
        const string DesignCharConstants::RodChar            = "│";
        const array<char, 3> DesignCharConstants::RodLabels  = { '1', '2', '3' };
        const string DesignCharConstants::SpaceBetweenTowers = "   ";
        const string DesignCharConstants::LineBreak          = "----------------------------------------------------------";

    }
}
