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
#include <system_error>
#include <vector>

Character::Character(const sf::Vector2f& position)
    : Collidable(), m_ptr_physicsBehavior(
                        std::make_unique<CharacterPhysicsBehavior>(position)),
      m_ptr_displayBehavior(std::make_unique<CharacterDisplayBehavior>()) {
  {
    // Play idle anim
    m_ptr_displayBehavior->playAnimation(Animations::playerIdleAnimation);

    // Set player's hitbox
    const auto hitbox =
        sf::FloatRect(sf::Vector2f(3.0f, 1.0f), sf::Vector2f(9.0f, 15.0f));
    m_relativeHitboxes.push_back(hitbox);
    // Shift the hitbox with player's position
    updateHitboxesPosition(position);
  };
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

void Character::display(sf::RenderTarget& target) {
  m_ptr_displayBehavior->update(m_ptr_physicsBehavior->m_position);
  target.draw(*m_ptr_displayBehavior);
}

void Character::physicsTick() {
  m_ptr_physicsBehavior->physicsTick();
  updateHitboxesPosition(m_ptr_physicsBehavior->m_position);
}

void Character::resolveCollision(const HitboxesPair& hitboxPair) {
  const auto& myHitbox = *hitboxPair.ptr_myHitbox;
  const auto& otherHitbox = *hitboxPair.ptr_otherHitbox;

  const auto myHitboxCenter = Utils::getFloatRectCenter(myHitbox);
  const auto collidedHitboxCenter = Utils::getFloatRectCenter(otherHitbox);

  const auto overlapPosition =
      sf::Vector2f(std::max(myHitbox.left, otherHitbox.left),
                   std::max(myHitbox.top, otherHitbox.top));
  const auto overlapRect = sf::FloatRect(
      overlapPosition,
      sf::Vector2f(std::min(myHitbox.left + myHitbox.width,
                            otherHitbox.left + otherHitbox.width),
                   std::min(myHitbox.top + myHitbox.height,
                            otherHitbox.top + otherHitbox.height)) -
          overlapPosition);

  auto restitution =
      sf::Vector2f(overlapRect.getSize().x, overlapRect.getSize().y);

  sf::Vector2f restitutionFactor;
  sf::Vector2f velocityFactor;

  // Restitution on X axis
  if (overlapRect.getSize().y > overlapRect.getSize().x) {
    velocityFactor = sf::Vector2f(0.0f, 1.0f);
    if (myHitboxCenter.x < collidedHitboxCenter.x)
      restitutionFactor = sf::Vector2f(-1.0f, 0.0f);
    else
      restitutionFactor = sf::Vector2f(1.0f, 0.0f);
    // Restitution on Y axis
  } else {
    velocityFactor = sf::Vector2f(1.0f, 0.0f);
    if (myHitboxCenter.y < collidedHitboxCenter.y)
      restitutionFactor = sf::Vector2f(0.0f, -1.0f);
    else
      restitutionFactor = sf::Vector2f(0.0f, 1.0f);
  }
  restitution.x *= restitutionFactor.x;
  restitution.y *= restitutionFactor.y;

  m_ptr_physicsBehavior->m_position += restitution;

  m_ptr_physicsBehavior->m_velocity.x *= velocityFactor.x;
  m_ptr_physicsBehavior->m_velocity.y *= velocityFactor.y;

  updateHitboxesPosition(m_ptr_physicsBehavior->m_position);
}
