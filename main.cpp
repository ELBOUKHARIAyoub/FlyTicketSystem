#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "User.h"
#include "UserManager.h"
#include "FlightManager.h"
#include "AdminPanel.h"
#include "UserPanel.h"
#include "utils.h"
UserManager userManager;
FlightManager flightManager;

void loadUsers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string username, password, role;
        iss >> id >> username >> password >> role;
        userManager.addUser(User(id, username, password, role));
        std::cout << "Loaded user: " << username << ", " << password << ", " << role << std::endl;
    }
}

void loadFlights() {
    flightManager.loadFlights();
}

// Helper function for smooth color transitions
sf::Color putColor( sf::Color& a, sf::Color& b, float t) {
    t = std::max(0.0f, std::min(1.0f, t));
    return sf::Color(
        static_cast<sf::Uint8>(a.r + t * (b.r - a.r)),
        static_cast<sf::Uint8>(a.g + t * (b.g - a.g)),
        static_cast<sf::Uint8>(a.b + t * (b.b - a.b)),
        static_cast<sf::Uint8>(a.a + t * (b.a - a.a))
    );
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Flight Ticket Booking System", sf::Style::Close);
    window.setFramerateLimit(60);

    loadUsers("C:/Users/HP/Documents/FlyTicketSystem/users.txt");
    loadFlights();

    sf::Font font;
    if (!font.loadFromFile("C:/Users/HP/Documents/FlyTicketSystem/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Clock for animations
    sf::Clock clock;
    sf::Clock buttonHoverClock;
    bool buttonHovered = false;

    // Background gradient effect
    sf::RectangleShape background(sf::Vector2f(1000, 700));

    // Main login container
    sf::RectangleShape loginContainer(sf::Vector2f(400, 500));
    loginContainer.setPosition(300, 100);
    loginContainer.setFillColor(sf::Color(255, 255, 255, 240));
    loginContainer.setOutlineThickness(1);
    loginContainer.setOutlineColor(sf::Color(200, 200, 200, 150));

    // Add shadow effect
    sf::RectangleShape shadow(sf::Vector2f(400, 500));
    shadow.setPosition(305, 105);
    shadow.setFillColor(sf::Color(0, 0, 0, 30));

    // Title
    sf::Text titleText("Flight Booking System", font, 32);
    titleText.setPosition(350, 130);
    titleText.setFillColor(sf::Color(41, 128, 185));
    titleText.setStyle(sf::Text::Bold);

    sf::Text subtitleText("Please sign in to continue", font, 16);
    subtitleText.setPosition(400, 170);
    subtitleText.setFillColor(sf::Color(127, 140, 141));

    // Input boxes with modern styling
    sf::RectangleShape usernameBox(sf::Vector2f(320, 45));
    usernameBox.setPosition(340, 230);
    usernameBox.setFillColor(sf::Color(250, 250, 250));
    usernameBox.setOutlineThickness(2);
    usernameBox.setOutlineColor(sf::Color(189, 195, 199));

    sf::RectangleShape passwordBox(sf::Vector2f(320, 45));
    passwordBox.setPosition(340, 310);
    passwordBox.setFillColor(sf::Color(250, 250, 250));
    passwordBox.setOutlineThickness(2);
    passwordBox.setOutlineColor(sf::Color(189, 195, 199));

    // Labels with icons
    sf::Text usernameLabel("👤 Username", font, 18);
    usernameLabel.setPosition(345, 200);
    usernameLabel.setFillColor(sf::Color(52, 73, 94));
    usernameLabel.setStyle(sf::Text::Bold);

    sf::Text passwordLabel("🔒 Password", font, 18);
    passwordLabel.setPosition(345, 280);
    passwordLabel.setFillColor(sf::Color(52, 73, 94));
    passwordLabel.setStyle(sf::Text::Bold);

    // Input text
    sf::Text usernameText("", font, 18);
    usernameText.setPosition(350, 240);
    usernameText.setFillColor(sf::Color(44, 62, 80));

    sf::Text passwordText("", font, 18);
    passwordText.setPosition(350, 320);
    passwordText.setFillColor(sf::Color(44, 62, 80));

    // Placeholder texts
    sf::Text usernamePlaceholder("Enter your username", font, 16);
    usernamePlaceholder.setPosition(350, 242);
    usernamePlaceholder.setFillColor(sf::Color(149, 165, 166));

    sf::Text passwordPlaceholder("Enter your password", font, 16);
    passwordPlaceholder.setPosition(350, 322);
    passwordPlaceholder.setFillColor(sf::Color(149, 165, 166));

    // Modern login button
    sf::RectangleShape loginButton(sf::Vector2f(320, 50));
    loginButton.setPosition(340, 390);
    loginButton.setFillColor(sf::Color(52, 152, 219));

    sf::Text loginLabel("LOGIN", font, 20);
    loginLabel.setPosition(475, 402);
    loginLabel.setFillColor(sf::Color::White);
    loginLabel.setStyle(sf::Text::Bold);

    // Message text
    sf::Text messageText("", font, 16);
    messageText.setPosition(340, 460);

    // Additional decorative elements
    sf::CircleShape decorCircle1(30);
    decorCircle1.setPosition(50, 50);
    decorCircle1.setFillColor(sf::Color(52, 152, 219, 100));

    sf::CircleShape decorCircle2(20);
    decorCircle2.setPosition(900, 600);
    decorCircle2.setFillColor(sf::Color(46, 204, 113, 100));

    std::string usernameInput, passwordInput;
    bool isTypingUsername = false;
    bool isTypingPassword = false;
    bool loginSuccess = false;

    while (window.isOpen()) {
        sf::Event event;
        float deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle text input
            if (!loginSuccess && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') { // Backspace
                    if (isTypingUsername && !usernameInput.empty())
                        usernameInput.pop_back();
                    else if (isTypingPassword && !passwordInput.empty())
                        passwordInput.pop_back();
                } else if (event.text.unicode == '\t') { // Tab
                    // Handle tab separately
                } else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\t') {
                    if (isTypingUsername && usernameInput.length() < 20)
                        usernameInput += static_cast<char>(event.text.unicode);
                    else if (isTypingPassword && passwordInput.length() < 20)
                        passwordInput += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    if (isTypingUsername) {
                        isTypingUsername = false;
                        isTypingPassword = true;
                    } else if (isTypingPassword) {
                        isTypingPassword = false;
                        isTypingUsername = true;
                    } else {
                        isTypingUsername = true;
                    }
                }

                if (!loginSuccess && event.key.code == sf::Keyboard::Enter) {
                    User* user = userManager.authenticate(usernameInput, passwordInput);
                    if (user != nullptr) {
                        loginSuccess = true;
                        std::string role = user->getRole();
                        messageText.setFillColor(sf::Color(39, 174, 96));
                        if (role == "admin") {
                            messageText.setString("✓ Login successful! Opening Admin Panel...");
                            AdminPanel adminPanel(font, userManager, flightManager);
                            adminPanel.showPanel(window);
                            usernameInput.clear();
                            passwordInput.clear();
                            messageText.setString("");
                            loginSuccess = false;
                            isTypingUsername = false;
                            isTypingPassword = false;
                        } else {
                            messageText.setString("✓ Login successful! Opening User Panel...");
                            UserPanel userPanel(font, flightManager);
                            userPanel.show(window);
                            usernameInput.clear();
                            passwordInput.clear();
                            messageText.setString("");
                            loginSuccess = false;
                            isTypingUsername = false;
                            isTypingPassword = false;
                        }
                    } else {
                        messageText.setString("✗ Login failed: Invalid username or password");
                        messageText.setFillColor(sf::Color(231, 76, 60));
                    }
                }
            }

            if (!loginSuccess && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (usernameBox.getGlobalBounds().contains(mouseF)) {
                    isTypingUsername = true;
                    isTypingPassword = false;
                }
                else if (passwordBox.getGlobalBounds().contains(mouseF)) {
                    isTypingPassword = true;
                    isTypingUsername = false;
                }
                else {
                    isTypingUsername = false;
                    isTypingPassword = false;
                }

                if (loginButton.getGlobalBounds().contains(mouseF)) {
                    User* user = userManager.authenticate(usernameInput, passwordInput);
                    if (user != nullptr) {
                        loginSuccess = true;
                        std::string role = user->getRole();
                        messageText.setFillColor(sf::Color(39, 174, 96));
                        if (role == "admin") {
                            messageText.setString("✓ Login successful! Opening Admin Panel...");
                            AdminPanel adminPanel(font, userManager, flightManager);
                            adminPanel.showPanel(window);
                            usernameInput.clear();
                            passwordInput.clear();
                            messageText.setString("");
                            loginSuccess = false;
                            isTypingUsername = false;
                            isTypingPassword = false;
                        } else {
                            messageText.setString("✓ Login successful! Opening User Panel...");
                            UserPanel userPanel(font, flightManager);
                            userPanel.show(window);
                            usernameInput.clear();
                            passwordInput.clear();
                            messageText.setString("");
                            loginSuccess = false;
                            isTypingUsername = false;
                            isTypingPassword = false;
                        }
                    } else {
                        messageText.setString("✗ Login failed: Invalid username or password");
                        messageText.setFillColor(sf::Color(231, 76, 60));
                    }
                }
            }

            // Mouse hover effects
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (loginButton.getGlobalBounds().contains(mouseF)) {
                    if (!buttonHovered) {
                        buttonHovered = true;
                        buttonHoverClock.restart();
                    }
                } else {
                    if (buttonHovered) {
                        buttonHovered = false;
                        buttonHoverClock.restart();
                    }
                }
            }
        }

        // Animate button hover effect
        float hoverProgress = buttonHoverClock.getElapsedTime().asSeconds() * 3.0f;
        if (hoverProgress > 1.0f) hoverProgress = 1.0f;

        sf::Color normalButtonColor(52, 152, 219);
        sf::Color hoverButtonColor(41, 128, 185);

        if (buttonHovered) {
            loginButton.setFillColor(putColor(normalButtonColor, hoverButtonColor, hoverProgress));
        } else {
            loginButton.setFillColor(putColor(hoverButtonColor, normalButtonColor, hoverProgress));
        }

        // Update input box colors based on focus
        if (isTypingUsername) {
            usernameBox.setOutlineColor(sf::Color(52, 152, 219));
            usernameBox.setOutlineThickness(3);
        } else {
            usernameBox.setOutlineColor(sf::Color(189, 195, 199));
            usernameBox.setOutlineThickness(2);
        }

        if (isTypingPassword) {
            passwordBox.setOutlineColor(sf::Color(52, 152, 219));
            passwordBox.setOutlineThickness(3);
        } else {
            passwordBox.setOutlineColor(sf::Color(189, 195, 199));
            passwordBox.setOutlineThickness(2);
        }

        // Update text display
        usernameText.setString(usernameInput);
        passwordText.setString(std::string(passwordInput.size(), 'D'));

        // Animate decorative circles
        float time = clock.getElapsedTime().asSeconds();
        decorCircle1.setPosition(50 + sin(time * 0.5f) * 10, 50 + cos(time * 0.3f) * 5);
        decorCircle2.setPosition(900 + sin(time * 0.7f) * 8, 600 + cos(time * 0.4f) * 6);

        // Create animated background gradient
        float gradientOffset = sin(time * 0.2f) * 20;
        background.setFillColor(sf::Color(236 + gradientOffset, 240 + gradientOffset, 241));

        // Render everything
        window.clear();
        window.draw(background);
        window.draw(decorCircle1);
        window.draw(decorCircle2);

        if (!loginSuccess) {
            window.draw(shadow);
            window.draw(loginContainer);
            window.draw(titleText);
            window.draw(subtitleText);

            window.draw(usernameLabel);
            window.draw(usernameBox);
            if (usernameInput.empty() && !isTypingUsername) {
                window.draw(usernamePlaceholder);
            } else {
                window.draw(usernameText);
            }

            window.draw(passwordLabel);
            window.draw(passwordBox);
            if (passwordInput.empty() && !isTypingPassword) {
                window.draw(passwordPlaceholder);
            } else {
                window.draw(passwordText);
            }

            window.draw(loginButton);
            window.draw(loginLabel);
        }

        window.draw(messageText);
        window.display();
    }

    return 0;
}