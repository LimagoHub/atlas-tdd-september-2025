//
// Created by JoachimWagner on 19.08.2024.
//

#pragma once


#include "Mult.h"


class MultImpl: public Mult {
public:
    long mult(int a, int b) const override {
        long result = 0;


        for(int i = 0 ; i < a; i++) {
            result += b;
        }
        return result;
    }
};
