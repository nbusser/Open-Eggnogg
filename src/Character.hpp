#include "PhysicsBody.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <system_error>

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class Character : PhysicsBody {
private:
  sf::Sprite sprite;

public:
  Character(const sf::Vector2f &position) : PhysicsBody{position} {
    sf::Texture texture = sf::Texture();
    if (!texture.loadFromFile("../assets/textures/sample.jpg")) {
      throw std::system_error(std::make_error_code(std::errc::io_error),
                              "Cannot open file");
    }
    sprite.setTexture(texture);
  };

  void physicsTick() {};

  void applyForce(const sf::Vector2f force) {};
};

#endif
