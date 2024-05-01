#pragma once

#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Character : public PhysicsBody {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

public:
  Character(const sf::Vector2f &position);

  ~Character(void) override;

  void physicsTick(void) override;

  void applyForce(const sf::Vector2f force) override;
};
