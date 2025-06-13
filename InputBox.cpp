#include "InputBox.h"

InputBox::InputBox(sf::Font& f, float x, float y, float w, float h)
    : font(f) {
    box.setPosition(x, y);
    box.setSize({w, h});
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setPosition(x + 5, y + 5);
}

void InputBox::draw(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(text);
}

void InputBox::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        auto pos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        active = box.getGlobalBounds().contains(pos);
        box.setOutlineColor(active ? sf::Color::Blue : sf::Color::Black);
    }
    if (active && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {  // Backspace
            if (!input.empty()) input.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
            input += static_cast<char>(event.text.unicode);
        }
        if (passwordMode) {
            std::string masked(input.length(), '*');
            text.setString(masked);
        } else {
            text.setString(input);
        }
    }
}

std::string InputBox::getText() const {
    return input;
}

void InputBox::clear() {
    input.clear();
    text.setString("");
}

void InputBox::setAsPassword(bool isPassword) {
    passwordMode = isPassword;
    if (passwordMode) {
        std::string masked(input.length(), '*');
        text.setString(masked);
    } else {
        text.setString(input);
    }
}

void InputBox::setText(const std::string& text) {
    this->input = text;
    this->text.setString(text);
}
