#include "AdminPanel.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <SFML/Window.hpp>

// Constructor
AdminPanel::AdminPanel(sf::Font& f, UserManager& um, FlightManager& fm)
    : font(f), userManager(um), flightManager(fm), selectedUserId(-1), selectedFlightIndex(-1),
      showUserPanel(true),

      // User management input boxes
      usernameInputBox(f, 120, 100, 200, 30),
      passwordInputBox(f, 120, 140, 200, 30),
      roleInputBox(f, 120, 180, 200, 30),

      // Flight management input boxes
      flightNumberInputBox(f, 120, 100, 200, 30),
      //destinationInputBox(f, 120, 140, 200, 30),
      startInputBox(f, 120, 180, 200, 30),
        endInputBox(f, 120, 140, 200, 30),
      durationInputBox(f, 120, 220, 200, 30),
      totalTicketInputBox(f, 120, 260, 200, 30),
      soldTicketInputBox(f, 120, 300, 200, 30) {
    // Labels for Flight management inputs
    flightNumberLabel.setFont(font);
    flightNumberLabel.setString("Flight No:");
    flightNumberLabel.setCharacterSize(18);
    flightNumberLabel.setFillColor(sf::Color::Black);
    flightNumberLabel.setPosition(10, 100);

    endLabel.setFont(font);
    endLabel.setString("Destination:");
    endLabel.setCharacterSize(18);
    endLabel.setFillColor(sf::Color::Black);
    endLabel.setPosition(10, 140);

    startLabel.setFont(font);
    startLabel.setString("Departure:");
    startLabel.setCharacterSize(18);
    startLabel.setFillColor(sf::Color::Black);
    startLabel.setPosition(10, 180);

    durationLabel.setFont(font);
    durationLabel.setString("Duration (hrs):");
    durationLabel.setCharacterSize(18);
    durationLabel.setFillColor(sf::Color::Black);
    durationLabel.setPosition(10, 220);

    totalTicketLabel.setFont(font);
    totalTicketLabel.setString("Total Tickets:");
    totalTicketLabel.setCharacterSize(18);
    totalTicketLabel.setFillColor(sf::Color::Black);
    totalTicketLabel.setPosition(10, 260);

    soldTicketLabel.setFont(font);
    soldTicketLabel.setString("Sold Tickets:");
    soldTicketLabel.setCharacterSize(18);
    soldTicketLabel.setFillColor(sf::Color::Black);
    soldTicketLabel.setPosition(10, 300);

    // User management labels
    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(18);
    usernameLabel.setFillColor(sf::Color::Black);
    usernameLabel.setPosition(10, 100);

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(18);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setPosition(10, 140);

    roleLabel.setFont(font);
    roleLabel.setString("Role:");
    roleLabel.setCharacterSize(18);
    roleLabel.setFillColor(sf::Color::Black);
    roleLabel.setPosition(10, 180);

    // Add User Button
    addUserButton.setSize({100, 30});
    addUserButton.setFillColor(sf::Color::Green);
    addUserButton.setPosition(10, 230);

    addUserLabel.setFont(font);
    addUserLabel.setString("Add User");
    addUserLabel.setCharacterSize(16);
    addUserLabel.setFillColor(sf::Color::Black);
    addUserLabel.setPosition(15, 235);

    // Add Flight Button
    addFlightButton.setSize({120, 30});
    addFlightButton.setFillColor(sf::Color::Yellow);
    addFlightButton.setPosition(10, 340);
    editFlightButton.setSize({120, 30});
    editFlightButton.setFillColor(sf::Color::Yellow);


    addFlightLabel.setFont(font);
    addFlightLabel.setString("Add Flight");
    addFlightLabel.setCharacterSize(16);
    addFlightLabel.setFillColor(sf::Color::Black);
    addFlightLabel.setPosition(15, 345);

    // Toggle Button to switch views
    toggleButton.setSize({150, 30});
    toggleButton.setFillColor(sf::Color::Blue);
    toggleButton.setPosition(10, 10);

    toggleLabel.setFont(font);
    toggleLabel.setString("Switch to Flights");
    toggleLabel.setCharacterSize(16);
    toggleLabel.setFillColor(sf::Color::White);
    toggleLabel.setPosition(15, 12);

    // Title text
    title.setFont(font);
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::Black);
    title.setPosition(10, 50);

    // Load users and flights
    userList = userManager.getUsers();
    flightList = flightManager.getFlights();
}


void AdminPanel::drawUI(sf::RenderWindow& window) {
    window.draw(toggleButton);
    window.draw(toggleLabel);
    window.draw(title);
    if (showUserPanel) drawUserUI(window);
    else drawFlightUI(window);
}

void AdminPanel::drawUserUI(sf::RenderWindow& window) {
    title.setString("User Management");
    window.draw(usernameLabel);
    window.draw(passwordLabel);
    window.draw(roleLabel);
    usernameInputBox.draw(window);
    passwordInputBox.draw(window);
    roleInputBox.draw(window);
    window.draw(addUserButton);
    window.draw(addUserLabel);

    for (size_t i = 0; i < userList.size(); ++i) {
        if (selectedUserId == i) {
            sf::RectangleShape highlight(sf::Vector2f(700, 30));
            highlight.setPosition(0, 270 + i * 40);
            highlight.setFillColor(sf::Color(200, 220, 255));
            window.draw(highlight);
        }

        sf::Text userText( "ID: " + std::to_string(userList[i].getId()) + " | " + userList[i].getUsername(), font,16);
        userText.setPosition(10, 270 + i * 40);
        userText.setFillColor(sf::Color::Black);
        window.draw(userText);

        sf::RectangleShape editButton({120, 30});
        editButton.setPosition(400, 270 + i * 40);
        editButton.setFillColor(sf::Color(255, 255, 0, 100));
        window.draw(editButton);
        sf::Text editLabel("Edit", font, 16);
        editLabel.setPosition(460 - editLabel.getGlobalBounds().width / 2, 275 + i * 40);
        editLabel.setFillColor(sf::Color::Black);
        window.draw(editLabel);

        sf::RectangleShape deleteButton({120, 30});
        deleteButton.setPosition(530, 270 + i * 40);
        deleteButton.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(deleteButton);
        sf::Text deleteLabel("Delete", font, 16);
        deleteLabel.setPosition(590 - deleteLabel.getGlobalBounds().width / 2, 275 + i * 40);
        deleteLabel.setFillColor(sf::Color::Black);
        window.draw(deleteLabel);
    }
}

void AdminPanel::drawFlightUI(sf::RenderWindow& window) {
    title.setString("Flight Management");
    window.draw(title);

    // Labels & input boxes for all fields
    window.draw(flightNumberLabel);       // e.g. "Flight No:"
    flightNumberInputBox.draw(window);

    window.draw(startLabel);              // e.g. "Departure:"
    startInputBox.draw(window);

    window.draw(endLabel);                // e.g. "Destination:"
    endInputBox.draw(window);

    window.draw(durationLabel);           // e.g. "Duration (hrs):"
    durationInputBox.draw(window);

    window.draw(totalTicketLabel);        // e.g. "Total Tickets:"
    totalTicketInputBox.draw(window);

    window.draw(soldTicketLabel);         // e.g. "Sold Tickets:"
    soldTicketInputBox.draw(window);

    // Add flight button
    window.draw(addFlightButton);
    window.draw(addFlightLabel);

    // Column headers for list display


    // Draw flight list with full info
    for (size_t i = 0; i < flightList.size(); ++i) {
        float yOffset = 270 + i * 50;

        if (selectedFlightIndex == i) {
            sf::RectangleShape highlight(sf::Vector2f(780, 40));
            highlight.setPosition(10, yOffset+100);
            highlight.setFillColor(sf::Color(200, 220, 255));
            window.draw(highlight);
        }

        const Flight& flight = flightList[i];
        std::ostringstream oss;
        oss << flight.flightNo
            << " | " << flight.start
            << " | " << flight.end
            << " | " << flight.duration << " hrs"
            << " | " << flight.soldTicket << "$" << flight.totalTicket<< " ticket" ;

        sf::Text flightText(oss.str(), font, 16);
        flightText.setPosition(15, yOffset + 100);
        flightText.setFillColor(sf::Color::Black);
        window.draw(flightText);

        // Edit button
        sf::RectangleShape editFlightButton({80, 30});
        editFlightButton.setPosition(600, yOffset + 100);
        editFlightButton.setFillColor(sf::Color(255, 255, 0, 180));
        window.draw(editFlightButton);

        sf::Text editLabel("Edit", font, 16);
        editLabel.setFillColor(sf::Color::Black);
        editLabel.setPosition(600 + 40 - editLabel.getGlobalBounds().width / 2, yOffset + 105);
        window.draw(editLabel);

        // Delete button
        sf::RectangleShape deleteButton({80, 30});
        deleteButton.setPosition(690, yOffset + 100);
        deleteButton.setFillColor(sf::Color(255, 0, 0, 180));
        window.draw(deleteButton);

        sf::Text deleteLabel("Delete", font, 16);
        deleteLabel.setFillColor(sf::Color::Black);
        deleteLabel.setPosition(690 + 40 - deleteLabel.getGlobalBounds().width / 2, yOffset + 105);
        window.draw(deleteLabel);
    }
}



void AdminPanel::showPanel(sf::RenderWindow& window) {
    bool inAdminPanel = true;
    sf::Event event;

    while (inAdminPanel && window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) inAdminPanel = false;

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosF((float)event.mouseButton.x, (float)event.mouseButton.y);

                if (toggleButton.getGlobalBounds().contains(mousePosF)) {
                    showUserPanel = !showUserPanel;
                    toggleLabel.setString(showUserPanel ? "Switch to Flights" : "Switch to Users");
                    selectedUserId = -1;
                    selectedFlightIndex = -1;
                    usernameInputBox.clear(); passwordInputBox.clear(); roleInputBox.clear();
                    flightNumberInputBox.clear(); endInputBox.clear();
                }

                if (showUserPanel) {
                    for (size_t i = 0; i < userList.size(); ++i) {
                        if (sf::FloatRect(400, 270 + i * 40, 120, 30).contains(mousePosF)) {
                            selectedUserId = i;
                            usernameInputBox.setText(userList[i].getUsername());
                            passwordInputBox.setText(userList[i].getPassword());
                            roleInputBox.setText(userList[i].getRole());
                        }
                        if (sf::FloatRect(530, 270 + i * 40, 120, 30).contains(mousePosF)) {
                            userManager.deleteUserById(userList[i].getId());
                            userList = userManager.getUsers();
                            selectedUserId = -1;
                        }
                    }

                    if (addUserButton.getGlobalBounds().contains(mousePosF)) {
                        if (!usernameInputBox.getText().empty() && !passwordInputBox.getText().empty()) {
                            if (selectedUserId >= 0 && selectedUserId < userList.size()) {
                                userManager.updateUser(User(userList[selectedUserId].getId(), usernameInputBox.getText(), passwordInputBox.getText(), roleInputBox.getText()));
                            } else {
                                userManager.addUser(User(userManager.generateNewUserId(), usernameInputBox.getText(), passwordInputBox.getText(), roleInputBox.getText()));
                            }
                            selectedUserId = -1;
                            usernameInputBox.clear(); passwordInputBox.clear(); roleInputBox.clear();
                            userList = userManager.getUsers();
                        }
                    }

                } else  {
    for (size_t i = 0; i < flightList.size(); ++i) {
        float yOffset = 270 + i * 50;

        // Select a flight to edit
        if (sf::FloatRect(600, yOffset + 100, 80, 30).contains(mousePosF)) {
            selectedFlightIndex = i;

            const Flight& f = flightList[i];
            flightNumberInputBox.setText(f.flightNo);
            startInputBox.setText(f.start);
            endInputBox.setText(f.end);
            durationInputBox.setText(std::to_string(f.duration));
            totalTicketInputBox.setText(std::to_string(f.totalTicket));
            soldTicketInputBox.setText(std::to_string(f.soldTicket));
        }

        // Delete flight
        if (sf::FloatRect(690, yOffset + 100, 80, 30).contains(mousePosF)) {
            flightManager.deleteFlight(i);
            flightList = flightManager.getFlights();
            selectedFlightIndex = -1;
        }
    }

    // Add or update flight
    if (addFlightButton.getGlobalBounds().contains(mousePosF)) {
        if (!flightNumberInputBox.getText().empty() &&
            !startInputBox.getText().empty() &&
            !endInputBox.getText().empty() &&
            !durationInputBox.getText().empty() &&
            !totalTicketInputBox.getText().empty() &&
            !soldTicketInputBox.getText().empty())
        {
            Flight flight;
            strcpy(flight.flightNo, flightNumberInputBox.getText().c_str());
            strcpy(flight.start, startInputBox.getText().c_str());
            strcpy(flight.end, endInputBox.getText().c_str());
            flight.duration = std::stof(durationInputBox.getText());
            flight.totalTicket = std::stoi(totalTicketInputBox.getText());
            flight.soldTicket = std::stoi(soldTicketInputBox.getText());

            if (selectedFlightIndex >= 0 && selectedFlightIndex < flightList.size()) {
                // Update existing flight
                flightList[selectedFlightIndex] = flight;
            } else {
                // Add new flight
                flightList.push_back(flight);
            }

            flightManager.saveFlightsToFile("C:/Users/HP/Documents/FlyTicketSystem/flights.txt", flightList);

            // Reset state
            selectedFlightIndex = -1;
            flightNumberInputBox.clear();
            startInputBox.clear();
            endInputBox.clear();
            durationInputBox.clear();
            totalTicketInputBox.clear();
            soldTicketInputBox.clear();

            // Refresh list
            flightList = flightManager.getFlights();
        }
    }
}

                }

                // Input Handling
                if (showUserPanel) {
                    usernameInputBox.handleEvent(event);
                    passwordInputBox.handleEvent(event);
                    roleInputBox.handleEvent(event);
                } else {
                    flightNumberInputBox.handleEvent(event);
                    startInputBox.handleEvent(event);
                    endInputBox.handleEvent(event);
                    durationInputBox.handleEvent(event);
                    totalTicketInputBox.handleEvent(event);
                    soldTicketInputBox.handleEvent(event);
                }
            }
            window.clear(sf::Color(245, 245, 245));
            drawUI(window);
            window.display();
        }
    }


