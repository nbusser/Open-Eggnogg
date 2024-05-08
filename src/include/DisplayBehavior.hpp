#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils.hpp"
#include <memory>

class DisplayBehavior : public sf::Drawable {
protected:
  sf::Sprite m_sprite;
  sf::Texture m_texture;

public:
  DisplayBehavior(const std::string& textureFilepath, sf::Vector2i textureUv,
                  sf::Vector2i textureUvSize);

  ~DisplayBehavior(void) = default;

  virtual void update(const sf::Vector2f& position, const Direction direction,
                      const float delta);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
