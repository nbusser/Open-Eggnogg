#pragma once

#include "SFML/System/Vector2.hpp"
class PhysicsEntity {
public:
  virtual void moveX(const float amount) = 0;
  virtual void moveY(const float amount) = 0;
};
