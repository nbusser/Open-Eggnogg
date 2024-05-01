#pragma once

#include "PhysicsBody.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <memory>

class Displayable {
private:
  std::shared_ptr<sf::RenderWindow> ptr_window;

  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

public:
  Displayable(const std::shared_ptr<sf::RenderWindow> &ptr_window,
              const std::string &textureFilepath);

  ~Displayable(void) = default;

  virtual void display(void);
};
