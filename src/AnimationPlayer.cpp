#include "include/AnimationPlayer.hpp"

AnimationPlayer::AnimationPlayer(sf::Sprite &ptr_sprite)
    : m_ptr_sprite(&ptr_sprite) {
  resetCounters();
};

void AnimationPlayer::update(void) {
  // TODO: advance in animation
}

void AnimationPlayer::resetCounters(void) {
  m_frameCounter = 0;
  m_currentFrame = 0;
  m_ptr_currentAnimation = nullptr;
}

void AnimationPlayer::play(const Animation &animation) {
  m_frameCounter = 0;
  m_currentFrame = 0;
};

void AnimationPlayer::stop(void) {

};
