//
// Created by JoachimWagner on 16.09.2025.
//

#pragma once


#include <string>
#include <iostream>
#include "Writer.h"
class Logger {

    Writer &writer;
public:
    explicit Logger(Writer &writer) : writer(writer) {}

public:
    void log(std::string message) {
        const std::string prefix = "Ein komplexer Prefix: ";
        writer.write(prefix + message);

    }

};
