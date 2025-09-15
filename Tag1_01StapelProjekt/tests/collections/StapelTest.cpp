//
// Created by JoachimWagner on 15.09.2025.
//

#include "StapelTest.h"

TEST_F(StapelTest, isEmpty__emptyStack__returnsTrue){
    // Arrange


    // Act


    // Assert
    EXPECT_TRUE(objectUnderTest.isEmpty());
}

TEST_F(StapelTest, isEmpty__NotemptyStack__returnsFalse){
    // Arrange

    objectUnderTest.push(1);

    // Act
    auto result = objectUnderTest.isEmpty();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(StapelTest, isEmpty__EmptyAgainStack__returnsTrue) {

    auto const validValue = 1;
    // Arrange

    objectUnderTest.push(validValue);
    objectUnderTest.pop();
    // Action

    auto result = objectUnderTest.isEmpty();

    // Assertion
    EXPECT_TRUE(result);

}
//Methode__Fall__Erwartung
TEST_F(StapelTest, push__fillupToLimit__noExceptionIsThrown) {
    fillUpToLimitWithoutException();

}

TEST_F(StapelTest, push__Overflow__throwsStapelException) {
    fillUpToLimitWithoutException();
    EXPECT_THROW(objectUnderTest.push(1), StapelException);
}

TEST_F(StapelTest, push__Overflow__throwsStapelException_variante) {

    try {;
        fillUpToLimitWithoutException();
        objectUnderTest.push(1);
        FAIL() << "Fehler Stapelexception erwartet!";
    } catch (const StapelException & ex) {
        EXPECT_STREQ("Overflow", ex.what());
    }

}