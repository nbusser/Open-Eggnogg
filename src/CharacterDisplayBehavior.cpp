#include "include/CharacterDisplayBehavior.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/AnimationPlayer.hpp"
#include "include/Aninmation.hpp"
#include "include/DisplayBehavior.hpp"
#include "include/Map.hpp"
#include "include/Utils.hpp"

CharacterDisplayBehavior::CharacterDisplayBehavior(void)
    : DisplayBehavior(Constants::characterTextureFilepath,
                      sf::Vector2f(16.0f, 16.0f)),
      Animated(AnimationPlayer(m_sprite)) {};

void CharacterDisplayBehavior::update(const sf::Vector2f& position,
                                      const Direction direction,
                                      const float delta) {
  DisplayBehavior::update(position, direction, delta);
  m_animationPlayer.update(delta);
}
