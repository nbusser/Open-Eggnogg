#pragma once

#include "Displayable.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum Direction { LEFT, RIGHT };

class Character : public PhysicsBody, public Displayable {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

  const float acceleration = 10.0;

  void applyForce(const sf::Vector2f &force) override;

public:
  Character(const sf::Vector2f &position);

  ~Character(void) override;

  void move(const Direction direction);

  void physicsTick(void) override;
};
