#include "include/CharacterPhysicsBehavior.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/PhysicsBehavior.hpp"
#include <algorithm>

namespace Constants {
constexpr float characterMaxm_velocityX = 6.0f;
constexpr float characterAccelerationFactor = 1.0f;
constexpr float characterDecelerationFactor = 0.2f;
} // namespace Constants

CharacterPhysicsBehavior::CharacterPhysicsBehavior(const sf::Vector2f& position)
    : PhysicsBehavior(position, Constants::characterMaxm_velocityX,
                      Constants::characterAccelerationFactor,
                      Constants::characterDecelerationFactor) {};

void CharacterPhysicsBehavior::physicsTick(void) {
  PhysicsBehavior::physicsTick();

  // Deceleration
  if (m_velocity.x > 0) {
    m_velocity.x = std::max(0.0f, m_velocity.x - m_decelerationFactor);
  } else if (m_velocity.x < 0) {
    m_velocity.x = std::min(0.0f, m_velocity.x + m_decelerationFactor);
  }

  // Gravity
  // TODO: if in air
  if (m_position.y < Constants::groundLevel) {
    applyForce(Constants::gravityVector);
  } else {
    m_velocity.y = 0.0f;
  }
}
