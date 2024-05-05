#pragma once

#import "CollisionBehavior.hpp"
#include "PhysicsBehavior.hpp"
#include <memory>

class PushableCollisionBehavior : public CollisionBehavior {
private:
  bool m_isPushableX;
  bool m_isPushableY;
  std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior;

public:
  PushableCollisionBehavior(
      const std::shared_ptr<PhysicsBehavior> m_ptr_physicsBehavior);

  virtual bool canBePushed(const Axis& axis) const override;
  virtual void setUnpushable(const Axis& axis) override;
  virtual void reset(void) override;
};
