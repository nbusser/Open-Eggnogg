#pragma once

#include "CharacterPhysicsBehavior.hpp"
#include "DisplayBehavior.hpp"
#include "Displayable.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum Direction { LEFT, RIGHT };

class Character : public PhysicsEntity, public Displayable {
private:
  std::unique_ptr<PhysicsBehavior> m_ptr_physicsBehavior;
  DisplayBehavior m_displayBehavior;

  virtual void display(sf::RenderTarget &target) override;

public:
  Character(const sf::Vector2f &position);

  ~Character(void);

  void move(const Direction direction);

  void jump(void);

  void physicsTick(void) override;
};
