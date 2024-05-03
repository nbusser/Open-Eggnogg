#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

class DisplayBehavior : public sf::Drawable {
private:
  sf::Sprite sprite;
  std::unique_ptr<sf::Texture> ptr_texture;

public:
  DisplayBehavior(const std::string &textureFilepath);

  ~DisplayBehavior(void) = default;

  void updateSpritePosition(const sf::Vector2f &position);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
