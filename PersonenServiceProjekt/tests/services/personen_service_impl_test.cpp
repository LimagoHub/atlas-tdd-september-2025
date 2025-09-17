//
// Created by JoachimWagner on 16.09.2025.
//
#include <stdexcept>
#include "personen_service_impl_test.h"
#include "../../source/services/personen_service_exception.h"


TEST_P(personen_service_impl_parameter_test, speichern__throws_personen_service_exception) {
    try {

        objectUnderTest.speichern(invalidPerson);
        FAIL() << "Exception erwartet";
    } catch (personen_service_exception &ex) {
        EXPECT_STREQ(ex.what(), expectedErrorMessage.c_str());
    }
}

TEST_F(personen_service_impl_test, speichern__VornameZuKurz__throws_personen_service_exception) {
    try {
        // Arrange
        person invalidPerson{"j", "Doe"};

        EXPECT_CALL(repositoryMock, save_or_update(_)).Times(0);
        // Action
        objectUnderTest.speichern(invalidPerson);

        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Vorname zu kurz!"));
    }

}

TEST_F(personen_service_impl_test, speichern__NachnameZuKurz__throws_personen_service_exception) {
    try {
        // Arrange
        person invalidPerson{"john", "d"};

        // Action
        objectUnderTest.speichern(invalidPerson);

        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Nachname zu kurz!"));
    }

}

TEST_F(personen_service_impl_test, speichern__ExceptionInBlacklistedService__throws_personen_service_exception) {
    try {
        // Arrange
        person invalidPerson{"John", "Der Hunne"};
        EXPECT_CALL(blackListServiceMock, isBlacklisted(_)).WillOnce(Throw(std::invalid_argument{"xxx"}));
        // Action
        objectUnderTest.speichern(invalidPerson);

        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Ein Fehler ist aufgetreten"));
    }

}

TEST_F(personen_service_impl_test, speichern__BlacklistedPerson__throws_personen_service_exception) {
    try {
        // Arrange
        person invalidPerson{"John", "Der Hunne"};
        EXPECT_CALL(blackListServiceMock, isBlacklisted(invalidPerson)).WillOnce(Return(true));
        // Action
        objectUnderTest.speichern(invalidPerson);

        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Unerwuenschte Person"));
    }

}

TEST_F(personen_service_impl_test, speichern__UnexpectedExceptionInUnderlyingService__throws_personen_service_exception) {
    try {
        person validPerson{"John", "Doe"};


        EXPECT_CALL(repositoryMock, save_or_update(_)).WillOnce(Throw(std::out_of_range("Upps")));

        objectUnderTest.speichern(validPerson);
        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Ein Fehler ist aufgetreten"));
    }
}

TEST_F(personen_service_impl_test, speichern__HappyDay__personPassedToRepo) {
        InSequence dummy;
        person validPerson{"John", "Doe"};
        EXPECT_CALL(blackListServiceMock, isBlacklisted(_)).WillOnce(Return(false));
        EXPECT_CALL(repositoryMock, save_or_update(validPerson));

        objectUnderTest.speichern(validPerson);

}


TEST_F(personen_service_impl_test, speichern__happy_day__person_passed_to_repo_overloaded) {
    InSequence dummy;
    person captured_person{};
    EXPECT_CALL(blackListServiceMock, isBlacklisted(_)).WillOnce(Return(false));
    EXPECT_CALL(repositoryMock, save_or_update(_)).WillOnce(DoAll(SaveArg<0>(&captured_person)));
    objectUnderTest.speichern("John","Mustermann");
    EXPECT_THAT( captured_person.getVorname(), AnyOf(StartsWith("J"), StartsWith("M")));
    EXPECT_THAT(captured_person.getNachname(), AnyOf(Eq("Doe"), Eq("Mustermann")));
    //EXPECT_THAT(captured_person.getId(), Not(IsEmpty()));

}

INSTANTIATE_TEST_SUITE_P(
        speichern_invalid_names, // Name der Testa frei waehlbar
        personen_service_impl_parameter_test, // Verbindung zur Testklasse
        Values(
                std::make_pair(person{"","Doe"},"Vorname zu kurz!" ),
                std::make_pair(person{"J","Doe"},"Vorname zu kurz!" ),
                std::make_pair(person{"John",""},"Nachname zu kurz!" ),
                std::make_pair(person{"John","D"},"Nachname zu kurz!" )
        )
);