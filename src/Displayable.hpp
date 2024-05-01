#pragma once

#include "PhysicsBody.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <memory>

class Displayable {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

public:
  Displayable(const std::string &textureFilepath);

  ~Displayable(void) = default;

  virtual void display(sf::RenderWindow &window);
};
