//
// Created by JoachimWagner on 16.09.2025.
//

#pragma once

#include <iostream>
#include "Writer.h"

class ConsoleWriter: public Writer {
public:
    void write(std::string message) override {
        std::cout << message << std::endl;
    }
};
