#include "Character.hpp"
#include "PhysicsBody.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

int main() {
  auto player1 = std::make_shared<Character>(sf::Vector2f(-15.0, 0.0));
  auto player2 = std::make_shared<Character>(sf::Vector2f(15.0, 0.0));

  std::vector<std::shared_ptr<PhysicsBody>> physicsBodies{player1, player2};

  auto window = sf::RenderWindow{{640u, 360u}, "Open Eggnogg"};
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    for (const auto &physicsBodyPtr : physicsBodies) {
      (*physicsBodyPtr).physicsTick();
    }

    window.clear();
    window.display();
  }
}
