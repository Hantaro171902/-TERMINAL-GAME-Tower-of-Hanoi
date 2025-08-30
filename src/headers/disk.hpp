#include "utils.hpp"
#include "string"

class Disk {
public:
    int size;
    std::string representation;
    
    Disk(int s, int maxHeight);
}