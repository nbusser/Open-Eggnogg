#include "Character.hpp"
#include "Displayable.hpp"
#include "PhysicsBody.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

int main() {
  auto window = sf::RenderWindow{{640u, 360u}, "Open Eggnogg"};
  window.setFramerateLimit(60);

  auto player1 = std::make_shared<Character>(sf::Vector2f(200.0, 150.0));
  auto player2 = std::make_shared<Character>(sf::Vector2f(400.0, 150.0));

  std::vector<std::shared_ptr<PhysicsBody>> physicsBodies{player1, player2};
  std::vector<std::shared_ptr<Displayable>> displayables{player1, player2};

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
          player1->move(Direction::LEFT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
          player1->move(Direction::RIGHT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
          player1->jump();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
          player2->move(Direction::LEFT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
          player2->move(Direction::RIGHT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
          player2->jump();
      default:
        break;
      }
    }

    window.clear();

    for (const auto &ptr_physicsBody : physicsBodies) {
      ptr_physicsBody->physicsTick();
    }
    for (const auto &ptr_displayable : displayables) {
      ptr_displayable->display(window);
    }

    window.display();
  }
}
