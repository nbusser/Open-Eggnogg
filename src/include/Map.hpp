#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
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
  sf::Texture tilesetTexture;

  void clearGrid();
  void buildGrid(const size_t width, const size_t height);
};
