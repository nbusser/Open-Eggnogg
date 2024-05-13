#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>
#include <optional>
#include <vector>

struct HitboxesPair {
  const sf::FloatRect& myHitbox;
  const sf::FloatRect& otherHitbox;
};

enum Axis { X, Y };

struct Collision {
  std::pair<const sf::FloatRect&, const sf::FloatRect&> hitboxes;
  sf::FloatRect collisionRect;
  Axis axis;
};

class Collidable : public sf::Drawable {
public:
  std::vector<sf::FloatRect> m_relativeHitboxes;
  std::vector<sf::FloatRect> m_absoluteHitboxes;

  Collidable();
  Collidable(const std::vector<sf::FloatRect>& hitboxes);

  std::optional<HitboxesPair> getCollidingHitbox(const Collidable& other) const;

  void updateHitboxesPosition(const sf::Vector2f& newPosition);

  static Collision GetCollision(const HitboxesPair& hitboxesPair);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
