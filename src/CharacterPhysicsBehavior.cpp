#include "include/CharacterPhysicsBehavior.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/PhysicsBehavior.hpp"
#include <algorithm>

namespace Constants {
constexpr float characterMaxVelocityX = 6.0f;
constexpr float characterAccelerationFactor = 1.0f;
constexpr float characterDecelerationFactor = 0.2f;
} // namespace Constants

CharacterPhysicsBehavior::CharacterPhysicsBehavior(const sf::Vector2f &position)
    : PhysicsBehavior(position, Constants::characterMaxVelocityX,
                      Constants::characterAccelerationFactor,
                      Constants::characterDecelerationFactor) {};

void CharacterPhysicsBehavior::physicsTick(void) {
  PhysicsBehavior::physicsTick();

  // Deceleration
  if (velocity.x > 0) {
    velocity.x = std::max(0.0f, velocity.x - decelerationFactor);
  } else if (velocity.x < 0) {
    velocity.x = std::min(0.0f, velocity.x + decelerationFactor);
  }

  // Gravity
  // TODO: if in air
  if (position.y < Constants::groundLevel) {
    applyForce(Constants::gravityVector);
  } else {
    velocity.y = 0.0f;
  }
}
