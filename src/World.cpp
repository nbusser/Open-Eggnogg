#include "include/World.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/PhysicsEntity.hpp"
#include "include/Utils.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#define GET_PLAYER(i) m_ptr_characters[i]

World::World(void) : m_ptr_map(std::make_shared<Map>()) {
  auto ptr_player1 = std::make_shared<Character>(sf::Vector2f(-64.0f, 32.0f));
  auto ptr_player2 = std::make_shared<Character>(sf::Vector2f(64.0f, 32.0f));

  m_ptr_characters =
      std::vector<std::shared_ptr<Character>>{ptr_player1, ptr_player2};

  m_ptr_displayables = std::vector<std::shared_ptr<Displayable>>{
      ptr_player1, ptr_player2, m_ptr_map};

  m_ptr_collidables = std::vector<std::shared_ptr<Collidable>>{
      ptr_player1, ptr_player2, m_ptr_map};

  m_ptr_map->loadMap("./assets/maps/sample.png");
}

void World::process(void) {
  // Pressed inputs processing
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    GET_PLAYER(0)->move(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    GET_PLAYER(0)->move(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    GET_PLAYER(0)->jump();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    GET_PLAYER(1)->move(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    GET_PLAYER(1)->move(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    GET_PLAYER(1)->jump();

  // for (const auto& ptr_physicsBody : m_ptr_characters) {
  //   ptr_physicsBody->physicsTick();
  // }

  for (size_t i = 0; i < m_ptr_characters.size(); ++i) {
    const auto player = m_ptr_characters[i];
    const auto otherPlayer = m_ptr_characters[(i + 1) % 2];

    // Decelerate
    if (player->m_velocity.x > 0) {
      player->m_velocity.x = std::max(0.0f, player->m_velocity.x - 0.2f);
    } else if (player->m_velocity.x < 0) {
      player->m_velocity.x = std::min(0.0f, player->m_velocity.x + 0.2f);
    }

    // Apply gravity
    player->updateSpeed(Constants::gravityVector);

    // Move X
    const auto directionX = player->m_velocity.x < 0 ? -1 : 1;
    auto amountToMoveX = std::abs(std::round(player->m_velocity.x));

    while (amountToMoveX-- > 0) {
      // Move hitboxes 1 pixel into direction
      player->updateHitboxesPosition(player->m_position +
                                     sf::Vector2f(directionX, 0.0f));

      // Test collisions against map
      const auto collidingMapHitboxes = player->getCollidingHitbox(*m_ptr_map);
      if (collidingMapHitboxes != nullptr) {
        // TODO: check if collision occurs on axis X
        // Collision againt map detected
        player->m_velocity.x = 0;
        break;
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
    auto amountToMoveY = std::abs(std::round(player->m_velocity.y));

    while (amountToMoveY-- > 0) {
      // Move hitboxes 1 pixel into direction
      player->updateHitboxesPosition(player->m_position +
                                     sf::Vector2f(0.0f, directionY));

      // Test collisions against map
      const auto collidingMapHitboxes = player->getCollidingHitbox(*m_ptr_map);
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

void World::display(sf::RenderTarget& target) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target);
  }
}
