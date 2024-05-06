#pragma once

#include "Character.hpp"
#include "Collidable.hpp"
#include "Displayable.hpp"
#include "Map.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Rect.hpp"
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
  void process(void);

  virtual void display(sf::RenderTarget& target);

private:
  void resolvePlayerToMapCollision(const Character& player,
                                   const sf::FloatRect& hitboxPlayer,
                                   const sf::FloatRect& hitboxMap,
                                   const sf::FloatRect& collisionRect) const;
  void resolvePlayerToPlayerCollision(const Character& player1,
                                      const Character& player2,
                                      const sf::FloatRect& hitboxPlayer1,
                                      const sf::FloatRect& hitboxPlayer2,
                                      const sf::FloatRect& collisionRect) const;
};
