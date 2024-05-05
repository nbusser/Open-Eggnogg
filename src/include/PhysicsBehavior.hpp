#pragma once

#include "SFML/System/Vector2.hpp"

namespace Constants {
constexpr float gravity = 2.0f;
const auto gravityVector = sf::Vector2f(0.0f, gravity);
constexpr float groundLevel = 32.0f;
} // namespace Constants

class PhysicsBehavior {
public:
  sf::Vector2f m_position;

  sf::Vector2f m_velocity;

  const float m_maxVelocityX;
  const float m_accelerationFactor;
  const float m_decelerationFactor;

  PhysicsBehavior(const sf::Vector2f& position, const float maxVelocityX,
                  const float accelerationFactor,
                  const float decelerationFactor)
      : m_position(position), m_maxVelocityX(maxVelocityX),
        m_accelerationFactor(accelerationFactor),
        m_decelerationFactor(decelerationFactor) {};
  virtual ~PhysicsBehavior(void) = default;

  virtual void applyForce(const sf::Vector2f& force);
  virtual void physicsTick(void);
};
