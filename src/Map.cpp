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

void throwMapReadingError(const std::string& mapFilePath,
                          const std::string& details) {
  throw std::system_error(std::make_error_code(std::errc::io_error),
                          "Error while reading '" + mapFilePath +
                              "': " + details);
}

bool isValidTile(const char c) {
  return c == static_cast<char>(Tile::NONE) ||
         c == static_cast<char>(Tile::WALL) ||
         c == static_cast<char>(Tile::WATER);
}

Map::Map() : m_grid(), m_tilesetTexture(sf::Texture()) {
  if (!m_tilesetTexture.loadFromFile(Constants::tilesetFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file ");
  }
}

void Map::clearGrid() {
  for (auto row : m_grid) {
    row.clear();
  }
  m_grid.clear();

  // TODO: empty vertices
}

void Map::loadMapFile(const std::string& mapFilePath) {
  std::ifstream mapFile(mapFilePath);

  std::string line;

  if (!std::getline(mapFile, line)) {
    THROW_MAP_READING_ERROR("Cannot read first line");
  }

  std::istringstream iss(line);
  if (!(iss >> m_width >> m_height)) {
    THROW_MAP_READING_ERROR("Cannot read width and height");
  }

  for (size_t i = 0; i < m_height; ++i) {
    auto row = std::vector<Tile>();

    if (!std::getline(mapFile, line)) {
      THROW_MAP_READING_ERROR("Cannot read line #" + std::to_string(i));
    }

    if (line.length() != m_width) {
      THROW_MAP_READING_ERROR("Line #" + std::to_string(i) +
                              " has a length of " +
                              std::to_string(line.length()) + " (expected " +
                              std::to_string(m_height) + ")");
    }
    for (size_t j = 0; j < m_width; ++j) {
      char charTile = line[j] - '0';
      if (!isValidTile(charTile)) {
        THROW_MAP_READING_ERROR("Unexpected tile found: " +
                                std::to_string(charTile));
      }
      row.push_back(static_cast<Tile>(charTile));
    }

    m_grid.push_back(row);
  }
}

void Map::loadMapVertices(void) {
  const sf::Vector2f offset(
      -static_cast<float>(static_cast<float>(m_width * Constants::mapTileSize) /
                          2.0f),
      -static_cast<float>(
          static_cast<float>(m_height * Constants::mapTileSize) / 2.0f));

  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(m_width * m_height * 4);

  for (size_t i = 0; i < m_height; ++i) {
    for (size_t j = 0; j < m_width; ++j) {
      const auto tileKind = m_grid[i][j];
      std::uint16_t textureU =
          tileKind % (m_tilesetTexture.getSize().x / Constants::mapTileSize);
      std::uint16_t textureV =
          tileKind / (m_tilesetTexture.getSize().x / Constants::mapTileSize);

      sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

      quad[0].position =
          sf::Vector2f(i * Constants::mapTileSize, j * Constants::mapTileSize) +
          offset;
      quad[1].position = sf::Vector2f((i + 1) * Constants::mapTileSize,
                                      j * Constants::mapTileSize) +
                         offset;
      quad[2].position = sf::Vector2f((i + 1) * Constants::mapTileSize,
                                      (j + 1) * Constants::mapTileSize) +
                         offset;
      quad[3].position = sf::Vector2f(i * Constants::mapTileSize,
                                      (j + 1) * Constants::mapTileSize) +
                         offset;

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

void Map::loadMap(const std::string& mapFilePath) {
  clearGrid();
  loadMapFile(mapFilePath);
  loadMapVertices();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = &m_tilesetTexture;
  target.draw(m_vertices, states);
}
