#include "SFML/System/Vector2.hpp"
#include "include/PhysicsBehavior.hpp"
#include <algorithm>

void PhysicsBehavior::applyForce(const sf::Vector2f &force) {
  velocity += force;

  velocity.x = std::clamp(velocity.x, -maxVelocityX, maxVelocityX);
  velocity.y = std::min(velocity.y, Constants::gravity);
}

void PhysicsBehavior::physicsTick(void) {
  // Updates position
  position += velocity;
}
