//
// Created by JoachimWagner on 16.09.2025.
//

#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Mockpersonen_repository.h"
#include "MockBlackListService.h"
#include "../../source/services/personen_service_impl.h"

using namespace testing;

class personen_service_impl_test: public Test {
protected:
    StrictMock<Mockpersonen_repository> repositoryMock;
    NaggyMock<MockBlackListService> blackListServiceMock;
    personen_service_impl objectUnderTest{repositoryMock, blackListServiceMock};

    void SetUp() override {
        ON_CALL(blackListServiceMock, isBlacklisted(_)).WillByDefault(Return(false));
    }
};

class personen_service_impl_parameter_test : public personen_service_impl_test, public WithParamInterface<std::pair<person, std::string>> {
public:
    personen_service_impl_parameter_test(): personen_service_impl_test(){}

protected:
    person invalidPerson{"",""};
    std::string expectedErrorMessage;

    void SetUp() override{

        std::tie<person, std::string>(invalidPerson, expectedErrorMessage) = GetParam();

    }

};

