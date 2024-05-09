#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

struct Animation {
  std::vector<sf::Vector2i> textureUVs;
  float nSecondsPerAnimation;
  bool loop;
  sf::Vector2i textureSize;

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation, const bool loop,
            const sf::Vector2i textureSize)
      : textureUVs(textureUVs), nSecondsPerAnimation(nSecondsPerAnimation),
        loop(loop), textureSize(textureSize) {};
  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation, const bool loop)
      : Animation(textureUVs, nSecondsPerAnimation, loop,
                  sf::Vector2i(16, 16)) {};
  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation)
      : Animation(textureUVs, nSecondsPerAnimation, true) {};
};

struct FullBodyAnimation {
  const Animation& bodyAnimation;
  const std::optional<Animation> armAnimation;

  FullBodyAnimation(auto& bodyAnimation, auto& armAnimation)
      : bodyAnimation(bodyAnimation), armAnimation(armAnimation) {};

  FullBodyAnimation(auto& bodyAnimation)
      : bodyAnimation(bodyAnimation),
        armAnimation(std::optional<Animation>()) {};
};
