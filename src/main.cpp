#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "include/Character.hpp"
#include "include/Collidable.hpp"
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

  World& world = WORLD;

  sf::View camera(sf::FloatRect(0.0f, 0.0f, 240.0f, 160.0f));
  camera.setCenter(0.0f, 0.0f);
  window.setView(camera);

  sf::Shader shader;

  // load both shaders
  if (!shader.loadFromFile("./shaders/main.vert", "./shaders/main.frag")) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "Cannot open shader");
  }
  shader.setUniform("texture", sf::Shader::CurrentTexture);

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

    window.draw(world, &shader);

    window.display();
  }
}
