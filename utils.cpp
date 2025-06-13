// utils.cpp
#include "utils.h"

// Define the function in only one .cpp file
sf::Color putColor(const sf::Color& start, const sf::Color& end, float t) {
    return sf::Color(
        static_cast<sf::Uint8>(start.r + t * (end.r - start.r)),
        static_cast<sf::Uint8>(start.g + t * (end.g - start.g)),
        static_cast<sf::Uint8>(start.b + t * (end.b - start.b)),
        static_cast<sf::Uint8>(start.a + t * (end.a - start.a))
    );
}