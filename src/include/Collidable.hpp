#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <vector>

struct HitboxesPair {
  std::unique_ptr<sf::FloatRect> ptr_myHitbox;
  std::unique_ptr<sf::FloatRect> ptr_otherHitbox;
};

enum Axis { X, Y };

struct Collision {
  std::pair<const sf::FloatRect&, const sf::FloatRect&> hitboxes;
  sf::FloatRect collisionRect;
  Axis axis;
};

class Collidable {
public:
  std::vector<sf::FloatRect> m_relativeHitboxes;
  std::vector<sf::FloatRect> m_absoluteHitboxes;

  Collidable();
  Collidable(const std::vector<sf::FloatRect>& hitboxes);

  std::unique_ptr<HitboxesPair>
  getCollidingHitbox(const Collidable& other) const;

  void updateHitboxesPosition(const sf::Vector2f& newPosition);

  virtual void resolveCollision(const HitboxesPair& hitboxesPair,
                                const sf::FloatRect& overlapingRect);

  static Collision GetCollision(const HitboxesPair& hitboxesPair);
};
