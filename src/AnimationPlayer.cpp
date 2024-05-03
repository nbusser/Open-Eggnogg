#include "include/AnimationPlayer.hpp"
#include "SFML/Graphics/Rect.hpp"

AnimationPlayer::AnimationPlayer(sf::Sprite& ptr_sprite)
    : m_ptr_sprite(&ptr_sprite) {
  resetCounters();
};

bool AnimationPlayer::isAnimationLoaded(void) const {
  return m_ptr_currentAnimation != nullptr;
}

bool AnimationPlayer::isAnimationEnded(void) const {
  return isAnimationLoaded() &&
         m_currentFrame == m_ptr_currentAnimation->textureUVs.size();
}

void AnimationPlayer::setAnimationFrame(const std::uint8_t frameIndex) {
  const auto uv = m_ptr_currentAnimation->textureUVs[frameIndex];
  const auto textureSize = m_ptr_currentAnimation->textureSize;

  const auto textureRect = sf::IntRect(uv, textureSize);
  m_ptr_sprite->setTextureRect(textureRect);
}

void AnimationPlayer::update(void) {
  if (!isAnimationLoaded()) {
    return;
  }
  if (++m_frameCounter > m_ptr_currentAnimation->nFramesPerAnimtion &&
      (m_ptr_currentAnimation->loop || !isAnimationEnded())) {
    m_frameCounter = 0;
    m_currentFrame =
        (++m_currentFrame) % m_ptr_currentAnimation->textureUVs.size();
    setAnimationFrame(m_currentFrame);
  }
}

void AnimationPlayer::resetCounters(void) {
  m_frameCounter = 0;
  m_currentFrame = 0;
  m_ptr_currentAnimation = nullptr;
}

void AnimationPlayer::play(const Animation& animation) {
  resetCounters();
  m_ptr_currentAnimation = &animation;
  setAnimationFrame(0);
};

void AnimationPlayer::stop(void) {

};
