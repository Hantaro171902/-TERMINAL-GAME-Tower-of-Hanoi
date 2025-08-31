#pragma once

#include <string>
#include <vector>

class Rod {
private:
    int _height = 1;
    std::string _rodBase;
    std::string _label;

    std::string createRodBase();

public:
    Rod(int noDisks, int index);

    int getHeight() const { return _height; }
    void setHeight(int value) { _height = value; }

    std::string getLabel() const { return _label; }
    void setLabel(std::string value) { _label = value; }

    std::string getRodBase() const { return _rodBase; }
    void setRodBase(std::string value) { _rodBase = value; }
};