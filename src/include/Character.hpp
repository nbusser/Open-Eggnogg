#pragma once

#include "CharacterDisplayBehavior.hpp"
#include "Collidable.hpp"
#include "Displayable.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils.hpp"

namespace Constants {
constexpr float characterMaxVelocityX = 2.0f;
constexpr float characterMinVelocityY = -15.0f;
constexpr float characterJumpForce = -5.0f;
constexpr float characterAccelerationFactor = 15.0f;
constexpr float characterDecelerationFactor = 7.0f;
} // namespace Constants

class Character : public PhysicsEntity, public Displayable, public Collidable {
private:
  std::unique_ptr<CharacterDisplayBehavior> m_ptr_displayBehavior;

  virtual void display(sf::RenderTarget& target, const float delta) override;

  std::shared_ptr<Character> getOtherCharacter(void) const;

  Direction m_direction;
  Direction m_input_direction;

public:
  Character(const sf::Vector2f& position, const Direction direction);

  ~Character(void);

  void inputDirection(const Direction direction);

  void jump(const float delta);

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::Vector2f m_remainder;

  bool m_isGrounded;

  void updateSpeed(sf::Vector2f force);

  void move(void);

  void physicsTick(const float delta);

  virtual void moveX(const float amount) override;
  virtual void moveY(const float amount) override;

  // std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior;
};
