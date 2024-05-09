#pragma once

#include "AnimationPlayer.hpp"
#include "Aninmation.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "TexturedSprite.hpp"

namespace Constants {
const std::string characterTextureFilepath = "./assets/textures/player.png";
const auto swordOffset = sf::Vector2f(13.0f, 0.0f);
const auto carriedSwordUv = sf::Vector2i(16, 0);
} // namespace Constants

class CharacterDisplayBehavior : public sf::Drawable {
private:
  sf::Texture m_bodyArmTexture;
  sf::Texture m_swordTexture;

  sf::Sprite m_bodySprite;
  sf::Sprite m_armSprite;
  sf::Sprite m_swordSprite;

  AnimationPlayer m_bodyAnimationPlayer;
  AnimationPlayer m_armAnimationPlayer;

public:
  CharacterDisplayBehavior(void);

  ~CharacterDisplayBehavior(void) = default;

  void update(const sf::Vector2f& position, const Direction direction,
              const float delta);

  void playAnimation(const FullBodyAnimation& fullBodyAnimation);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
