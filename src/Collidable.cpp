#include "include/Collidable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "include/Utils.hpp"
#include <optional>
#include <vector>

Collidable::Collidable() : Collidable(std::vector<sf::FloatRect>()) {};

Collidable::Collidable(const std::vector<sf::FloatRect>& hitboxes)
    : m_relativeHitboxes(hitboxes), m_absoluteHitboxes(hitboxes) {};

std::optional<HitboxesPair>
Collidable::getCollidingHitbox(const Collidable& other) const {
  for (const auto& myHitbox : m_absoluteHitboxes) {
    for (const auto& otherHitbox : other.m_absoluteHitboxes) {
      if (myHitbox.intersects(otherHitbox)) {
        return std::make_optional<HitboxesPair>(
            HitboxesPair{myHitbox, otherHitbox});
      }
    }
  }
  return std::nullopt;
};

void Collidable::updateHitboxesPosition(const sf::Vector2f& newPosition) {
  m_absoluteHitboxes.clear();
  for (const auto& relativeHitbox : m_relativeHitboxes) {
    const auto absoluteHitbox = sf::FloatRect(
        relativeHitbox.getPosition() + newPosition, relativeHitbox.getSize());
    m_absoluteHitboxes.push_back(absoluteHitbox);
  }
}

Collision Collidable::GetCollision(const HitboxesPair& hitboxesPair) {
  const auto& hitbox1 = hitboxesPair.myHitbox;
  const auto& hitbox2 = hitboxesPair.otherHitbox;

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

void Collidable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!IS_DEBUG_MODE) {
    return;
  }
  for (const auto& hitbox : m_absoluteHitboxes) {
    auto rect = sf::RectangleShape(hitbox.getSize());
    rect.setPosition(hitbox.getPosition());
    rect.setFillColor(sf::Color(255, 0, 0, 100));
    target.draw(rect);
  }
}
