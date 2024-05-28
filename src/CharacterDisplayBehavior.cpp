#include "include/CharacterDisplayBehavior.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/AnimationPlayer.hpp"
#include "include/Aninmation.hpp"
#include "include/Map.hpp"
#include "include/Sword.hpp"
#include "include/Utils.hpp"
#include <exception>

sf::Texture createTextureFromFile(const std::string filepath) {
  auto texture = sf::Texture();
  if (!texture.loadFromFile(filepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file " +
                                filepath);
  }
  return texture;
}

sf::Sprite createSpriteFromTexture(const sf::Texture& texture,
                                   const sf::Vector2f textureUvSize) {
  auto sprite = sf::Sprite();
  sprite.setTexture(texture);
  sprite.setOrigin(textureUvSize / 2.0f);
  return sprite;
}

sf::Sprite createSpriteFromTexture(const sf::Texture& texture) {
  return createSpriteFromTexture(texture, sf::Vector2f(16.0f, 16.0f));
}

CharacterDisplayBehavior::CharacterDisplayBehavior(void)
    : m_bodyArmTexture(
          createTextureFromFile(Constants::characterTextureFilepath)),
      m_swordTexture(createTextureFromFile(Constants::swordTextureFilepath)),
      m_bodySprite(createSpriteFromTexture(m_bodyArmTexture)),
      m_armSprite(createSpriteFromTexture(m_bodyArmTexture)),
      m_swordSprite(createSpriteFromTexture(m_swordTexture)),
      m_bodyAnimationPlayer(m_bodySprite), m_armAnimationPlayer(m_armSprite) {
  m_swordSprite.setTextureRect(
      sf::IntRect(Constants::carriedSwordUv, sf::Vector2i(16, 16)));
};

void updateSprite(sf::Sprite& sprite, const sf::Vector2f& position,
                  const Direction direction) {
  const auto localePosition = position + sprite.getOrigin();
  sprite.setPosition(localePosition.x, localePosition.y);

  auto flipScale = direction == Direction::RIGHT ? 1.0f : -1.0f;
  sprite.setScale(flipScale, 1.0f);
}

void CharacterDisplayBehavior::update(const sf::Vector2f& position,
                                      const Direction direction,
                                      const float delta) {

  m_bodyAnimationPlayer.update(delta);
  m_armAnimationPlayer.update(delta);

  const auto directionFactor = direction == Direction::LEFT ? -1.0f : 1.0f;

  const auto& bodyOffset =
      !m_bodyAnimationPlayer.getCurrentAnimation().has_value()
          ? sf::Vector2f()
          : m_bodyAnimationPlayer.getCurrentAnimation()
                    .value()
                    .spriteOffsets[m_bodyAnimationPlayer.getCurrentFrame()] *
                directionFactor;
  const auto& armOffset =
      !m_armAnimationPlayer.getCurrentAnimation().has_value()
          ? sf::Vector2f()
          : m_armAnimationPlayer.getCurrentAnimation()
                    .value()
                    .spriteOffsets[m_armAnimationPlayer.getCurrentFrame()] *
                directionFactor;

  const auto swordOffset = armOffset + Constants::swordOffset * directionFactor;

  updateSprite(m_bodySprite, position + bodyOffset, direction);
  updateSprite(m_armSprite, position + armOffset, direction);
  updateSprite(m_swordSprite, position + swordOffset, direction);
}

void CharacterDisplayBehavior::playAnimation(
    const FullBodyAnimation& fullBodyAnimation) {
  m_bodyAnimationPlayer.play(fullBodyAnimation.bodyAnimation);

  if (fullBodyAnimation.armAnimation.has_value()) {
    m_armAnimationPlayer.play(*fullBodyAnimation.armAnimation);
  } else {
    // Turns arm invisible
    m_armSprite.setTextureRect(sf::IntRect());
  }
}

void CharacterDisplayBehavior::draw(sf::RenderTarget& target,
                                    sf::RenderStates states) const {
  target.draw(m_swordSprite, states);
  target.draw(m_armSprite, states);
  target.draw(m_bodySprite, states);
}
