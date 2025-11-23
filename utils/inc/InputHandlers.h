#ifndef INDIVIDUELLT_PROJEKTARBETE_INPUTHANDLERS_H
#define INDIVIDUELLT_PROJEKTARBETE_INPUTHANDLERS_H
#include <string>
#include <vector>


bool validCoordinate(const char* input, const std::vector<char>& rows, const std::vector<int>& columns);

std::string getValidCoordinate(const std::vector<char>& rows, const std::vector<int>& columns);

int getIntInRange(int min, int max);


#endif //INDIVIDUELLT_PROJEKTARBETE_INPUTHANDLERS_H