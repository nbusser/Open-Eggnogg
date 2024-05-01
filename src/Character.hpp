#pragma once

#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Character : public PhysicsBody {
private:
  sf::Sprite sprite;

public:
  Character(const sf::Vector2f &position);

  ~Character() override;

  void physicsTick() override;

  void applyForce(const sf::Vector2f force) override;
};
