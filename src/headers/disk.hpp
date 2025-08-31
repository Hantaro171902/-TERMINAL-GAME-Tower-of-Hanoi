#pragma once

#include "utils.hpp"
#include "string"

class Disk {
private:
    int _size = 1;
    std::string _disk;
    std::string createDisk();

public:
    std::string representation;
    Disk(int _size);
};