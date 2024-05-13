#pragma once

#include "Character.hpp"
#include "Collidable.hpp"
#include "Map.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"
#include "Sword.hpp"
#include <memory>
#include <vector>

#define WORLD World::GetInstance()

class World : public sf::Drawable {
private:
  std::vector<std::shared_ptr<sf::Drawable>> m_ptr_drawables;

public:
  static World& GetInstance(void);

  void process(const float delta);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

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
