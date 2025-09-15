#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "euro_to_dollar_presenter.h"
#include "../view/euro_to_dollar_view.h"



class euro_to_dollar_presenter_impl :
	public euro_to_dollar_presenter
{
private:
	euro_to_dollar_view* view_{ nullptr };
	euro_to_dollar_calculator* model_{ nullptr };



    [[nodiscard]] std::string specifiy_format(double dollar) const {
        std::stringstream ss;

        ss << std::fixed;
        ss.precision(2);
        ss << dollar;
        return ss.str();
    }


public:
	euro_to_dollar_presenter_impl() = default;

	void set_model(euro_to_dollar_calculator* model) override
	{

		model_ = model;
	}

	void set_view(euro_to_dollar_view* view) override
	{
        view_ = view;
	}

	void populate_items() const override
	{
        view_->set_euro("0");
        view_->set_dollar("0");
        view_->set_rechnen_enabled(true);

	}

    //Euro string aus view lesen
    // eurowert wandeln -> double (Im fehlerfall -> Fehlermeldung im Dollarfeld)
    // servicecall -> bei Fehler -> Fehlermeldung im Dollarfeld
    // double dollar -> string
    // ergebnis in das Dollarfeld schreiben
    /*
     *
    */
	void rechnen() const override
	{
        try {
            std::string euroValueAsString = view_->get_euro();
            size_t endpos;
            double euro = std::stod(euroValueAsString, &endpos);
            if((euroValueAsString.length() != endpos ) || !( std::isfinite(euro))) {
                view_->set_dollar("Keine Zahl");
                return;
            }
            double dollar = model_->convert(euro);
            view_->set_dollar(specifiy_format(dollar));
        } catch(const std::runtime_error &e) {
            view_->set_dollar("Internal Server Error");
        } catch (const std::invalid_argument &e) {
            view_->set_dollar("Keine Zahl");
        }
	}


    void beenden() const override
	{
        view_->dispose();
	}

    /*
     * Eurowert als String lesen
     * wenn gueltig rechnen aktivieren
     * sonst deaktivieren
     */
	void update_rechnen_action_state() const override
	{
        try {
            std::stod(view_->get_euro());
            view_->set_rechnen_enabled(true);
        } catch( const std::invalid_argument ) {
            view_->set_rechnen_enabled(false);
        }

	}
};

