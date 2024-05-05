#pragma once

#include "SFML/System/Vector2.hpp"
class PhysicsEntity {
public:
  sf::Vector2f m_position;
  sf::Vector2f m_velocity;

  virtual void physicsTick(void) = 0;

  bool isMovable(void);
};
