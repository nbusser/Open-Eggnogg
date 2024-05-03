#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

class DisplayBehavior : public sf::Drawable {
private:
  sf::Sprite m_sprite;
  sf::Texture m_texture;

public:
  DisplayBehavior(const std::string &textureFilepath);

  ~DisplayBehavior(void) = default;

  virtual void update(const sf::Vector2f &position);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
