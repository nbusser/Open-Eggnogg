#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Map.hpp"
#include "include/PhysicsEntity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

int main() {
  auto window = sf::RenderWindow{{640u, 360u}, "Open Eggnogg"};
  window.setFramerateLimit(60);

  auto player1 = std::make_shared<Character>(sf::Vector2f(200.0, 150.0));
  auto player2 = std::make_shared<Character>(sf::Vector2f(400.0, 150.0));

  std::vector<std::shared_ptr<PhysicsEntity>> physicsEntities{player1, player2};
  std::vector<std::shared_ptr<sf::Drawable>> displayables{player1, player2};

  auto map = Map();
  map.loadMap("./assets/maps/sample.map");

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }
    }

    // Pressed inputs processing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
      player1->move(Direction::LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
      player1->move(Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
      player1->jump();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
      player2->move(Direction::LEFT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
      player2->move(Direction::RIGHT);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
      player2->jump();

    window.clear();

    for (const auto &ptr_physicsBody : physicsEntities) {
      ptr_physicsBody->physicsTick();
    }
    for (const auto &ptr_displayable : displayables) {
      window.draw(*ptr_displayable);
    }
    window.draw(map);

    window.display();
  }
}
