#pragma once

#include "Collidable.hpp"

class CollisionBehavior {
public:
  virtual bool canBePushed(const Axis& axis) const = 0;
  virtual void setUnpushable(const Axis& axis) = 0;
  virtual void reset(void) = 0;
};
