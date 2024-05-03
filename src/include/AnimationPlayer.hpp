#pragma once

#include "Aninmation.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>

class AnimationPlayer {
private:
  sf::Sprite* m_ptr_sprite;
  std::uint8_t m_frameCounter;
  std::uint8_t m_currentFrame;
  const Animation* m_ptr_currentAnimation;
  bool m_isFrozen;

  bool isAnimationLoaded(void) const;
  bool isAnimationEnded(void) const;
  void setAnimationFrame(const std::uint8_t frameIndex);
  void resetCounters(void);

public:
  AnimationPlayer(sf::Sprite& ptr_sprite);

  ~AnimationPlayer(void) = default;

  void update(void);

  void play(const Animation& animation);
  void stop(void);
};
