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
  std::vector<std::shared_ptr<Displayable>> m_ptr_displayables;
  std::vector<std::shared_ptr<Collidable>> m_ptr_collidables;

public:
  static std::shared_ptr<Map> ptr_Map;
  static std::vector<std::shared_ptr<Character>> ptr_Characters;

  static void Init(void);

  World(void);
  void process(const float delta);

  virtual void display(sf::RenderTarget& target, const float delta);

private:
  void resolvePlayerToMapCollision(const Character& player,
                                   const Collision& collision) const;
  void resolvePlayerToPlayerCollision(const Character& player1,
                                      const Character& player2,
                                      const Collision& collision,
                                      const bool player1CanBePushed,
                                      const bool player2CanBePushed) const;
};
