#include "disk.hpp"
#include "design_char_constants.hpp" // You’ll need this file for constants
#include <iostream>

using namespace std;

namespace HanoiTower {
    namespace GameElements {

        // Constructor
        Disk::Disk(int size) {
            if (size < 0) {
                size = std::abs(size);
            } else if (size == 0) {
                size = 1;
            }
            _size = size;
            _disk = createDisk();
        }

        // Size getter & setter
        int Disk::Size() const { return _size; }
        void Disk::Size(int value) { _size = value; }

        // Disk getter & setter
        std::string Disk::GetDisk() const { return _disk; }
        void Disk::GetDisk(const std::string& value) { _disk = value; }

        // Create disk ASCII representation
        std::string Disk::createDisk() {
            std::string peg = DesignCharConstants::DiskStartChar;

            for (int i = 0; i < _size - 1; i++) {
                peg += DesignCharConstants::DiskStructureChar;
            }

            peg += DesignCharConstants::DiskMiddleChar;

            for (int i = 0; i < _size - 1; i++) {
                peg += DesignCharConstants::DiskStructureChar;
            }

            peg += DesignCharConstants::DiskEndChar;

            return peg;
        }
    }
}
