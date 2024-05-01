#pragma once

#include "SFML/System/Vector2.hpp"

class PhysicsBody {
protected:
  virtual void applyForce(const sf::Vector2f &force) = 0;

public:
  sf::Vector2f position;

  sf::Vector2f velocity;

  const float maxVelocityX;
  const float maxVelocityY;
  const float accelerationFactor;

  PhysicsBody(const sf::Vector2f &position, const float maxVelocityX,
              const float maxVelocityY, const float accelerationFactor)
      : position(position), maxVelocityX(maxVelocityX),
        maxVelocityY(maxVelocityY), accelerationFactor(accelerationFactor) {};

  virtual void physicsTick(void) = 0;

  virtual ~PhysicsBody(void) = default;
};
