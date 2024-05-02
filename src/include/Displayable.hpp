#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

class Displayable {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

protected:
  void updateSpritePosition(const sf::Vector2f &position);

public:
  Displayable(const std::string &textureFilepath);

  ~Displayable(void) = default;

  virtual void display(sf::RenderWindow &window);
};
