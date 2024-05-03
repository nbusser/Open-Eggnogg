#include "include/CharacterDisplayBehavior.hpp"
#include "include/AnimationPlayer.hpp"
#include "include/Aninmation.hpp"
#include "include/DisplayBehavior.hpp"
#include "include/Map.hpp"

CharacterDisplayBehavior::CharacterDisplayBehavior(void)
    : DisplayBehavior(Constants::characterTextureFilepath),
      m_animationPlayer(AnimationPlayer(m_sprite)) {}

void CharacterDisplayBehavior::update(const sf::Vector2f& position) {
  DisplayBehavior::update(position);
  m_animationPlayer.update();
}
