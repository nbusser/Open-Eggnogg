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

void Collidable::resolveCollision(const HitboxesPair& hitboxesPair,
                                  const sf::FloatRect& overlapingRect) {}

void Collidable::updateHitboxesPosition(const sf::Vector2f& newPosition) {
  m_absoluteHitboxes.clear();
  for (const auto& relativeHitbox : m_relativeHitboxes) {
    const auto absoluteHitbox = sf::FloatRect(
        relativeHitbox.getPosition() + newPosition, relativeHitbox.getSize());
    m_absoluteHitboxes.push_back(absoluteHitbox);
  }
}

Collision Collidable::GetCollision(const HitboxesPair& hitboxesPair) {
  const auto& hitbox1 = *hitboxesPair.ptr_myHitbox;
  const auto& hitbox2 = *hitboxesPair.ptr_otherHitbox;

  const auto overlapPosition = sf::Vector2f(
      std::max(hitbox1.left, hitbox2.left), std::max(hitbox1.top, hitbox2.top));
  const auto overlapRect = sf::FloatRect(
      overlapPosition, sf::Vector2f(std::min(hitbox1.left + hitbox1.width,
                                             hitbox2.left + hitbox2.width),
                                    std::min(hitbox1.top + hitbox1.height,
                                             hitbox2.top + hitbox2.height)) -
                           overlapPosition);

  const auto axis =
      overlapRect.getSize().x > overlapRect.getSize().y ? Axis::Y : Axis::X;

  const Collision collision{
      std::pair<const sf::FloatRect&, const sf::FloatRect&>(hitbox1, hitbox2),
      overlapRect, axis};
  return collision;
}
