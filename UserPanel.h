#ifndef USER_PANEL_H
#define USER_PANEL_H

#include <SFML/Graphics.hpp>
#include "FlightManager.h"
#include "InputBox.h"

class UserPanel {
public:
    UserPanel(sf::Font& font, FlightManager& flightManager);
    void show(sf::RenderWindow& window);

private:
    sf::Text buySuccessMessage;
    sf::Clock buyMessageClock;
    sf::Font& font;
    FlightManager& flightManager;
    std::vector<Flight> allFlights;
    std::vector<Flight> filteredFlights;

    InputBox startFilterBox;
    InputBox destinationFilterBox;
    sf::RectangleShape filterButton;
    sf::Text filterLabel;

    void drawUI(sf::RenderWindow& window) const;
    void handleInput(sf::RenderWindow& window);
    void filterFlights();
};

#endif
