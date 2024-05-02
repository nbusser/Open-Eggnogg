#include "include/Map.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <_types/_uint16_t.h>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

#define THROW_MAP_READING_ERROR(details)                                       \
  throwMapReadingError(mapFilePath, details)

void throwMapReadingError(const std::string &mapFilePath,
                          const std::string &details) {
  throw std::system_error(std::make_error_code(std::errc::io_error),
                          "Error while reading '" + mapFilePath +
                              "': " + details);
}

bool isValidTile(const char c) {
  return c == static_cast<char>(Tile::NONE) ||
         c == static_cast<char>(Tile::WALL);
}

Map::Map() : grid(), tilesetTexture(sf::Texture()) {
  if (!tilesetTexture.loadFromFile("./assets/textures/sample.jpg")) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file ");
  }
}

void Map::clearGrid() {
  for (auto row : grid) {
    row.clear();
  }
  grid.clear();

  // TODO: empty vertices
}

void Map::loadMapFile(const std::string &mapFilePath) {
  std::ifstream mapFile(mapFilePath);

  std::string line;

  if (!std::getline(mapFile, line)) {
    THROW_MAP_READING_ERROR("Cannot read first line");
  }

  std::istringstream iss(line);
  if (!(iss >> width >> height)) {
    THROW_MAP_READING_ERROR("Cannot read width and height");
  }

  for (size_t i = 0; i < height; ++i) {
    auto row = std::vector<Tile>();

    if (!std::getline(mapFile, line)) {
      THROW_MAP_READING_ERROR("Cannot read line #" + std::to_string(i));
    }

    if (line.length() != width) {
      THROW_MAP_READING_ERROR("Line #" + std::to_string(i) +
                              " has a length of " +
                              std::to_string(line.length()) + " (expected " +
                              std::to_string(height) + ")");
    }
    for (size_t j = 0; j < width; ++j) {
      char charTile = line[j] - '0';
      if (!isValidTile(charTile)) {
        THROW_MAP_READING_ERROR("Unexpected tile found: " +
                                std::to_string(charTile));
      }
      row.push_back(static_cast<Tile>(charTile));
    }

    grid.push_back(row);
  }
}

void Map::loadMapVertices(void) {
  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(width * height * 4);

  for (size_t i = 0; i < height; ++i) {
    for (size_t j = 0; j < width; ++j) {
      const auto tileKind = grid[i][j];
      uint16_t textureU =
          tileKind % (tilesetTexture.getSize().x / Constants::mapTileSize);
      uint16_t textureV =
          tileKind / (tilesetTexture.getSize().x / Constants::mapTileSize);

      sf::Vertex *quad = &vertices[(i + j * width) * 4];

      quad[0].position =
          sf::Vector2f(i * Constants::mapTileSize, j * Constants::mapTileSize);
      quad[1].position = sf::Vector2f((i + 1) * Constants::mapTileSize,
                                      j * Constants::mapTileSize);
      quad[2].position = sf::Vector2f((i + 1) * Constants::mapTileSize,
                                      (j + 1) * Constants::mapTileSize);
      quad[3].position = sf::Vector2f(i * Constants::mapTileSize,
                                      (j + 1) * Constants::mapTileSize);

      quad[0].texCoords = sf::Vector2f(textureU * Constants::mapTileSize,
                                       textureV * Constants::mapTileSize);
      quad[1].texCoords = sf::Vector2f((textureU + 1) * Constants::mapTileSize,
                                       textureV * Constants::mapTileSize);
      quad[2].texCoords = sf::Vector2f((textureU + 1) * Constants::mapTileSize,
                                       (textureV + 1) * Constants::mapTileSize);
      quad[3].texCoords = sf::Vector2f(textureU * Constants::mapTileSize,
                                       (textureV + 1) * Constants::mapTileSize);
    }
  }
}

void Map::loadMap(const std::string &mapFilePath) {
  clearGrid();
  loadMapFile(mapFilePath);
  loadMapVertices();
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.texture = &tilesetTexture;
  target.draw(vertices, states);
}
