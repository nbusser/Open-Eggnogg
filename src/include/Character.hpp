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
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

namespace Constants {
// Physics
constexpr float characterMaxVelocityX = 2.0f;
constexpr float characterMinVelocityY = -15.0f;
constexpr float characterJumpForce = -5.0f;
constexpr float characterAccelerationFactor = 15.0f;
constexpr float characterDecelerationFactor = 7.0f;

// Timers
constexpr float characterMarsupialStunDuration = 0.3f;
constexpr float respawnDuration = 2.0f;
constexpr float attackForwardPhaseDuration = 0.2f;
constexpr float attackBackwardPhaseDuration = 0.1f;
constexpr float attackNeutralPhaseDuration = 0.2f;
} // namespace Constants

class Character : public PhysicsEntity, public Displayable {
private:
  std::unique_ptr<CharacterDisplayBehavior> m_ptr_displayBehavior;

  virtual void display(sf::RenderTarget& target, const float delta) override;

  std::shared_ptr<Character> getOtherCharacter(void) const;

  Direction m_direction;
  Direction m_input_direction;

  Timer m_stunTimer;
  Timer m_respawnTimer;

  Timer m_attackForwardPhaseTimer;
  Timer m_attackBackwardPhaseTimer;
  Timer m_attackNeutralPhaseTimer;

  void jump();

  bool isControllable(void) const;
  void respawn(void);

public:
  Character(const sf::Vector2f& position, const Direction direction);

  ~Character(void);

  void inputDirection(const Direction direction);

  void inputJump(const float delta);

  void inputAttack(void);

  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::Vector2f m_remainder;
  Collidable m_hurtbox;
  Collidable m_hitbox;

  bool m_isGrounded;

  void updateSpeed(sf::Vector2f force);

  void move(void);

  void tickTimers(const float delta);

  void physicsTick(const float delta);

  virtual void moveX(const float amount) override;
  virtual void moveY(const float amount) override;

  void endureMarsupialJump(void);
  void endStun(void);
  void endAttack(void);

  void kill(void);

  // std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior;
};
