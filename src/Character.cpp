#include "Character.hpp"
#include "Displayable.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <system_error>

namespace Constants {
constexpr float characterMaxVelocityX = 10.0f;
constexpr float characterMaxVelocityY = 10.0f;
constexpr float characterAccelerationFactor = 1.0f;
const std::string characterTextureFilepath = "./assets/textures/sample.jpg";
} // namespace Constants

Character::Character(const sf::Vector2f &position)
    : PhysicsBody{position, Constants::characterMaxVelocityX,
                  Constants::characterMaxVelocityY,
                  Constants::characterAccelerationFactor},
      Displayable(Constants::characterTextureFilepath) {};

Character::~Character(void) {};

void Character::physicsTick(void) { position += velocity; };

void Character::applyForce(const sf::Vector2f &force) {
  velocity += force;

  velocity.x = std::clamp(velocity.x, -maxVelocityX, maxVelocityX);
  velocity.y = std::clamp(velocity.y, -maxVelocityY, maxVelocityY);
};

void Character::move(const Direction direction) {
  switch (direction) {
  case Direction::LEFT:
    applyForce(sf::Vector2f(-accelerationFactor, 0.0));
    break;
  case Direction::RIGHT:
    applyForce(sf::Vector2f(accelerationFactor, 0.0));
    break;
  }
}

void Character::display(sf::RenderWindow &window) {
  Displayable::display(window);
  updateSpritePosition(position);
}
