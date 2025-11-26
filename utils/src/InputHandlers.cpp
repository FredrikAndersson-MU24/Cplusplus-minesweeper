#include "../inc/InputHandlers.h"

#include <iostream>
#include <ostream>
#include <sstream>

std::string InputHandlers::getValidCoordinate(const std::vector<char>& rows, const std::vector<int>& columns)
{
    while (true) {
        std::cout << "Enter coordinate  : " << std::endl;
        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss(input);
        if (InputHandlers::validCoordinate(input.c_str(), rows, columns)){
            return input;
        }
        std::cout << "Please enter a valid coordinate! "
                        "(Row " << rows.front() <<  "-" << rows.back() <<
                        ", column " << columns.front() <<  "-" << columns.back() <<  ". For example A1.)\n";
    }
}

bool InputHandlers::validCoordinate(const char* input, const std::vector<char>& rows, const std::vector<int>& columns)
{
    int index = 0;
    bool validColumn = false;
    bool validRow = false;
    std::string col_as_string;
    while (*input)
    {
        const char temp = *input;
        if (index == 0 && std::isalpha(temp))
        {
            for (char c : rows)
            {
                if (tolower(c) == tolower(temp))
                {
                    validRow = true;
                    break;
                }
            }
            if (!validRow)
            {
                std::cout << "INVALID ROW ERROR 1" << std::endl;
                return false;
            }
        } else if (index != 0 && std::isalpha(temp))
        {
            std::cout << "INVALID ROW ERROR 2" << std::endl;
            return false;
        }
        if (index == 0 && std::isdigit(temp))
        {
            std::cout << "INVALID ROW ERROR 3" << std::endl;
            return false;
        }
        if (index != 0 && !std::isdigit(temp))
        {
            std::cout << "INVALID ROW ERROR 4" << std::endl;
            return false;
        }
        if (index != 0 && std::isdigit(temp))
        {
            col_as_string.push_back(temp);
        }
        input++;
        index++;
    }
    if (validRow && !col_as_string.empty())
    {
        const int col_as_int = stoi(col_as_string);
        for (const int column : columns)
        {
            if (col_as_int == column)
            {
                validColumn = true;
                break;
            }
        }
    } else
    {
            std::cout << "INVALID ROW ERROR 5" << std::endl;
    }
    return validRow && validColumn;
}


int InputHandlers::getIntInRange(const int min, const int max){
    int value;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (ss >> value && ss.eof() && value >= min && value <= max) {
            return value;
        } else
        {
            std::cout << "Please enter a valid integer in the range " << min << " to " << max << ".\n";
        }
    }
}

