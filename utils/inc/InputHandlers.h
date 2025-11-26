#ifndef INPUTHANDLERS_H
#define INPUTHANDLERS_H

#include <string>
#include <vector>

class InputHandlers
{

public:
    static bool validCoordinate(const char* input, const std::vector<char>& rows, const std::vector<int>& columns);
    static std::string getValidCoordinate(const std::vector<char>& rows, const std::vector<int>& columns);
    static int getIntInRange(int min, int max);

};




#endif