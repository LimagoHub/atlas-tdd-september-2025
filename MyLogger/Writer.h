//
// Created by JoachimWagner on 16.09.2025.
//

#pragma once


#include <string>

class Writer {
public:
    virtual void write(std::string message) = 0;
};
