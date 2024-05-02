#pragma once

#include "PhysicsBehavior.hpp"
#include "SFML/System/Vector2.hpp"

class CharacterPhysicsBehavior : public PhysicsBehavior {
public:
  CharacterPhysicsBehavior(const sf::Vector2f &position);

  virtual void physicsTick(void) override;
};
