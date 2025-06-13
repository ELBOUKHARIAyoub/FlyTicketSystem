#include <SFML/Graphics.hpp>
#include "UserManager.h"
#include "FlightManager.h"
#include "InputBox.h"

class AdminPanel {
public:
    AdminPanel(sf::Font& f, UserManager& um, FlightManager& fm);
    void showPanel(sf::RenderWindow& window);

private:
    sf::Text startLabel;
    InputBox startInputBox;    // your own wrapper for text input

    sf::Text endLabel;
    InputBox endInputBox;

    sf::Text durationLabel;
    InputBox durationInputBox;

    sf::Text totalTicketLabel;
    InputBox totalTicketInputBox;

    sf::Text soldTicketLabel;
    InputBox soldTicketInputBox;
    std::vector<User> userList;
    std::vector<Flight> flightList;

    sf::Font& font;
    UserManager& userManager;
    FlightManager& flightManager;

    // Toggle between User and Flight panes
    bool showUserPanel;
    sf::RectangleShape toggleButton;
    sf::Text toggleLabel;

    // General UI Elements
    sf::Text title;

    // User Management UI
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text roleLabel;
    InputBox usernameInputBox;
    InputBox passwordInputBox;
    InputBox roleInputBox;
    sf::RectangleShape addUserButton;
    sf::Text addUserLabel;
    int selectedUserId;

    // Flight Management UI
    sf::Text flightNumberLabel;
    // sf::Text destinationLabel;
    InputBox flightNumberInputBox;
    // InputBox destinationInputBox;
    sf::RectangleShape addFlightButton;
    sf::Text addFlightLabel;
    int selectedFlightIndex;
    sf::RectangleShape editFlightButton;

    // Drawing helpers
    void drawUI(sf::RenderWindow& window);
    void drawUserUI(sf::RenderWindow& window);
    void drawFlightUI(sf::RenderWindow& window);

};

// ADMIN_PANEL_H
