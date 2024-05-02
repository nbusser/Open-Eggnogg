#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>

enum Tile { NONE, WALL };

class Map {
public:
  size_t width;
  size_t height;
  std::vector<std::vector<Tile>> grid;

  Map();

  void loadMapFile(const std::string &mapFilePath);

  void display(sf::RenderWindow &window);

private:
  std::vector<std::vector<sf::Sprite>> spritesGrid;
  std::unique_ptr<sf::Texture> ptr_texture_tileset;

  void clearGrid();
  void buildGrid(const size_t width, const size_t height);
};
