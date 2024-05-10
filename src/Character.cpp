#include "include/Character.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/Animations.hpp"
#include "include/CharacterDisplayBehavior.hpp"
#include "include/CharacterPhysicsBehavior.hpp"
#include "include/Collidable.hpp"
#include "include/Utils.hpp"
#include "include/World.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <system_error>
#include <vector>

#define IS_JUMPING m_pixelsJumpingLeft > 0
#define IS_STUNNED isPerformingAction(TimedAction::STUN)
#define IS_DEAD isPerformingAction(TimedAction::RESPAWN)
#define IS_ATTACKING                                                           \
  (isPerformingAction(TimedAction::ATTACK_FORWARD) ||                          \
   isPerformingAction(TimedAction::ATTACK_BACKWARD) ||                         \
   isPerformingAction(TimedAction::ATTACK_NEUTRAL))

bool Character::isPerformingAction(const TimedAction action) const {
  return m_timers[action].isRunning();
}

Character::Character(const sf::Vector2f& position, const Direction direction)
    : m_displayBehavior(CharacterDisplayBehavior()), m_position(position),
      m_velocity(sf::Vector2f(0.0f, 0.0f)), m_isGrounded(false),
      m_pixelsJumpingLeft(0), m_remainder(sf::Vector2f(0.0f, 0.0f)),
      m_direction(direction), m_input_direction(Direction::NEUTRAL),
      m_timers(std::vector<Timer>()), m_hurtbox(Collidable()),
      m_hitbox(Collidable()) {
  // Play idle anim
  m_displayBehavior.playAnimation(Animations::FullBody::playerIdle);

  // Set player's hurtbox
  const auto hurtbox =
      sf::FloatRect(sf::Vector2f(3.0f, 1.0f), sf::Vector2f(9.0f, 15.0f));
  m_hurtbox.m_relativeHitboxes.push_back(hurtbox);
  // Shift the hurtbox with player's position
  m_hurtbox.updateHitboxesPosition(position);

  // Set player's hitbox
  const auto hitbox =
      sf::FloatRect(sf::Vector2f(16.0f, 8.0f), sf::Vector2f(9.0f, 1.0f));
  m_hitbox.m_relativeHitboxes.push_back(hitbox);
  // Shift the hitbox with player's position
  m_hitbox.updateHitboxesPosition(position);

  for (size_t i = 0; i < static_cast<size_t>(TimedAction::TOTAL); ++i) {
    m_timers.push_back(Timer());
  }
};

Character::~Character(void) {};

void Character::physicsTick(const float delta) {
  // Apply acceleration regarding input direction
  const auto acceleration = Constants::characterAccelerationFactor * delta;

  switch (m_input_direction) {
  case Direction::LEFT:
    updateSpeed(sf::Vector2f(-acceleration, 0.0f));
    break;
  case Direction::RIGHT:
    updateSpeed(sf::Vector2f(acceleration, 0.0f));
    break;
  default:
    break;
  }
  // Consumes direction
  m_input_direction = Direction::NEUTRAL;

  // Apply friction
  const auto decelerationAmount =
      Constants::characterDecelerationFactor * delta;
  if (m_velocity.x > 0) {
    m_velocity.x = std::max(0.0f, m_velocity.x - decelerationAmount);
  } else if (m_velocity.x < 0) {
    m_velocity.x = std::min(0.0f, m_velocity.x + decelerationAmount);
  }

  // Character is jumping
  if (IS_JUMPING) {
    updateSpeed(sf::Vector2f(0.0f, Constants::characterJumpForce) * delta);
  }

  // Apply gravity
  updateSpeed(Constants::gravityVector * delta);

  // Switch direction
  if (isControllable()) {
    if (m_direction == Direction::RIGHT && m_velocity.x < 0.0f) {
      m_direction = Direction::LEFT;
    } else if (m_direction == Direction::LEFT && m_velocity.x > 0.0f) {
      m_direction = Direction::RIGHT;
    }
  }

  // Character is lunging forward
  const auto lungingForce = sf::Vector2f(40.0f, 0.0f) * delta *
                            (m_direction == Direction::LEFT ? -1.0f : 1.0f);
  if (m_timers[TimedAction::ATTACK_FORWARD].isRunning()) {
    updateSpeed(lungingForce);
  } else if (m_timers[TimedAction::ATTACK_BACKWARD].isRunning()) {
    updateSpeed(-lungingForce);
  }
}

void Character::updateSpeed(sf::Vector2f force) {
  m_velocity += force;

  m_velocity.x = std::clamp(m_velocity.x, -Constants::characterMaxVelocityX,
                            Constants::characterMaxVelocityX);
  m_velocity.y = std::clamp(m_velocity.y, Constants::characterMinVelocityY,
                            Constants::gravity);
}

void Character::move() {
  moveX(m_velocity.x);
  moveY(m_velocity.y);
}

std::shared_ptr<Character> Character::getOtherCharacter(void) const {
  for (const auto ptr_character : WORLD.m_ptr_characters) {
    if (ptr_character.get() != this) {
      return ptr_character;
    }
  }
  // Should never happen
  return nullptr;
}

void Character::inputDirection(const Direction direction) {
  if (isControllable()) {
    m_input_direction = direction;
  }
}

void Character::inputJump(const float delta) {
  // TODO: use delta??
  if (m_isGrounded && isControllable()) {
    jump();
  }
}

void Character::inputAttack(void) {
  if (!isControllable() || !m_isGrounded)
    return;

  m_velocity.x = 0.0f;

  m_displayBehavior.playAnimation(Animations::FullBody::playerAttack);
  m_timers[TimedAction::ATTACK_FORWARD].start(
      Constants::attackForwardPhaseDuration, [this] {
        // Run neutral timer
        const auto neutralTimerStartCallback = [this] {
          m_timers[TimedAction::ATTACK_NEUTRAL].start(
              Constants::attackNeutralPhaseDuration, [this] { endAttack(); });
        };

        // If the character is in ground after forward phase, go to backward
        // phase
        if (m_isGrounded) {
          m_timers[TimedAction::ATTACK_BACKWARD].start(
              Constants::attackBackwardPhaseDuration,
              neutralTimerStartCallback);
          // Otherwise, skips backward phase
        } else {
          neutralTimerStartCallback();
        }
      });
}

void Character::jump() {
  m_pixelsJumpingLeft = Constants::characterJumpHeightPixel;
  m_isGrounded = false;
}

void Character::interruptJump() {
  // Finish jump
  m_pixelsJumpingLeft = 0;
  m_velocity.y = 0;
}

bool Character::isControllable(void) const {
  return !IS_STUNNED && !IS_DEAD && !IS_ATTACKING;
}

void Character::endStun(void) {
  m_displayBehavior.playAnimation(Animations::FullBody::playerIdle);
}

void Character::endAttack(void) {
  m_velocity.x = 0.0f;
  m_displayBehavior.playAnimation(Animations::FullBody::playerIdle);
}

void Character::endureMarsupialJump(void) {
  m_displayBehavior.playAnimation(
      Animations::FullBody::playerEndureMarsupialJump);
  m_timers[TimedAction::STUN].start(Constants::characterMarsupialStunDuration,
                                    [this] { endStun(); });
}

void Character::tickTimers(const float delta) {
  for (auto& timer : m_timers) {
    timer.tick(delta);
  }
}

void Character::display(sf::RenderTarget& target, const float delta) {
  m_displayBehavior.update(m_position, m_direction, delta);
  target.draw(m_displayBehavior);
}

void Character::respawn(void) {
  // TODO: chose respawn position
  // TODO: reactivate hitboxes
  const sf::Vector2f respawnPosition(32.0f, 32.0f);

  m_position = respawnPosition;
  m_velocity = sf::Vector2f(0.0f, 0.0f);
  m_displayBehavior.playAnimation(Animations::FullBody::playerIdle);
}

void Character::kill(void) {
  // TODO: remove hitboxes
  m_displayBehavior.playAnimation(Animations::FullBody::playerDeath);

  // Stop all timers
  for (auto& timer : m_timers) {
    timer.stop();
  }
  m_timers[TimedAction::RESPAWN].start(Constants::respawnDuration,
                                       [this] { respawn(); });
}

void Character::endureAttack(void) {
  // TODO: check attack parameters (direction, armed/karate)
  // Determine outcome
  if (!IS_DEAD) {
    kill();
  }
}

void Character::moveX(const float amount) {
  const auto otherPlayer = getOtherCharacter();

  m_remainder.x += std::abs(amount);

  const auto directionX = amount < 0 ? -1 : 1;

  auto amountToMoveX = std::abs(std::round(m_remainder.x));

  if (amountToMoveX > 0) {
    m_remainder.x -= amountToMoveX;
  }

  while (amountToMoveX-- > 0) {
    // Move hitboxes 1 pixel into direction
    m_hurtbox.updateHitboxesPosition(m_position +
                                     sf::Vector2f(directionX, 0.0f));
    m_hitbox.updateHitboxesPosition(m_position +
                                    sf::Vector2f(directionX, 0.0f));

    // Test collisions against map
    const auto collidingMapHitboxes =
        m_hurtbox.getCollidingHitbox(*WORLD.m_ptr_map);
    if (collidingMapHitboxes.has_value()) {
      const auto collision =
          Collidable::GetCollision(collidingMapHitboxes.value());
      if (collision.axis == Axis::X) {
        // TODO: check if collision occurs on axis X
        // Collision againt map detected
        m_velocity.x = 0;
        break;
      }
    }

    // Test collisions against player

    // Hitbox
    const auto touchingOtherPlayerHurtboxWithMyHitbox =
        m_hitbox.getCollidingHitbox(otherPlayer->m_hurtbox);
    if (touchingOtherPlayerHurtboxWithMyHitbox.has_value()) {
      otherPlayer->endureAttack();
    }
    const auto touchingOtherPlayerHitboxWithMyHurtbox =
        m_hurtbox.getCollidingHitbox(otherPlayer->m_hitbox);
    if (touchingOtherPlayerHitboxWithMyHurtbox.has_value()) {
      endureAttack();
      if (IS_DEAD)
        break;
    }

    // Hurtbox
    const auto collidingPlayerHitboxes =
        m_hurtbox.getCollidingHitbox(otherPlayer->m_hurtbox);
    if (collidingPlayerHitboxes.has_value()) {
      // TODO: check if collision occurs on axis X
      // Collision againt player detected
      m_velocity.x = 0;
      break;
    }

    // No obstacle, apply position
    m_position.x += directionX;
  }
  m_hurtbox.updateHitboxesPosition(m_position);
  m_hitbox.updateHitboxesPosition(m_position);
}

void Character::moveY(const float amount) {
  const auto otherPlayer = getOtherCharacter();

  m_remainder.y += std::abs(amount);

  const auto directionY = amount < 0 ? -1 : 1;
  auto amountToMoveY = std::abs(std::round(m_remainder.y));

  if (amountToMoveY > 0) {
    m_remainder.y -= amountToMoveY;
  }

  while (amountToMoveY-- > 0) {
    // Move hitboxes 1 pixel into direction
    m_hurtbox.updateHitboxesPosition(m_position +
                                     sf::Vector2f(0.0f, directionY));
    m_hitbox.updateHitboxesPosition(m_position +
                                    sf::Vector2f(0.0f, directionY));

    // Test collisions against map
    const auto collidingMapHitboxes =
        m_hurtbox.getCollidingHitbox(*WORLD.m_ptr_map);
    if (collidingMapHitboxes.has_value()) {
      // TODO: check if collision occurs on axis Y
      // Collision againt map detected
      m_velocity.y = 0;

      // If is falling
      if (directionY > 0) {
        m_isGrounded = true;
      }

      interruptJump();

      break;
    }

    // Test collisions against player

    // Hitbox
    const auto touchingOtherPlayerHurtboxWithMyHitbox =
        m_hitbox.getCollidingHitbox(otherPlayer->m_hurtbox);
    if (touchingOtherPlayerHurtboxWithMyHitbox.has_value()) {
      otherPlayer->endureAttack();
    }
    const auto touchingOtherPlayerHitboxWithMyHurtbox =
        m_hurtbox.getCollidingHitbox(otherPlayer->m_hitbox);
    if (touchingOtherPlayerHitboxWithMyHurtbox.has_value()) {
      endureAttack();
      if (IS_DEAD)
        break;
    }

    // Hurtbox
    const auto collidingPlayerHitboxes =
        m_hurtbox.getCollidingHitbox(otherPlayer->m_hurtbox);

    // Marsupial jump
    if (collidingPlayerHitboxes.has_value()) {
      if (collidingPlayerHitboxes.value().myHitbox.top <
          collidingPlayerHitboxes.value().otherHitbox.top) {
        jump();
        otherPlayer->endureMarsupialJump();
      }
      break;
    }

    // No obstacle, apply position
    m_position.y += directionY;

    // Whatever happens, if you move vertically, it means that you are in air
    m_isGrounded = false;

    if (directionY < 0 && IS_JUMPING && --m_pixelsJumpingLeft <= 0) {
      // Finish jump
      interruptJump();
      break;
    }
  }
  m_hurtbox.updateHitboxesPosition(m_position);
  m_hitbox.updateHitboxesPosition(m_position);
}
