#pragma once

#include "Animated.hpp"
#include "AnimationPlayer.hpp"
#include "DisplayBehavior.hpp"

namespace Constants {
const std::string characterTextureFilepath = "./assets/textures/player.png";
} // namespace Constants

class CharacterDisplayBehavior : public DisplayBehavior, public Animated {
public:
  CharacterDisplayBehavior(void);

  ~CharacterDisplayBehavior(void) = default;

  virtual void update(const sf::Vector2f& position) override;
};
