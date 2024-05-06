#pragma once

#include "CollisionBehavior.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <vector>

struct HitboxesPair {
  std::unique_ptr<sf::FloatRect> ptr_myHitbox;
  std::unique_ptr<sf::FloatRect> ptr_otherHitbox;
};

class Collidable {
public:
  std::vector<sf::FloatRect> m_relativeHitboxes;
  std::vector<sf::FloatRect> m_absoluteHitboxes;

  std::unique_ptr<CollisionBehavior> m_ptr_collisionBehavior;

  Collidable(std::unique_ptr<CollisionBehavior> ptr_collisionBehavior);
  Collidable(std::unique_ptr<CollisionBehavior> ptr_collisionBehavior,
             const std::vector<sf::FloatRect>& hitboxes);

  std::unique_ptr<HitboxesPair>
  getCollidingHitbox(const Collidable& other) const;

  void updateHitboxesPosition(const sf::Vector2f& newPosition);

  virtual void resolveCollision(const HitboxesPair& hitboxPair);
};
