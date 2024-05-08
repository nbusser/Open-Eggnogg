#include "include/DisplayBehavior.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/Character.hpp"
#include <iostream>

DisplayBehavior::DisplayBehavior(const std::string& textureFilepath,
                                 sf::Vector2i textureUv,
                                 sf::Vector2i textureUvSize)
    : m_texture(sf::Texture()) {
  if (!m_texture.loadFromFile(textureFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file " +
                                textureFilepath);
  }
  m_sprite.setTexture(m_texture);
  m_sprite.setOrigin(sf::Vector2f(textureUvSize) / 2.f);

  const auto textureRect = sf::IntRect(textureUv, textureUvSize);
  m_sprite.setTextureRect(textureRect);
}

void DisplayBehavior::update(const sf::Vector2f& position,
                             const Direction direction, const float delta) {
  const auto localePosition = position + m_sprite.getOrigin();
  m_sprite.setPosition(localePosition.x, localePosition.y);

  auto flipScale = direction == Direction::RIGHT ? 1.0f : -1.0f;
  m_sprite.setScale(flipScale, 1.0f);
}

void DisplayBehavior::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  target.draw(m_sprite);
};
