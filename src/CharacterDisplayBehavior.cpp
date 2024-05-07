#include "include/CharacterDisplayBehavior.hpp"
#include "include/AnimationPlayer.hpp"
#include "include/Aninmation.hpp"
#include "include/DisplayBehavior.hpp"
#include "include/Map.hpp"

CharacterDisplayBehavior::CharacterDisplayBehavior(void)
    : DisplayBehavior(Constants::characterTextureFilepath),
      Animated(AnimationPlayer(m_sprite)) {}

void CharacterDisplayBehavior::update(const sf::Vector2f& position,
                                      const float delta) {
  DisplayBehavior::update(position, delta);
  m_animationPlayer.update(delta);
}
