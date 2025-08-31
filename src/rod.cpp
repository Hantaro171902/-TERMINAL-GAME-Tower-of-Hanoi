#include "rod.hpp"
#include "design_char_constants.hpp"  // we need constants
#include <cmath>

namespace HanoiTower {
    namespace GameElements {

        // Constructor
        Rod::Rod(int noDisks, int index) {
            if (noDisks < 0) {
                noDisks = std::abs(noDisks);
            } else if (noDisks == 0) {
                noDisks = 1;
            }
            _height = noDisks;

            // Label = "[1]", "[2]", "[3]"
            _label = "[" + std::string(1, DesignCharConstants::RodLabels[index]) + "]";

            // Build rod base
            _rodBase = createRodBase();
        }

        // Height getter/setter
        int Rod::Height() const { return _height; }
        void Rod::Height(int value) { _height = value; }

        // Label getter/setter
        std::string Rod::Label() const { return _label; }
        void Rod::Label(const std::string& value) { _label = value; }

        // RodBase getter/setter
        std::string Rod::RodBase() const { return _rodBase; }
        void Rod::RodBase(const std::string& value) { _rodBase = value; }

        // Private helper to create rod base
        std::string Rod::createRodBase() {
            std::string rodBase = DesignCharConstants::RodBaseChar;
            for (int i = 0; i < (_height * 4); i++) {
                rodBase += DesignCharConstants::RodBaseChar;
            }
            return rodBase;
        }

    }
}
