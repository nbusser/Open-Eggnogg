#include "include/Utils.hpp"

sf::Vector2f Utils::getFloatRectCenter(const sf::FloatRect& rect) {
  float centerX = rect.left + rect.width / 2.0f;
  float centerY = rect.top + rect.height / 2.0f;
  return sf::Vector2f(centerX, centerY);
}
