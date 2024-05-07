#include "include/Character.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/Animations.hpp"
#include "include/CharacterDisplayBehavior.hpp"
#include "include/CharacterPhysicsBehavior.hpp"
#include "include/Collidable.hpp"
#include "include/DisplayBehavior.hpp"
#include "include/Utils.hpp"
#include <cstdlib>
#include <iostream>
#include <system_error>
#include <vector>

Character::Character(const sf::Vector2f& position)
    : m_ptr_displayBehavior(std::make_unique<CharacterDisplayBehavior>()),
      m_position(position), m_velocity(sf::Vector2f(0.0f, 0.0f)),
      m_isGrounded(false) {
  // Play idle anim
  m_ptr_displayBehavior->playAnimation(Animations::playerIdleAnimation);

  // Set player's hitbox
  const auto hitbox =
      sf::FloatRect(sf::Vector2f(3.0f, 1.0f), sf::Vector2f(9.0f, 15.0f));
  m_relativeHitboxes.push_back(hitbox);
  // Shift the hitbox with player's position
  updateHitboxesPosition(position);
};

Character::~Character(void) {};

void Character::updateSpeed(sf::Vector2f force) {
  m_velocity += force;

  constexpr float characterMax_velocityX = 4.0f;

  m_velocity.x =
      std::clamp(m_velocity.x, -characterMax_velocityX, characterMax_velocityX);
  m_velocity.y = std::clamp(m_velocity.y, -15.0f, Constants::gravity);
}

void Character::move(const Direction direction) {
  switch (direction) {
  case Direction::LEFT:
    updateSpeed(sf::Vector2f(-1.0f, 0.0f));
    break;
  case Direction::RIGHT:
    updateSpeed(sf::Vector2f(1.0f, 0.0f));
    break;
  }
}

void Character::jump(void) {
  // TODO: collides with the ground
  if (m_isGrounded) {
    updateSpeed(sf::Vector2f(0.0f, -15.0f));
    m_isGrounded = false;
  }
}

void Character::display(sf::RenderTarget& target) {
  m_ptr_displayBehavior->update(m_position);
  target.draw(*m_ptr_displayBehavior);
}

void Character::physicsTick() {
  //   m_ptr_physicsBehavior->physicsTick();
  //   updateHitboxesPosition(m_ptr_physicsBehavior->m_position);
}
