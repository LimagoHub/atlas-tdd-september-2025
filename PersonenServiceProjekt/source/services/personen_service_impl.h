//
// Created by JoachimWagner on 16.09.2025.
//

#pragma once
#include "personen_service.h"
#include "personen_service_exception.h"
#include "../persistence/personen_repository.h"
#include "BlackListService.h"

class personen_service_impl: public personen_service{
public:
    personen_service_impl(personen_repository &repo, BlackListService &blackListService) : repo(repo), blackListService(
            blackListService) {}

/*
 *	Vorname < 2 -> PSE
 *	Nachname < 2 -> PSE
 *
 *	Attila -> PSE
 *
 *	Alle technische Exceptions -> PSE
 *
 *	Happy Day -> person an Save_or_update Methode uebergeben
 *
 */
    void speichern(person &person_) override {
        try {
            speichernImpl(person_);

        } catch(personen_service_exception &ex) {
            throw ex;
        } catch (std::exception &ex) {
            throw personen_service_exception{"Ein Fehler ist aufgetreten"};
        }
    }

    void speichern(std::string vorname, std::string nachname) override {
        person p{vorname, nachname};
        speichern(p);
    }


private:
    personen_repository &repo;
    BlackListService & blackListService;

    void speichernImpl(const person &person_) const {
        checkPerson(person_);
        repo.save_or_update(person_);
    }

    void checkPerson(const person &person_) const {
        validatePerson(person_);
        businessCheck(person_);
    }

    void businessCheck(const person &person_) const {
        if (blackListService.isBlacklisted(person_))
            throw personen_service_exception{"Unerwuenschte Person"};
    }

    void validatePerson(const person &person_) const {
        if (person_.getVorname().length() < 2)
            throw personen_service_exception{"Vorname zu kurz!"};
        if (person_.getNachname().length() < 2)
            throw personen_service_exception{"Nachname zu kurz!"};
    }


};
