#include "include/Map.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Utf.hpp"
#include "SFML/System/Vector2.hpp"
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

#define THROW_MAP_READING_ERROR(details)                                       \
  throwMapReadingError(mapFilepath, details)

void throwMapReadingError(const std::string& mapFilepath,
                          const std::string& details) {
  throw std::system_error(std::make_error_code(std::errc::io_error),
                          "Error while reading '" + mapFilepath +
                              "': " + details);
}

const std::unordered_map<sf::Uint32, Tile> Map::ColorToTileMap = {
    {0xFFFFFFFF, Tile::NONE}, // White
    {0x000000FF, Tile::WALL}, // Back
    {0x46BBE7FF, Tile::WATER} // Blue
};

Map::Map()
    : m_grid(std::vector<Tile>()), m_tilesetTexture(sf::Texture()),
      m_vertices(sf::VertexArray()) {
  if (!m_tilesetTexture.loadFromFile(Constants::tilesetFilepath)) {
    throw std::system_error(std::make_error_code(std::errc::io_error),
                            "An error occured while opening texture file ");
  }
}

Tile Map::getTile(const size_t row, const size_t column) const {
  const size_t tileIndex = column + row * m_width;
  return m_grid[tileIndex];
}

void Map::clearMap() {
  m_grid.clear();
  m_vertices.clear();
  m_relativeHitboxes.clear();
}

void Map::loadMapFile(const std::string& mapFilepath) {
  auto image = sf::Image();

  if (!image.loadFromFile(mapFilepath)) {
    THROW_MAP_READING_ERROR("Cannot find file");
  }

  m_width = image.getSize().x;
  m_height = image.getSize().y;

  for (size_t row = 0; row < m_height; ++row) {
    for (size_t column = 0; column < m_width; ++column) {
      const auto pixelHexColor = image.getPixel(column, row).toInteger();

      const auto it = ColorToTileMap.find(pixelHexColor);

      if (it == ColorToTileMap.end()) {
        std::stringstream ss;
        ss << std::hex << pixelHexColor;
        std::string hexStr = ss.str();
        THROW_MAP_READING_ERROR(
            "Unexpected pixel color at position " + std::to_string(column) +
            "," + std::to_string(row) + " - Hex color code #" + hexStr);
      }

      m_grid.push_back(static_cast<Tile>(it->second));
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

      if (tileKind != Tile::NONE) {
        const auto tileBoxSize =
            sf::Vector2f(Constants::mapTileSize, Constants::mapTileSize);
        auto tileBox = sf::FloatRect(quad[0].position, tileBoxSize);
        m_relativeHitboxes.push_back(tileBox);
      }
    }
  }
}

void Map::loadMap(const std::string& mapFilePath) {
  clearMap();
  loadMapFile(mapFilePath);
  loadMapVertices();
  updateHitboxesPosition(sf::Vector2f(0.0f, 0.0f));
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.texture = &m_tilesetTexture;
  target.draw(m_vertices, states);
}
