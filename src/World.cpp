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

    player->moveX(0.0f);
    player->moveY(0.0f);
  }
}

void World::display(sf::RenderTarget& target, const float delta) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target, delta);
  }
}
