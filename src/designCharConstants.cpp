#include "designCharConstants.hpp"
#include <iostream>

using namespace std;

namespace HanoiTower {
    namespace GameElements {

        const vector<string> DesignCharConstants::Header = {
            "\t╔╦╗┌─┐┬ ┬┌─┐┬─┐  ┌─┐┌─┐  ╦ ╦┌─┐┌┐┌┌─┐┬",
            "\t ║ │ ││││├┤ ├┬┘  │ │├┤   ╠═╣├─┤││││ ││",
            "\t ╩ └─┘└┴┘└─┘┴└─  └─┘└    ╩ ╩┴ ┴┘└┘└─┘┴"
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
