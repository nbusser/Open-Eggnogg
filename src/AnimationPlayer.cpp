#include "include/AnimationPlayer.hpp"

AnimationPlayer::AnimationPlayer(std::unique_ptr<sf::Sprite> &&ptr_sprite)
    : m_ptr_sprite(std::move(ptr_sprite)) {};

void AnimationPlayer::update(void) {
  // TODO: advance in animation
}
