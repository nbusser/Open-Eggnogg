#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>

class Collidable {
public:
  std::vector<sf::FloatRect> m_relativeHitboxes;

  std::vector<sf::FloatRect> m_absoluteHitboxes;

  Collidable();
  Collidable(const std::vector<sf::FloatRect>& hitboxes);

  bool isColliding(const Collidable& other) const;

  void updateHitboxesPosition(const sf::Vector2f newPosition);
};
