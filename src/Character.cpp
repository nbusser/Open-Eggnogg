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
#include "include/World.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <system_error>
#include <vector>

Character::Character(const sf::Vector2f& position)
    : m_ptr_displayBehavior(std::make_unique<CharacterDisplayBehavior>()),
      m_position(position), m_velocity(sf::Vector2f(0.0f, 0.0f)),
      m_isGrounded(false), m_remainder(sf::Vector2f(0.0f, 0.0f)) {
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

  constexpr float characterMax_velocityX = 2.0f;

  m_velocity.x =
      std::clamp(m_velocity.x, -characterMax_velocityX, characterMax_velocityX);
  m_velocity.y = std::clamp(m_velocity.y, -15.0f, Constants::gravity);
}

std::shared_ptr<Character> Character::getOtherCharacter(void) const {
  for (const auto ptr_character : WORLD.m_ptr_characters) {
    if (ptr_character.get() != this) {
      return ptr_character;
    }
  }
  // Should never happen
  return nullptr;
}

void Character::move(const Direction direction, const float delta) {
  const auto acceleration = 15.0f * delta;
  switch (direction) {
  case Direction::LEFT:
    updateSpeed(sf::Vector2f(-acceleration, 0.0f));
    break;
  case Direction::RIGHT:
    updateSpeed(sf::Vector2f(acceleration, 0.0f));
    break;
  }
}

void Character::jump(const float delta) {
  // TODO: use delta??
  if (m_isGrounded) {
    updateSpeed(sf::Vector2f(0.0f, -5.0f));
    m_isGrounded = false;
  }
}

void Character::display(sf::RenderTarget& target, const float delta) {
  m_ptr_displayBehavior->update(m_position, delta);
  target.draw(*m_ptr_displayBehavior);
}

void Character::moveX(const float amount) {
  const auto otherPlayer = getOtherCharacter();

  const auto directionX = m_velocity.x < 0 ? -1 : 1;

  auto amountToMoveX = std::abs(std::round(m_remainder.x));

  if (amountToMoveX > 0) {
    m_remainder.x -= amountToMoveX;
  }

  while (amountToMoveX-- > 0) {
    // Move hitboxes 1 pixel into direction
    updateHitboxesPosition(m_position + sf::Vector2f(directionX, 0.0f));

    // Test collisions against map
    const auto collidingMapHitboxes = getCollidingHitbox(*WORLD.m_ptr_map);
    if (collidingMapHitboxes != nullptr) {
      const auto collision = Collidable::GetCollision(*collidingMapHitboxes);
      if (collision.axis == Axis::X) {
        // TODO: check if collision occurs on axis X
        // Collision againt map detected
        m_velocity.x = 0;
        break;
      }
    }

    // Test collisions against player
    const auto collidingPlayerHitboxes = getCollidingHitbox(*otherPlayer);
    if (collidingPlayerHitboxes != nullptr) {
      // TODO: check if collision occurs on axis X
      // Collision againt player detected
      m_velocity.x = 0;
      break;
    }

    // No obstacle, apply position
    m_position.x += directionX;
  }
  updateHitboxesPosition(m_position);
}

void Character::moveY(const float amount) {
  const auto otherPlayer = getOtherCharacter();

  const auto directionY = m_velocity.y < 0 ? -1 : 1;
  auto amountToMoveY = std::abs(std::round(m_remainder.y));

  if (amountToMoveY > 0) {
    m_remainder.y -= amountToMoveY;
  }

  while (amountToMoveY-- > 0) {
    // Move hitboxes 1 pixel into direction
    updateHitboxesPosition(m_position + sf::Vector2f(0.0f, directionY));

    // Test collisions against map
    const auto collidingMapHitboxes = getCollidingHitbox(*WORLD.m_ptr_map);
    if (collidingMapHitboxes != nullptr) {
      // TODO: check if collision occurs on axis Y
      // Collision againt map detected
      m_velocity.y = 0;

      // If is falling
      if (directionY > 0) {
        m_isGrounded = true;
      }

      break;
    }

    // Test collisions against player
    const auto collidingPlayerHitboxes = getCollidingHitbox(*otherPlayer);
    if (collidingPlayerHitboxes != nullptr) {
      // TODO: check if collision occurs on axis Y
      // Collision againt player detected
      m_velocity.y = 0;
      break;
    }

    // No obstacle, apply position
    m_position.y += directionY;
  }
  updateHitboxesPosition(m_position);
}
