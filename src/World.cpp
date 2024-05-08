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

#define GET_PLAYER(i) m_ptr_characters[i]

World& World::GetInstance(void) {
  static World instance;
  return instance;
}

World::World(void) : m_ptr_map(std::make_shared<Map>()) {
  const auto player1 = std::make_shared<Character>(sf::Vector2f(-64.0f, 32.0f));
  const auto player2 = std::make_shared<Character>(sf::Vector2f(64.0f, 32.0f));

  m_ptr_characters = std::vector<std::shared_ptr<Character>>{player1, player2};

  m_ptr_displayables =
      std::vector<std::shared_ptr<Displayable>>{player1, player2, m_ptr_map};

  m_ptr_collidables =
      std::vector<std::shared_ptr<Collidable>>{player1, player2, m_ptr_map};

  m_ptr_map->loadMap("./assets/maps/sample.png");
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

  for (size_t i = 0; i < m_ptr_characters.size(); ++i) {
    const auto player = m_ptr_characters[i];

    const auto decelerationAmount =
        Constants::characterDecelerationFactor * delta;
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

    player->moveX(0.0f);
    player->moveY(0.0f);
  }
}

void World::display(sf::RenderTarget& target, const float delta) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target, delta);
  }
}
