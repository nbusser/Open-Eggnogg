#pragma once

#import "CollisionBehavior.hpp"

class ImmobileCollisionBehavior : public CollisionBehavior {
public:
  virtual bool canBePushed(const Axis& axis) const override { return false; };
  virtual void setUnpushable(const Axis& axis) override {};
  virtual void reset(void) override {};
};
