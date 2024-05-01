#include "include/Character.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/Displayable.hpp"
#include "include/PhysicsBody.hpp"
#include <system_error>

namespace Constants {
constexpr float characterMaxVelocityX = 6.0f;
constexpr float characterAccelerationFactor = 1.0f;
constexpr float characterDecelerationFactor = 0.2f;
const std::string characterTextureFilepath = "./assets/textures/sample.jpg";
} // namespace Constants

Character::Character(const sf::Vector2f &position)
    : PhysicsBody{position, Constants::characterMaxVelocityX,
                  Constants::characterAccelerationFactor,
                  Constants::characterDecelerationFactor},
      Displayable(Constants::characterTextureFilepath) {};

Character::~Character(void) {};

void Character::physicsTick(void) {
  // Updates position
  position += velocity;

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
};

void Character::applyForce(const sf::Vector2f &force) {
  velocity += force;

  velocity.x = std::clamp(velocity.x, -maxVelocityX, maxVelocityX);
  velocity.y = std::min(velocity.y, Constants::gravity);
};

void Character::move(const Direction direction) {
  switch (direction) {
  case Direction::LEFT:
    applyForce(sf::Vector2f(-accelerationFactor, 0.0f));
    break;
  case Direction::RIGHT:
    applyForce(sf::Vector2f(accelerationFactor, 0.0f));
    break;
  }
}

void Character::jump(void) {
  // TODO: collides with the ground
  if (position.y >= Constants::groundLevel) {
    applyForce(sf::Vector2f(0.0f, -15.0f));
  }
}

void Character::display(sf::RenderWindow &window) {
  Displayable::display(window);
  updateSpritePosition(position);
}
