#pragma once

#include "SFML/Graphics/Rect.hpp"

#define IS_DEBUG_MODE true

class Utils {
public:
  static sf::Vector2f getFloatRectCenter(const sf::FloatRect& rect);
};

enum Direction { NEUTRAL, LEFT, RIGHT };
