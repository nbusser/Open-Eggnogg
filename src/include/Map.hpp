#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include <_types/_uint8_t.h>
#include <vector>

namespace Constants {
constexpr uint8_t mapTileSize = 16;
const std::string tilesetFilepath = "./assets/textures/tileset.png";
} // namespace Constants

enum Tile { NONE, WALL, WATER };

class Map : public sf::Drawable {
public:
  size_t width;
  size_t height;
  std::vector<std::vector<Tile>> grid;

  Map();

  void loadMap(const std::string &mapFilePath);

private:
  sf::Texture tilesetTexture;
  sf::VertexArray vertices;

  void clearGrid();
  void buildGrid(const size_t width, const size_t height);

  void loadMapFile(const std::string &mapFilePath);
  void loadMapVertices(void);

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
