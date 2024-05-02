#pragma once

#include "SFML/System/Vector2.hpp"

namespace Constants {
constexpr float gravity = 2.0f;
const auto gravityVector = sf::Vector2f(0.0f, gravity);
constexpr float groundLevel = 150.0f;
} // namespace Constants

class PhysicsBehavior {
public:
  sf::Vector2f position;

  sf::Vector2f velocity;

  const float maxVelocityX;
  const float accelerationFactor;
  const float decelerationFactor;

  PhysicsBehavior(const sf::Vector2f &position, const float maxVelocityX,
                  const float accelerationFactor,
                  const float decelerationFactor)
      : position(position), maxVelocityX(maxVelocityX),
        accelerationFactor(accelerationFactor),
        decelerationFactor(decelerationFactor) {};
  virtual ~PhysicsBehavior(void) = default;

  virtual void applyForce(const sf::Vector2f &force);
  virtual void physicsTick(void);
};
