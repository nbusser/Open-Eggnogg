#pragma once

#include "Character.hpp"
#include "Collidable.hpp"
#include "Displayable.hpp"
#include "Map.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"
#include <memory>
#include <vector>

class World : public Displayable {
private:
  std::shared_ptr<Map> m_ptr_map;

  std::vector<std::shared_ptr<Character>> m_ptr_characters;
  std::vector<std::shared_ptr<Displayable>> m_ptr_displayables;
  std::vector<std::shared_ptr<Collidable>> m_ptr_collidables;

public:
  World(void);
  void process(const float delta);

  virtual void display(sf::RenderTarget& target);

private:
  void resolvePlayerToMapCollision(const Character& player,
                                   const Collision& collision) const;
  void resolvePlayerToPlayerCollision(const Character& player1,
                                      const Character& player2,
                                      const Collision& collision,
                                      const bool player1CanBePushed,
                                      const bool player2CanBePushed) const;
};
