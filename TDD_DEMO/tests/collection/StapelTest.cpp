//
// Created by JoachimWagner on 24.02.2025.
//

#include "StapelTest.h"


TEST_F(StapelTest, bla) {
    EXPECT_TRUE(objectUnderTest.isEmpty());
}

TEST_F(StapelTest, blaBlupp) {
    objectUnderTest.push(1);
    EXPECT_FALSE(objectUnderTest.isEmpty());
}