#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
#include <vector>

struct Animation {
  std::vector<sf::Vector2f> textureUvs;
  std::uint8_t nFramesPerAnimtion;
  bool loop;
};
