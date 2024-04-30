#include "SFML/System/Vector2.hpp"

#ifndef BODY_HPP
#define BODY_HPP

class PhysicsBody {
public:
  sf::Vector2f position;

  sf::Vector2f velocity;

  PhysicsBody(const sf::Vector2f &position) : position(position) {};

  virtual void physicsTick() = 0;

  virtual void applyForce(const sf::Vector2f force) = 0;
};

#endif
