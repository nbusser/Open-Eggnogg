#pragma once

#include "Aninmation.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <memory>

class AnimationPlayer {
private:
  std::unique_ptr<sf::Sprite> m_ptr_sprite;
  std::uint8_t m_frameCounter;
  std::unique_ptr<Animation> m_currentAnimation;

public:
  AnimationPlayer(std::unique_ptr<sf::Sprite> &&ptr_sprite);

  ~AnimationPlayer(void) = default;

  void update(void);
};
