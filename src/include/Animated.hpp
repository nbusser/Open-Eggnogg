#pragma once

#include "AnimationPlayer.hpp"

class Animated {
protected:
  AnimationPlayer m_animationPlayer;

public:
  Animated(const AnimationPlayer& animationPlayer);
  ~Animated(void) = default;

  void playAnimation(const Animation& animation);
  void stopAnimation(void);
};
