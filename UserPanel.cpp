#include "UserPanel.h"

#include <cstring>
#include <sstream>

UserPanel::UserPanel(sf::Font& font, FlightManager& manager)
    : font(font), flightManager(manager),
      startFilterBox(font, 100, 60, 150, 30),
      destinationFilterBox(font, 300, 60, 150, 30) {

    allFlights = flightManager.getFlights();
    filteredFlights = allFlights;

    buySuccessMessage.setFont(font);
    buySuccessMessage.setCharacterSize(20);
    buySuccessMessage.setFillColor(sf::Color::Green);
    buySuccessMessage.setPosition(100, 500); // bottom of screen
    buySuccessMessage.setString("Ticket Purchased Successfully!");
    buySuccessMessage.setFillColor(sf::Color::Green);

    filterButton.setSize({100, 30});
    filterButton.setFillColor(sf::Color::Green);
    filterButton.setPosition(500, 60);

    filterLabel.setFont(font);
    filterLabel.setCharacterSize(18);
    filterLabel.setString("Filter");
    filterLabel.setFillColor(sf::Color::White);
    filterLabel.setPosition(515, 62);
}

void UserPanel::show(sf::RenderWindow& window) {
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            startFilterBox.handleEvent(event);
            destinationFilterBox.handleEvent(event);

            // UserPanel.cpp - show() function

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (filterButton.getGlobalBounds().contains(mousePos)) {
                    filterFlights();
                }

                // Check for Buy button clicks
                for (size_t i = 0; i < filteredFlights.size(); ++i) {
                    sf::FloatRect buyButtonBounds(600, 120 + i * 40, 80, 30);
                    if (buyButtonBounds.contains(mousePos)) {
                        Flight& f = const_cast<Flight&>(filteredFlights[i]);

                        if ( f.totalTicket>0) {
                            f.soldTicket++;
                            buySuccessMessage.setString("Ticket Purchased Successfully!");

                            // Update original list and save to file
                            for (auto& flight : flightManager.getFlights()) {
                                if (std::strcmp(flight.flightNo, f.flightNo) == 0) {
                                    flight.soldTicket++;
                                    break;
                                }
                            }
                            flightManager.saveFlights();

                            buyMessageClock.restart(); // reset timer
                        } else {
                            buySuccessMessage.setString("No more tickets available.");
                            buySuccessMessage.setFillColor(sf::Color::Red);
                            buyMessageClock.restart();
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        drawUI(window);
        window.display();
    }
}

void UserPanel::filterFlights() {
    std::string start = startFilterBox.getText();
    std::string end = destinationFilterBox.getText();

    filteredFlights.clear();
    for (const auto& f : allFlights) {
        if ((start.empty() || start == f.start) && (end.empty() || end == f.end)) {
            filteredFlights.push_back(f);
        }
    }
}

void UserPanel::drawUI(sf::RenderWindow& window) const {
    startFilterBox.draw(window);
    destinationFilterBox.draw(window);
    window.draw(filterButton);
    window.draw(filterLabel);

    for (size_t i = 0; i < filteredFlights.size(); ++i) {
        const auto& f = filteredFlights[i];
        std::ostringstream oss;
        oss << f.flightNo << " | " << f.start << " -> " << f.end
            << " | " << f.duration << "h | " << f.soldTicket << "/" << f.totalTicket;

        sf::Text flightText(oss.str(), font, 16);
        flightText.setFillColor(sf::Color::Black);
        flightText.setPosition(100, 120 + i * 40);
        window.draw(flightText);

        // Buy button
        sf::RectangleShape buyButton({80, 30});
        buyButton.setPosition(600, 120 + i * 40);
        buyButton.setFillColor(sf::Color::Blue);
        window.draw(buyButton);

        sf::Text buyLabel("Buy", font, 16);
        buyLabel.setFillColor(sf::Color::White);
        buyLabel.setPosition(615, 125 + i * 40);
        window.draw(buyLabel);
    }
    if (buyMessageClock.getElapsedTime().asSeconds() < 3) { // show for 3 seconds
        window.draw(buySuccessMessage);
    }
}
