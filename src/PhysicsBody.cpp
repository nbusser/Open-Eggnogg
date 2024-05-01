#include "include/PhysicsBody.hpp"
#include "SFML/System/Vector2.hpp"
#include <algorithm>

void PhysicsBody::applyForce(const sf::Vector2f &force) {
  velocity += force;

  velocity.x = std::clamp(velocity.x, -maxVelocityX, maxVelocityX);
  velocity.y = std::min(velocity.y, Constants::gravity);
}

void PhysicsBody::physicsTick(void) {
  // Updates position
  position += velocity;
}
