#include "include/World.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/Map.hpp"
#include "include/PhysicsEntity.hpp"
#include "include/Sword.hpp"
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
  const auto player1 = std::make_shared<Character>(sf::Vector2f(-16.0f, 32.0f),
                                                   Direction::RIGHT);
  const auto player2 =
      std::make_shared<Character>(sf::Vector2f(64.0f, 32.0f), Direction::LEFT);

  m_ptr_characters = std::vector<std::shared_ptr<Character>>{player1, player2};

  const auto ptr_sword = std::make_shared<Sword>();
  ptr_sword->attachTo(player1);
  m_ptr_swords = std::vector<std::shared_ptr<Sword>>{ptr_sword};

  m_ptr_displayables = std::vector<std::shared_ptr<Displayable>>{
      player1, player2, m_ptr_map, ptr_sword};

  m_ptr_map->loadMap("./assets/maps/sample.png");
}

void World::process(const float delta) {
  // Pressed inputs processing
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    GET_PLAYER(0)->inputDirection(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    GET_PLAYER(0)->inputDirection(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    GET_PLAYER(0)->inputJump(delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
    GET_PLAYER(0)->inputAttack();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    GET_PLAYER(1)->inputDirection(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    GET_PLAYER(1)->inputDirection(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    GET_PLAYER(1)->inputJump(delta);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    GET_PLAYER(1)->inputAttack();

  for (size_t i = 0; i < m_ptr_characters.size(); ++i) {
    const auto player = m_ptr_characters[i];

    player->tickTimers(delta);
    player->physicsTick(delta);
    player->move();
  }
}

void World::display(sf::RenderTarget& target, const float delta) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target, delta);
  }
}
