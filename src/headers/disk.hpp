#pragma once

#include <string>
#include <cmath>

namespace HanoiTower {
    namespace GameElements {
        class Disk {
        private:
            int _size = 1;
            std::string _disk;

        public:
            // Constructor
            Disk(int size);

            // Getter & Setter for Size
            int Size() const;
            void Size(int value);

            // Getter & Setter for Disk string
            std::string GetDisk() const;
            void GetDisk(const std::string& value);

        private:
            std::string createDisk();
        };
    }
}
