#include "include/World.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/PhysicsEntity.hpp"
#include "include/Utils.hpp"
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

  for (const auto& ptr_physicsBody : m_ptr_characters) {
    ptr_physicsBody->physicsTick();
  }

  // Collisions resolution

  // First, resolve collisions between characters and map

  auto playersPushabilities = std::vector<bool>{true, true, true, true};

  for (size_t j = 0; j < 2; ++j) {
    for (size_t i = 0; i < m_ptr_characters.size(); ++i) {
      const auto& player = m_ptr_characters[i];

      std::unique_ptr<HitboxesPair> ptr_collidingPair = nullptr;
      do {
        ptr_collidingPair = player->getCollidingHitbox(*m_ptr_map);
        if (ptr_collidingPair != nullptr) {
          const auto collision = Collidable::GetCollision(*ptr_collidingPair);
          resolvePlayerToMapCollision(*player, collision);
          player->updateHitboxesPosition(
              player->m_ptr_physicsBehavior->m_position);
          playersPushabilities[(i * 2) + collision.axis];
        }
      } while (ptr_collidingPair != nullptr);
    }

    // Then, resolve collisions between characters
    const auto player1 = m_ptr_characters[0];
    const auto player2 = m_ptr_characters[1];

    std::unique_ptr<HitboxesPair> ptr_collidingPair = nullptr;
    do {
      ptr_collidingPair = player1->getCollidingHitbox(*player2);
      if (ptr_collidingPair != nullptr) {
        const auto collision = Collidable::GetCollision(*ptr_collidingPair);

        resolvePlayerToPlayerCollision(
            *player1, *player2, collision,
            playersPushabilities[0 + collision.axis],
            playersPushabilities[2 + collision.axis]);
        player1->updateHitboxesPosition(
            player1->m_ptr_physicsBehavior->m_position);
        player2->updateHitboxesPosition(
            player2->m_ptr_physicsBehavior->m_position);
      }
    } while (ptr_collidingPair != nullptr);
  }
}

void World::display(sf::RenderTarget& target) {
  for (const auto& displayable : m_ptr_displayables) {
    displayable->display(target);
  }
}

void World::resolvePlayerToMapCollision(const Character& player,
                                        const Collision& collision) const {

  const auto& collisionRect = collision.collisionRect;
  const auto& hitboxPlayer = collision.hitboxes.first;
  const auto& hitboxMap = collision.hitboxes.second;
  const auto axis = collision.axis;

  auto restitution =
      sf::Vector2f(collisionRect.getSize().x, collisionRect.getSize().y);

  sf::Vector2f restitutionFactor;
  sf::Vector2f velocityFactor;

  // Restitution on X axis
  if (axis == Axis::X) {
    velocityFactor = sf::Vector2f(0.0f, 1.0f);
    if (hitboxPlayer.left < hitboxMap.left)
      restitutionFactor = sf::Vector2f(-1.0f, 0.0f);
    else
      restitutionFactor = sf::Vector2f(1.0f, 0.0f);
    // Restitution on Y axis
  } else {
    velocityFactor = sf::Vector2f(1.0f, 0.0f);
    if (hitboxPlayer.top < hitboxMap.top)
      restitutionFactor = sf::Vector2f(0.0f, -1.0f);
    else
      restitutionFactor = sf::Vector2f(0.0f, 1.0f);
  }
  restitution.x *= restitutionFactor.x;
  restitution.y *= restitutionFactor.y;

  player.m_ptr_physicsBehavior->m_position += restitution;
}

void World::resolvePlayerToPlayerCollision(
    const Character& player1, const Character& player2,
    const Collision& collision, const bool player1CanBePushed,
    const bool player2CanBePushed) const {

  const auto& collisionRect = collision.collisionRect;
  const auto& hitboxPlayer1 = collision.hitboxes.first;
  const auto& hitboxPlayer2 = collision.hitboxes.second;
  const auto axis = collision.axis;

  auto restitutionPlayer1 =
      sf::Vector2f(collisionRect.getSize().x, collisionRect.getSize().y);
  auto restitutionPlayer2 =
      sf::Vector2f(collisionRect.getSize().x, collisionRect.getSize().y);

  const auto collisionAxis =
      collisionRect.getSize().y > collisionRect.getSize().x ? Axis::X : Axis::Y;

  if (!player1CanBePushed && !player2CanBePushed) {
    return; // TODO
  }

  sf::Vector2f player1RestitutionFactor;
  sf::Vector2f player2RestitutionFactor;

  if (collisionAxis == Axis::X) {
    const bool isPlayer1LeftOfPlayer2 = hitboxPlayer1.left < hitboxPlayer2.left;
    player1RestitutionFactor = isPlayer1LeftOfPlayer2
                                   ? sf::Vector2f(-1.0f, 0.0f)
                                   : sf::Vector2f(1.0f, 0.0f);
    player2RestitutionFactor = isPlayer1LeftOfPlayer2
                                   ? sf::Vector2f(1.0f, 0.0f)
                                   : sf::Vector2f(-1.0f, 0.0f);
  } else {
    const bool isPlayer1TopOfPlayer2 = hitboxPlayer1.top < hitboxPlayer2.top;
    player1RestitutionFactor = isPlayer1TopOfPlayer2 ? sf::Vector2f(0.0f, -1.0f)
                                                     : sf::Vector2f(0.0f, 1.0f);
    player2RestitutionFactor = isPlayer1TopOfPlayer2
                                   ? sf::Vector2f(0.0f, 1.0f)
                                   : sf::Vector2f(0.0f, -1.0f);
  }

  if (!player1CanBePushed) {
    player1RestitutionFactor *= 0.0f;
  }
  if (!player2CanBePushed) {
    player2RestitutionFactor *= 0.0f;
  }

  if (player1CanBePushed && player2CanBePushed) {
    const float player1VelocityValue =
        collisionAxis == Axis::X ? player1.m_ptr_physicsBehavior->m_velocity.x
                                 : player1.m_ptr_physicsBehavior->m_velocity.y;
    const float player2VelocityValue =
        collisionAxis == Axis::X ? player2.m_ptr_physicsBehavior->m_velocity.x
                                 : player2.m_ptr_physicsBehavior->m_velocity.y;

    if (player1VelocityValue == player2VelocityValue) {
      player1RestitutionFactor *= 0.5f;
      player2RestitutionFactor *= 0.5f;
    } else if (player1VelocityValue > player2VelocityValue) {
      player1RestitutionFactor *= 0.0f;
    } else {
      player2RestitutionFactor *= 0.0f;
    }
  }

  // std::cout << player1RestitutionFactor.x << "," <<
  // player1RestitutionFactor.y << " - " << player2RestitutionFactor.x << "," <<
  // player2RestitutionFactor.y << std::endl;
  restitutionPlayer1.x *= player1RestitutionFactor.x;
  restitutionPlayer1.y *= player1RestitutionFactor.y;

  restitutionPlayer2.x *= player2RestitutionFactor.x;
  restitutionPlayer2.y *= player2RestitutionFactor.y;

  player1.m_ptr_physicsBehavior->m_position += restitutionPlayer1;
  player2.m_ptr_physicsBehavior->m_position += restitutionPlayer2;
}
