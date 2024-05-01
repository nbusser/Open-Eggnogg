#pragma once

#include "SFML/System/Vector2.hpp"

namespace Constants {
constexpr float gravity = 2.0f;
const auto gravityVector = sf::Vector2f(0.0f, gravity);
constexpr float groundLevel = 150.0f;
} // namespace Constants

class PhysicsBody {
protected:
  virtual void applyForce(const sf::Vector2f &force) = 0;

public:
  sf::Vector2f position;

  sf::Vector2f velocity;

  const float maxVelocityX;
  const float accelerationFactor;
  const float decelerationFactor;

  PhysicsBody(const sf::Vector2f &position, const float maxVelocityX,
              const float accelerationFactor, const float decelerationFactor)
      : position(position), maxVelocityX(maxVelocityX),
        accelerationFactor(accelerationFactor),
        decelerationFactor(decelerationFactor) {};

  virtual void physicsTick(void) = 0;

  virtual ~PhysicsBody(void) = default;
};
