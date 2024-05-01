#include "Character.hpp"
#include "Displayable.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <system_error>

#define CHARACTER_TEXTURE "./assets/textures/sample.jpg"
#define CHARACTER_MAX_VELOCITY_VALUE 7.0
#define CHARACTER_ACCELERATION_FACTOR 1.0

Character::Character(const sf::Vector2f &position)
    : PhysicsBody{position, CHARACTER_MAX_VELOCITY_VALUE,
                  CHARACTER_ACCELERATION_FACTOR},
      Displayable(CHARACTER_TEXTURE) {};

Character::~Character(void) {};

void Character::physicsTick(void) { position += velocity; };

void Character::applyForce(const sf::Vector2f &force) {
  velocity += force;

  velocity.x = std::clamp(velocity.x, -maxVelocityValue, maxVelocityValue);
  velocity.y = std::clamp(velocity.y, -maxVelocityValue, maxVelocityValue);
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
