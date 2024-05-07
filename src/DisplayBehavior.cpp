#include "include/DisplayBehavior.hpp"

DisplayBehavior::DisplayBehavior(const std::string& textureFilepath)
    : m_texture(sf::Texture()) {
  if (!m_texture.loadFromFile(textureFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file " +
                                textureFilepath);
  }
  m_sprite.setTexture(m_texture);
}

void DisplayBehavior::update(const sf::Vector2f& position, const float delta) {
  m_sprite.setPosition(position.x, position.y);
}

void DisplayBehavior::draw(sf::RenderTarget& target,
                           sf::RenderStates states) const {
  target.draw(m_sprite);
};
