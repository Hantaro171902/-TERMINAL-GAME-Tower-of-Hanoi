#pragma once

#include <string>

namespace HanoiTower {
    namespace GameElements {
        class Rod {
        private:
            int _height = 1;
            std::string _rodBase;
            std::string _label;

        public:
            // Constructor
            Rod(int noDisks, int index);

            // Getter & Setter for Height
            int Height() const;
            void Height(int value);

            // Getter & Setter for Label
            std::string Label() const;
            void Label(const std::string& value);

            // Getter & Setter for RodBase
            std::string RodBase() const;
            void RodBase(const std::string& value);

        private:
            std::string createRodBase();
        };
    }
}
