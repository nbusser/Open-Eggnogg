#include "Character.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <system_error>

Character::Character(const sf::Vector2f &position) : PhysicsBody{position} {
  sf::Texture texture = sf::Texture();
  if (!texture.loadFromFile("./assets/textures/sample.jpg")) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "Cannot open file");
  }
  sprite.setTexture(texture);
};

Character::~Character() {};

void Character::physicsTick() { std::cout << "Physics tick" << std::endl; };

void Character::applyForce(const sf::Vector2f force) {};
