#pragma once

#include "CharacterDisplayBehavior.hpp"
#include "Collidable.hpp"
#include "PhysicsBehavior.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "Timer.hpp"
#include "Utils.hpp"
#include <cstdint>

namespace Constants {
// Physics
constexpr float characterMaxVelocityX = 2.0f;
constexpr float characterMinVelocityY = -2.2f;
constexpr float characterJumpForce = -40.0f - Constants::gravity;
constexpr float characterAccelerationFactor = 15.0f;
constexpr float characterDecelerationFactor = 7.0f;
constexpr std::uint16_t characterJumpHeightPixel = 24;

// Timers
constexpr float characterMarsupialStunDuration = 0.3f;
constexpr float respawnDuration = 2.0f;
constexpr float attackForwardPhaseDuration = 0.2f;
constexpr float attackBackwardPhaseDuration = 0.1f;
constexpr float attackNeutralPhaseDuration = 0.2f;
} // namespace Constants

enum TimedAction {
  STUN,
  RESPAWN,
  ATTACK_FORWARD,
  ATTACK_BACKWARD,
  ATTACK_NEUTRAL,
  TOTAL,
};

class Character : public PhysicsEntity, public sf::Drawable {
private:
  CharacterDisplayBehavior m_displayBehavior;

  std::shared_ptr<Character> getOtherCharacter(void) const;

  Direction m_direction;
  Direction m_input_direction;

  std::uint16_t m_pixelsJumpingLeft;

  // Has one timer for each (indexed) TimedAction
  std::vector<Timer> m_timers;
  bool isPerformingAction(const TimedAction action) const;

  void jump(void);
  void interruptJump(void);

  bool isControllable(void) const;
  void respawn(void);

  void kill(void);

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

  void process(const float delta);

  void move(void);

  void tickTimers(const float delta);

  void physicsTick(const float delta);

  virtual void moveX(const float amount) override;
  virtual void moveY(const float amount) override;

  void endureMarsupialJump(void);
  void endStun(void);
  void endAttack(void);

  void endureAttack(void);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  // std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior;
};
