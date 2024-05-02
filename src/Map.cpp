#include "include/Map.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
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

Map::Map() : grid(), spritesGrid(), tilesetTexture(sf::Texture()) {
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

  for (auto spriteRow : spritesGrid) {
    spriteRow.clear();
  }
  spritesGrid.clear();
}

void Map::loadMapFile(const std::string &mapFilePath) {
  clearGrid();

  std::ifstream mapFile(mapFilePath);

  std::string line;

  if (!std::getline(mapFile, line)) {
    THROW_MAP_READING_ERROR("Cannot read first line");
  }

  size_t width, height;
  std::istringstream iss(line);
  if (!(iss >> width >> height)) {
    THROW_MAP_READING_ERROR("Cannot read width and height");
  }

  for (size_t i = 0; i < height; ++i) {
    auto row = std::vector<Tile>();
    auto spriteRow = std::vector<sf::Sprite>();

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
      auto tile = static_cast<Tile>(charTile);
      if (tile == Tile::WALL) {
        row.push_back(tile);
        auto sprite = sf::Sprite();

        sprite.setTexture(tilesetTexture);
        sprite.setPosition(j * 32.0f, i * 32.0f);
        spriteRow.push_back(sprite);
      }
    }

    grid.push_back(row);
    spritesGrid.push_back(spriteRow);
  }
}

void Map::display(sf::RenderWindow &window) {
  for (const auto spriteRow : spritesGrid) {
    for (const auto sprite : spriteRow) {
      window.draw(sprite);
    }
  }
}
