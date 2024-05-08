#pragma once

#include "Character.hpp"
#include "Collidable.hpp"
#include "Displayable.hpp"
#include "Map.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"
#include "Sword.hpp"
#include <memory>
#include <vector>

#define WORLD World::GetInstance()

class World : public Displayable {
private:
  std::vector<std::shared_ptr<Displayable>> m_ptr_displayables;

public:
  static World& GetInstance(void);

  void process(const float delta);

  virtual void display(sf::RenderTarget& target, const float delta);

  std::shared_ptr<Map> m_ptr_map;
  std::vector<std::shared_ptr<Character>> m_ptr_characters;
  std::vector<std::shared_ptr<Sword>> m_ptr_swords;

private:
  World(void);

  World(const World&) = delete;
  World& operator=(const World&) = delete;

  void resolvePlayerToMapCollision(const Character& player,
                                   const Collision& collision) const;
  void resolvePlayerToPlayerCollision(const Character& player1,
                                      const Character& player2,
                                      const Collision& collision,
                                      const bool player1CanBePushed,
                                      const bool player2CanBePushed) const;
};
