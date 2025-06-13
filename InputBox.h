#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class InputBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font& font;
    bool active = false;
    bool passwordMode = false;
    std::string input;
public:
    InputBox(sf::Font& f, float x, float y, float w, float h);
    void draw(sf::RenderWindow& window) const;
    void handleEvent(sf::Event& event);
    std::string getText() const;
    void clear();
    void setAsPassword(bool isPassword);
    void setText(const std::string& text);

    void setPosition(int i, int i1);
};

#endif