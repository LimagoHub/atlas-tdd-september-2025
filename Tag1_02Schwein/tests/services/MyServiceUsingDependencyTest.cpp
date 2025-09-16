//
// Created by JoachimWagner on 15.09.2025.
//
#include <iostream>
#include "MyServiceUsingDependencyTest.h"

TEST_F(MyServiceUsingDependencyTest, MockdemoFooFunc) {
    /*
 *
 *  void f(std::string value) {
        transform(value.begin(), value.end(), value.begin(), ::toupper);
        dependency.foo(value);
    }
 *
 */

    // Recordmode
    EXPECT_CALL(dependencyMock, foo("HALLO"));
    //EXPECT_CALL(dependencyMock, foo(_));
    // Replay

    objectUnderTest.f("hallo");
}

TEST_F(MyServiceUsingDependencyTest, MockdemoFooBarFunc) {
/*
 *  size_t g(std::string value) {
        value += " Welt";
        return dependency.foobar(value) + 5;;
    }
 *
 */
    EXPECT_CALL(dependencyMock, foobar("Hallo Welt")).Times(AtLeast(1))
    .WillOnce(Return(3L))
    .WillOnce(Return(5)).WillOnce(Throw(std::exception{"Upps"}));

    EXPECT_CALL(dependencyMock, foobar("Hello Welt")).Times(AtLeast(1))
            .WillOnce(Return(2L))
            .WillOnce(Return(1));

    EXPECT_CALL(dependencyMock, foobar(_)).Times(AtLeast(0))
            .WillOnce(Return(2L))
            .WillOnce(Return(1));


    EXPECT_EQ(8, objectUnderTest.g("Hallo"));
    EXPECT_EQ(7, objectUnderTest.g("Hello"));

}

TEST_F(MyServiceUsingDependencyTest, MockdemoBarFunc) {
    /*
     * long h() {
        return dependency.bar() * dependency.bar();

    }
     *
     */

    // Arrange
    // Recordmode
    EXPECT_CALL(dependencyMock, bar()).Times(1).WillRepeatedly(Return(3));

    // Action
    const auto result = objectUnderTest.h();

    // Assertion
    EXPECT_THAT(result, Eq(9));
}

void MyServiceUsingDependencyTest::SetUp() {
    std::cout << "SetUp" << std::endl;
}
