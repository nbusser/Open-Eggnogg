#include "include/DisplayBehavior.hpp"

DisplayBehavior::DisplayBehavior(const std::string &textureFilepath) {
  m_ptr_texture = std::make_unique<sf::Texture>();
  if (!m_ptr_texture->loadFromFile(textureFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file " +
                                textureFilepath);
  }
  m_sprite.setTexture(*m_ptr_texture);
}

void DisplayBehavior::updateSpritePosition(const sf::Vector2f &position) {
  m_sprite.setPosition(position.x, position.y);
}

void DisplayBehavior::draw(sf::RenderTarget &target,
                           sf::RenderStates states) const {
  target.draw(m_sprite);
};
