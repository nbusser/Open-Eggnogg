#include "include/Character.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/DisplayBehavior.hpp"
#include <system_error>

namespace Constants {
const std::string characterTextureFilepath = "./assets/textures/sample.jpg";
} // namespace Constants

Character::Character(const sf::Vector2f &position)
    : m_ptr_physicsBehavior(
          std::make_unique<CharacterPhysicsBehavior>(position)),
      m_displayBehavior(DisplayBehavior(Constants::characterTextureFilepath)) {
      };

Character::~Character(void) {};

void Character::move(const Direction direction) {
  switch (direction) {
  case Direction::LEFT:
    m_ptr_physicsBehavior->applyForce(
        sf::Vector2f(-m_ptr_physicsBehavior->m_accelerationFactor, 0.0f));
    break;
  case Direction::RIGHT:
    m_ptr_physicsBehavior->applyForce(
        sf::Vector2f(m_ptr_physicsBehavior->m_accelerationFactor, 0.0f));
    break;
  }
}

void Character::jump(void) {
  // TODO: collides with the ground
  if (m_ptr_physicsBehavior->m_position.y >= Constants::groundLevel) {
    m_ptr_physicsBehavior->applyForce(sf::Vector2f(0.0f, -15.0f));
  }
}

void Character::display(sf::RenderTarget &target) {
  m_displayBehavior.updateSpritePosition(m_ptr_physicsBehavior->m_position);
  target.draw(m_displayBehavior);
}

void Character::physicsTick() { m_ptr_physicsBehavior->physicsTick(); }
