#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "Utils.hpp"
#include <memory>

class TexturedSprite : public sf::Drawable {
private:
  sf::Sprite m_sprite;
  sf::Texture m_texture;

public:
  TexturedSprite(const std::string& textureFilepath,
                 const sf::Vector2i textureUv,
                 const sf::Vector2i textureUvSize);
  TexturedSprite(const std::string& textureFilepath,
                 const sf::Vector2i textureUv);

  ~TexturedSprite(void) = default;

  virtual void update(const sf::Vector2f& position, const Direction direction,
                      const float delta);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};
