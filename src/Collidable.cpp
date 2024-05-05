#include "include/Collidable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <vector>

Collidable::Collidable() : Collidable(std::vector<sf::FloatRect>()) {};

Collidable::Collidable(const std::vector<sf::FloatRect>& hitboxes)
    : m_relativeHitboxes(hitboxes), m_absoluteHitboxes(hitboxes) {};

std::unique_ptr<HitboxesPair>
Collidable::getCollidingHitbox(const Collidable& other) const {
  for (const auto& myHitbox : m_absoluteHitboxes) {
    for (const auto& otherHitbox : other.m_absoluteHitboxes) {
      if (myHitbox.intersects(otherHitbox)) {
        return std::make_unique<HitboxesPair>(
            HitboxesPair{std::make_unique<sf::FloatRect>(myHitbox),
                         std::make_unique<sf::FloatRect>(otherHitbox)});
      }
    }
  }
  return nullptr;
};

void Collidable::resolveCollision(const HitboxesPair& other) {}

void Collidable::updateHitboxesPosition(const sf::Vector2f& newPosition) {
  m_absoluteHitboxes.clear();
  for (const auto& relativeHitbox : m_relativeHitboxes) {
    const auto absoluteHitbox = sf::FloatRect(
        relativeHitbox.getPosition() + newPosition, relativeHitbox.getSize());
    m_absoluteHitboxes.push_back(absoluteHitbox);
  }
}
