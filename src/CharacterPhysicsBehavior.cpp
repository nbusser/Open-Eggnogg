#include "include/CharacterPhysicsBehavior.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/PhysicsBehavior.hpp"
#include <algorithm>

namespace Constants {
constexpr float characterMax_velocityX = 4.0f;
constexpr float characterAccelerationFactor = 1.0f;
constexpr float characterDecelerationFactor = 0.2f;
} // namespace Constants

CharacterPhysicsBehavior::CharacterPhysicsBehavior(const sf::Vector2f& position)
    : PhysicsBehavior(position, Constants::characterMax_velocityX,
                      Constants::characterAccelerationFactor,
                      Constants::characterDecelerationFactor) {};

void CharacterPhysicsBehavior::physicsTick(void) {
  // Deceleration
  if (m_velocity.x > 0) {
    m_velocity.x = std::max(0.0f, m_velocity.x - m_decelerationFactor);
  } else if (m_velocity.x < 0) {
    m_velocity.x = std::min(0.0f, m_velocity.x + m_decelerationFactor);
  }

  // Gravity
  applyForce(Constants::gravityVector);

  PhysicsBehavior::physicsTick();
}
