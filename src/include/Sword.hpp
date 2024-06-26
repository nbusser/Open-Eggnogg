#pragma once

#include "Character.hpp"
#include "PhysicsEntity.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector2.hpp"
#include "TexturedSprite.hpp"
#include <memory>

namespace Constants {
const std::string swordTextureFilepath = "./assets/textures/misc.png";
const auto swordTextureUv = sf::Vector2i(0, 0);
const auto swordTextureUvSize = sf::Vector2i(16.0f, 16.0f);
} // namespace Constants

class Sword : public PhysicsEntity, public sf::Drawable {
private:
  TexturedSprite m_displayBehavior;

  std::shared_ptr<Character> m_ptr_attachedCharacter;
  sf::Vector2f m_position;

public:
  Sword(void);
  ~Sword(void) = default;

  void attachTo(std::shared_ptr<Character> ptr_character);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  virtual void moveX(const float amount) override;
  virtual void moveY(const float amount) override;
};
