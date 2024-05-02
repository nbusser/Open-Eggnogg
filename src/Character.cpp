#include "include/Character.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/Displayable.hpp"
#include <system_error>

namespace Constants {
const std::string characterTextureFilepath = "./assets/textures/sample.jpg";
} // namespace Constants

Character::Character(const sf::Vector2f &position)
    : Displayable(Constants::characterTextureFilepath),
      ptr_physicsBehavior(
          std::make_unique<CharacterPhysicsBehavior>(position)) {};

Character::~Character(void) {};

void Character::move(const Direction direction) {
  switch (direction) {
  case Direction::LEFT:
    ptr_physicsBehavior->applyForce(
        sf::Vector2f(-ptr_physicsBehavior->accelerationFactor, 0.0f));
    break;
  case Direction::RIGHT:
    ptr_physicsBehavior->applyForce(
        sf::Vector2f(ptr_physicsBehavior->accelerationFactor, 0.0f));
    break;
  }
}

void Character::jump(void) {
  // TODO: collides with the ground
  if (ptr_physicsBehavior->position.y >= Constants::groundLevel) {
    ptr_physicsBehavior->applyForce(sf::Vector2f(0.0f, -15.0f));
  }
}

void Character::display(sf::RenderWindow &window) {
  Displayable::display(window);
  updateSpritePosition(ptr_physicsBehavior->position);
}

void Character::physicsTick() { ptr_physicsBehavior->physicsTick(); }
