#pragma once

#include "Aninmation.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>

class AnimationPlayer {
private:
  sf::Sprite *m_ptr_sprite;
  std::uint8_t m_frameCounter;
  std::uint8_t m_currentFrame;
  Animation *m_ptr_currentAnimation;

  void resetCounters(void);

public:
  AnimationPlayer(sf::Sprite &ptr_sprite);

  ~AnimationPlayer(void) = default;

  void update(void);

  void play(const Animation &animation);
  void stop(void);
};
