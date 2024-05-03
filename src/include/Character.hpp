#pragma once

#include "CharacterPhysicsBehavior.hpp"
#include "DisplayBehavior.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum Direction { LEFT, RIGHT };

class Character : public PhysicsEntity, public sf::Drawable {
private:
  std::unique_ptr<PhysicsBehavior> ptr_physicsBehavior;
  DisplayBehavior displayBehavior;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

public:
  Character(const sf::Vector2f &position);

  ~Character(void);

  void move(const Direction direction);

  void jump(void);

  void physicsTick(void) override;
};
