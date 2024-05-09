#include "include/Sword.hpp"
#include "SFML/System/Vector2.hpp"
#include "include/TexturedSprite.hpp"

Sword::Sword(void)
    : m_position(sf::Vector2f()), m_ptr_attachedCharacter(nullptr),
      m_displayBehavior(TexturedSprite(Constants::swordTextureFilepath,
                                       Constants::swordTextureUv,
                                       Constants::swordTextureUvSize)) {};

void Sword::attachTo(std::shared_ptr<Character> ptr_character) {
  m_ptr_attachedCharacter = ptr_character;
}

void Sword::display(sf::RenderTarget& target, const float delta) {
  target.draw(m_displayBehavior);
};

void Sword::moveX(const float amount) {}
void Sword::moveY(const float amount) {}
