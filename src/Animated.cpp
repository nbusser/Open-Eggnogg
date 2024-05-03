#include "include/Animated.hpp"
#include "include/AnimationPlayer.hpp"

Animated::Animated(const AnimationPlayer& animationPlayer)
    : m_animationPlayer(animationPlayer) {};

void Animated::playAnimation(const Animation& animation) {
  m_animationPlayer.play(animation);
}

void Animated::stopAnimation(void) { m_animationPlayer.stop(); }
