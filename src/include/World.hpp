#include "Character.hpp"
#include "Collidable.hpp"
#include "Displayable.hpp"
#include "Map.hpp"
#include "PhysicsEntity.hpp"
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
};
