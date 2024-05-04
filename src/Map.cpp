#include "include/Map.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
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

Map::Map()
    : m_grid(std::vector<Tile>()), m_tilesetTexture(sf::Texture()),
      m_vertices(sf::VertexArray()) {
  if (!m_tilesetTexture.loadFromFile(Constants::tilesetFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file ");
  }
}

void Map::clearMap() {
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

  for (size_t row = 0; row < m_height; ++row) {
    if (!std::getline(mapFile, line)) {
      THROW_MAP_READING_ERROR("Cannot read line #" + std::to_string(row));
    }

    if (line.length() != m_width) {
      THROW_MAP_READING_ERROR("Line #" + std::to_string(row) +
                              " has a length of " +
                              std::to_string(line.length()) + " (expected " +
                              std::to_string(m_height) + ")");
    }
    for (size_t column = 0; column < m_width; ++column) {
      char charTile = line[column] - '0';
      if (!isValidTile(charTile)) {
        THROW_MAP_READING_ERROR("Unexpected tile found: " +
                                std::to_string(charTile));
      }
      m_grid.push_back(static_cast<Tile>(charTile));
    }
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

  for (size_t row = 0; row < m_height; ++row) {
    for (size_t column = 0; column < m_width; ++column) {
      const size_t tileIndex = column + row * m_width;
      const auto tileKind = m_grid[tileIndex];

      std::uint16_t textureU =
          tileKind % (m_tilesetTexture.getSize().x / Constants::mapTileSize);
      std::uint16_t textureV =
          tileKind / (m_tilesetTexture.getSize().x / Constants::mapTileSize);

      sf::Vertex* quad = &m_vertices[(tileIndex) * 4];

      quad[0].position = sf::Vector2f(column * Constants::mapTileSize,
                                      row * Constants::mapTileSize) +
                         offset;
      quad[1].position = sf::Vector2f((column + 1) * Constants::mapTileSize,
                                      row * Constants::mapTileSize) +
                         offset;
      quad[2].position = sf::Vector2f((column + 1) * Constants::mapTileSize,
                                      (row + 1) * Constants::mapTileSize) +
                         offset;
      quad[3].position = sf::Vector2f(column * Constants::mapTileSize,
                                      (row + 1) * Constants::mapTileSize) +
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
  clearMap();
  loadMapFile(mapFilePath);
  loadMapVertices();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = &m_tilesetTexture;
  target.draw(m_vertices, states);
}
