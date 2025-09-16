//
// Created by JoachimWagner on 16.09.2025.
//

#include "personen_service_impl_test.h"
#include "../../source/services/personen_service_exception.h"

TEST_F(personen_service_impl_test, speichern__VornameZuKurz__throws_personen_service_exception) {
    try {
        // Arrange
        person invalidPerson{"j", "Doe"};

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
        person invalidPerson{"john", "D"};

        // Action
        objectUnderTest.speichern(invalidPerson);

        FAIL() << "personen_service_exception erwartet";
    } catch( const personen_service_exception & ex) {
        EXPECT_THAT(ex.what(), StrEq("Nachname zu kurz!"));
    }

}