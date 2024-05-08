#include "include/World.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/Map.hpp"
#include "include/PhysicsEntity.hpp"
#include "include/Utils.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#define GET_PLAYER(i) ptr_Characters[i]

std::shared_ptr<Map> World::ptr_Map = nullptr;
std::vector<std::shared_ptr<Character>> World::ptr_Characters = {};

void World::Init(void) {
  World::ptr_Map = std::make_shared<Map>();
  World::ptr_Characters.push_back(
      std::make_shared<Character>(sf::Vector2f(-64.0f, 32.0f)));
  World::ptr_Characters.push_back(
      std::make_shared<Character>(sf::Vector2f(64.0f, 32.0f)));
}

World::World(void) {
  m_ptr_displayables = std::vector<std::shared_ptr<Displayable>>{
      ptr_Characters[0], ptr_Characters[1], ptr_Map};

  m_ptr_collidables = std::vector<std::shared_ptr<Collidable>>{
      ptr_Characters[0], ptr_Characters[1], ptr_Map};

  ptr_Map->loadMap("./assets/maps/sample.png");
}

void World::process(const float delta) {
  // Pressed inputs processing
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    GET_PLAYER(0)->move(Direction::LEFT, delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    GET_PLAYER(0)->move(Direction::RIGHT, delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    GET_PLAYER(0)->jump(delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    GET_PLAYER(1)->move(Direction::LEFT, delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    GET_PLAYER(1)->move(Direction::RIGHT, delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    GET_PLAYER(1)->jump(delta);

  // for (const auto& ptr_physicsBody : m_ptr_characters) {
  //   ptr_physicsBody->physicsTick();
  // }

  for (size_t i = 0; i < ptr_Characters.size(); ++i) {
    const auto player = ptr_Characters[i];
    const auto otherPlayer = ptr_Characters[(i + 1) % 2];

    // Decelerate
    // TODO: if no input
    const auto decelerationAmount = 7.0f * delta;
    if (player->m_velocity.x > 0) {
      player->m_velocity.x =
          std::max(0.0f, player->m_velocity.x - decelerationAmount);
    } else if (player->m_velocity.x < 0) {
      player->m_velocity.x =
          std::min(0.0f, player->m_velocity.x + decelerationAmount);
    }

    // Apply gravity
    player->updateSpeed(Constants::gravityVector * delta);

    player->m_remainder.x += std::abs(player->m_velocity.x);
    player->m_remainder.y += std::abs(player->m_velocity.y);

    // Move X
    const auto directionX = player->m_velocity.x < 0 ? -1 : 1;

    auto amountToMoveX = std::abs(std::round(player->m_remainder.x));

    if (amountToMoveX > 0) {
      player->m_remainder.x -= amountToMoveX;
    }

    while (amountToMoveX-- > 0) {
      // Move hitboxes 1 pixel into direction
      player->updateHitboxesPosition(player->m_position +
                                     sf::Vector2f(directionX, 0.0f));

      // Test collisions against map
      const auto collidingMapHitboxes = player->getCollidingHitbox(*ptr_Map);
      if (collidingMapHitboxes != nullptr) {
        const auto collision = Collidable::GetCollision(*collidingMapHitboxes);
        if (collision.axis == Axis::X) {
          // TODO: check if collision occurs on axis X
          // Collision againt map detected
          player->m_velocity.x = 0;
          break;
        }
      }

      // Test collisions against player
      const auto collidingPlayerHitboxes =
          player->getCollidingHitbox(*otherPlayer);
      if (collidingPlayerHitboxes != nullptr) {
        // TODO: check if collision occurs on axis X
        // Collision againt player detected
        player->m_velocity.x = 0;
        break;
      }

      // No obstacle, apply position
      player->m_position.x += directionX;
    }
    player->updateHitboxesPosition(player->m_position);

    // Move Y
    const auto directionY = player->m_velocity.y < 0 ? -1 : 1;
    auto amountToMoveY = std::abs(std::round(player->m_remainder.y));

    if (amountToMoveY > 0) {
      player->m_remainder.y -= amountToMoveY;
    }

    while (amountToMoveY-- > 0) {
      // Move hitboxes 1 pixel into direction
      player->updateHitboxesPosition(player->m_position +
                                     sf::Vector2f(0.0f, directionY));

      // Test collisions against map
      const auto collidingMapHitboxes = player->getCollidingHitbox(*ptr_Map);
      if (collidingMapHitboxes != nullptr) {
        // TODO: check if collision occurs on axis Y
        // Collision againt map detected
        player->m_velocity.y = 0;

        // If is falling
        if (directionY > 0) {
          player->m_isGrounded = true;
        }

        break;
      }

      // Test collisions against player
      const auto collidingPlayerHitboxes =
          player->getCollidingHitbox(*otherPlayer);
      if (collidingPlayerHitboxes != nullptr) {
        // TODO: check if collision occurs on axis Y
        // Collision againt player detected
        player->m_velocity.y = 0;
        break;
      }

      // No obstacle, apply position
      player->m_position.y += directionY;
    }
    player->updateHitboxesPosition(player->m_position);
  }
}

void World::display(sf::RenderTarget& target, const float delta) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target, delta);
  }
}
