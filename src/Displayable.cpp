#include "Displayable.hpp"

Displayable::Displayable(const std::shared_ptr<sf::RenderWindow> &ptr_window,
                         const std::string &textureFilepath)
    : ptr_window(ptr_window) {
  ptr_texture = std::make_unique<sf::Texture>();
  if (!ptr_texture->loadFromFile(textureFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file " +
                                textureFilepath);
  }
  sprite.setTexture(*ptr_texture);
}

void Displayable::display(void) { ptr_window->draw(sprite); }
