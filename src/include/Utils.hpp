#pragma once

#include "SFML/Graphics/Rect.hpp"

class Utils {
public:
  static sf::Vector2f getFloatRectCenter(const sf::FloatRect& rect);
};
