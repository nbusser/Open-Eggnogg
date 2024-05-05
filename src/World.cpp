#include "include/World.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/PhysicsEntity.hpp"
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    GET_PLAYER(0)->move(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    GET_PLAYER(0)->move(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
    GET_PLAYER(0)->jump();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    GET_PLAYER(1)->move(Direction::LEFT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    GET_PLAYER(1)->move(Direction::RIGHT);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    GET_PLAYER(1)->jump();

  for (const auto& ptr_physicsBody : m_ptr_characters) {
    ptr_physicsBody->physicsTick();
  }

  for (const auto& character : m_ptr_characters) {
    for (const auto& collidable : m_ptr_collidables) {
      if (character == collidable) {
        continue;
      }
      const auto ptr_collidingPair = character->getCollidingHitbox(*collidable);
      if (ptr_collidingPair != nullptr) {
        character->resolveCollision(*ptr_collidingPair);
      }
    }
  }
}

void World::display(sf::RenderTarget& target) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target);
  }
}
