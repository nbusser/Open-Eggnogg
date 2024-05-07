#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
#include "include/Displayable.hpp"
#include "include/Map.hpp"
#include "include/PhysicsEntity.hpp"
#include "include/World.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

int main() {
  auto window = sf::RenderWindow{{640u, 360u}, "Open Eggnogg"};
  window.setFramerateLimit(60);

  auto world = World();

  sf::View camera(sf::FloatRect(0.0f, 0.0f, 240.0f, 160.0f));
  camera.setCenter(0.0f, 0.0f);
  window.setView(camera);

  auto m_delta = sf::Clock();
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

    window.clear();

    const auto delta = m_delta.restart().asSeconds();
    world.process(delta);

    world.display(window, delta);

    window.display();
  }
}
