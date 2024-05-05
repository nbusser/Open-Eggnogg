#include "SFML/System/Vector2.hpp"
#include "include/PhysicsBehavior.hpp"
#include <algorithm>

void PhysicsBehavior::applyForce(const sf::Vector2f& force) {
  m_velocity += force;

  m_velocity.x = std::clamp(m_velocity.x, -m_maxVelocityX, m_maxVelocityX);
  m_velocity.y = std::clamp(m_velocity.y, -15.0f, Constants::gravity);
}

void PhysicsBehavior::physicsTick(void) {
  // Updates position
  m_position += m_velocity;
}
