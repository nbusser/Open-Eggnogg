#pragma once

#include "SFML/System/Vector2.hpp"

class PhysicsBody {
protected:
  virtual void applyForce(const sf::Vector2f &force) = 0;

public:
  sf::Vector2f position;

  sf::Vector2f velocity;

  PhysicsBody(const sf::Vector2f &position) : position(position) {};

  virtual void physicsTick(void) = 0;

  virtual ~PhysicsBody(void) = default;
};
