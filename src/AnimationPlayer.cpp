#include "include/AnimationPlayer.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "include/Aninmation.hpp"
#include <optional>

AnimationPlayer::AnimationPlayer(sf::Sprite& ptr_sprite)
    : m_ptr_sprite(&ptr_sprite), m_secondsCounter(0), m_currentFrame(0),
      m_isFrozen(false), m_currentAnimation(std::nullopt) {};

bool AnimationPlayer::isAnimationLoaded(void) const {
  return m_currentAnimation.has_value();
}

bool AnimationPlayer::isAnimationEnded(void) const {
  return isAnimationLoaded() &&
         m_currentFrame == m_currentAnimation.value().textureUVs.size() - 1;
}
float nSecondsPerAnimtion;

void AnimationPlayer::setAnimationFrame(const std::uint8_t frameIndex) {
  const auto textureSize = m_currentAnimation.value().textureSize;

  auto uv = m_currentAnimation.value().textureUVs[frameIndex];
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

  if (m_secondsCounter > m_currentAnimation.value().nSecondsPerAnimation &&
      (!isAnimationEnded() || m_currentAnimation.value().loop)) {
    m_secondsCounter = 0.0f;
    m_currentFrame =
        (++m_currentFrame) % m_currentAnimation.value().textureUVs.size();
    setAnimationFrame(m_currentFrame);
  }
}

void AnimationPlayer::resetCounters(void) {
  m_secondsCounter = 0;
  m_currentFrame = 0;
  m_currentAnimation.reset();
  m_isFrozen = false;
}

void AnimationPlayer::play(const Animation& animation) {
  resetCounters();
  m_currentAnimation = std::make_optional(animation);
  setAnimationFrame(0);
};

void AnimationPlayer::stop(void) { m_isFrozen = true; };

std::uint8_t AnimationPlayer::getCurrentFrame(void) const {
  return m_currentFrame;
}

const std::optional<Animation>&
AnimationPlayer::getCurrentAnimation(void) const {
  return m_currentAnimation;
}
