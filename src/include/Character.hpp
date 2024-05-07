#pragma once

#include "CharacterDisplayBehavior.hpp"
#include "Collidable.hpp"
#include "DisplayBehavior.hpp"
#include "Displayable.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

enum Direction { LEFT, RIGHT };

class Character : public PhysicsEntity, public Displayable, public Collidable {
private:
  std::unique_ptr<CharacterDisplayBehavior> m_ptr_displayBehavior;

  virtual void display(sf::RenderTarget& target) override;

public:
  Character(const sf::Vector2f& position);

  ~Character(void);

  void move(const Direction direction);

  void jump(void);

  void physicsTick(void) override;

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;

  void updateSpeed(sf::Vector2f force);

  // std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior;
};
