#include "include/AnimationPlayer.hpp"
#include "SFML/Graphics/Rect.hpp"

AnimationPlayer::AnimationPlayer(sf::Sprite& ptr_sprite)
    : m_ptr_sprite(&ptr_sprite), m_secondsCounter(0), m_currentFrame(0),
      m_isFrozen(false), m_ptr_currentAnimation(nullptr) {};

bool AnimationPlayer::isAnimationLoaded(void) const {
  return m_ptr_currentAnimation != nullptr;
}

bool AnimationPlayer::isAnimationEnded(void) const {
  return isAnimationLoaded() &&
         m_currentFrame == m_ptr_currentAnimation->textureUVs.size();
}

void AnimationPlayer::setAnimationFrame(const std::uint8_t frameIndex) {
  const auto textureSize = m_ptr_currentAnimation->textureSize;

  auto uv = m_ptr_currentAnimation->textureUVs[frameIndex];
  uv.x *= textureSize.x;
  uv.y *= textureSize.y;

  const auto textureRect = sf::IntRect(uv, textureSize);
  m_ptr_sprite->setTextureRect(textureRect);
}

void AnimationPlayer::update(const float delta) {
  if (!isAnimationLoaded() || m_isFrozen) {
    return;
  }
  m_secondsCounter += delta;
  if (m_secondsCounter > m_ptr_currentAnimation->nSecondsPerAnimtion &&
      (m_ptr_currentAnimation->loop || !isAnimationEnded())) {
    m_secondsCounter = 0.0f;
    m_currentFrame =
        (++m_currentFrame) % m_ptr_currentAnimation->textureUVs.size();
    setAnimationFrame(m_currentFrame);
  }
}

void AnimationPlayer::resetCounters(void) {
  m_secondsCounter = 0;
  m_currentFrame = 0;
  m_ptr_currentAnimation = nullptr;
  m_isFrozen = false;
}

void AnimationPlayer::play(const Animation& animation) {
  resetCounters();
  m_ptr_currentAnimation = &animation;
  setAnimationFrame(0);
};

void AnimationPlayer::stop(void) { m_isFrozen = true; };
