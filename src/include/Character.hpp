#pragma once

#include "CharacterPhysicsBehavior.hpp"
#include "Displayable.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum Direction { LEFT, RIGHT };

class Character : public PhysicsEntity, public Displayable {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

  std::unique_ptr<PhysicsBehavior> ptr_physicsBehavior;

  void display(sf::RenderWindow &window) override;

public:
  Character(const sf::Vector2f &position);

  ~Character(void);

  void move(const Direction direction);

  void jump(void);

  void physicsTick(void) override;
};
