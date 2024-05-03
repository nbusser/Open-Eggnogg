#pragma once

#include "AnimationPlayer.hpp"
#include "DisplayBehavior.hpp"

namespace Constants {
const std::string characterTextureFilepath = "./assets/textures/sample.jpg";
} // namespace Constants

class CharacterDisplayBehavior : public DisplayBehavior {
private:
  AnimationPlayer m_animationPlayer;

public:
  CharacterDisplayBehavior(void);

  ~CharacterDisplayBehavior(void) = default;

  virtual void update(const sf::Vector2f &position) override;
};
