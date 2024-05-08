#include "include/CharacterDisplayBehavior.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/AnimationPlayer.hpp"
#include "include/Aninmation.hpp"
#include "include/DisplayBehavior.hpp"
#include "include/Map.hpp"
#include "include/Utils.hpp"

CharacterDisplayBehavior::CharacterDisplayBehavior(void)
    : DisplayBehavior(Constants::characterTextureFilepath, sf::Vector2i(0, 0),
                      sf::Vector2i(16, 16)),
      Animated(AnimationPlayer(m_sprite)) {};

void CharacterDisplayBehavior::update(const sf::Vector2f& position,
                                      const Direction direction,
                                      const float delta) {
  DisplayBehavior::update(position, direction, delta);
  m_animationPlayer.update(delta);
}
