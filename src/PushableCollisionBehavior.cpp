#import "include/PushableCollisionBehavior.hpp"

PushableCollisionBehavior::PushableCollisionBehavior(
    const std::shared_ptr<PhysicsBehavior> ptr_physicsBehavior)
    : m_ptr_physicsBehavior(ptr_physicsBehavior), m_isPushableX(true),
      m_isPushableY(true) {};

bool PushableCollisionBehavior::canBePushed(const Axis& axis) const {
  if (axis == Axis::X)
    return m_isPushableX;
  return m_isPushableY;
}

void PushableCollisionBehavior::setUnpushable(const Axis& axis) {
  if (axis == Axis::X)
    m_isPushableX = false;
  else
    m_isPushableY = false;
}

void PushableCollisionBehavior::reset(void) {
  m_isPushableX = true;
  m_isPushableY = true;
}
