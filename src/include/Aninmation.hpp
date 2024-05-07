#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
#include <vector>

struct Animation {
  std::vector<sf::Vector2i> textureUVs;
  sf::Vector2i textureSize;
  float nSecondsPerAnimtion;
  bool loop;
};
