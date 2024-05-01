#include "Character.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <system_error>

Character::Character(const sf::Vector2f &position) : PhysicsBody{position} {
  ptr_texture = std::make_unique<sf::Texture>();
  if (!ptr_texture->loadFromFile("./assets/textures/sample.jpg")) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "Cannot open file");
  }
  sprite.setTexture(*ptr_texture);
};

Character::~Character(void) {};

void Character::physicsTick(void) { std::cout << "Physics tick" << std::endl; };

void Character::applyForce(const sf::Vector2f force) {};
