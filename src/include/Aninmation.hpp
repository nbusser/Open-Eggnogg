#pragma once

#include "SFML/System/Vector2.hpp"
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct Animation {
  std::vector<sf::Vector2i> textureUVs;
  std::vector<sf::Vector2f> spriteOffsets;
  float nSecondsPerAnimation;
  bool loop;
  sf::Vector2i textureSize;

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const std::vector<sf::Vector2f>& spriteOffsets,
            const float nSecondsPerAnimation, const bool loop,
            const sf::Vector2i textureSize)
      : textureUVs(textureUVs), spriteOffsets(spriteOffsets),
        nSecondsPerAnimation(nSecondsPerAnimation), loop(loop),
        textureSize(textureSize) {
    if (textureUVs.size() != spriteOffsets.size()) {
      throw std::invalid_argument(
          "textureUVs and spriteOffsets sizes mismatch");
      ;
    }
  };

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const std::vector<sf::Vector2f>& spriteOffsets,
            const float nSecondsPerAnimation, const bool loop)
      : Animation(textureUVs, spriteOffsets, nSecondsPerAnimation, loop,
                  sf::Vector2i(16, 16)) {};
  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const std::vector<sf::Vector2f>& spriteOffsets,
            const float nSecondsPerAnimation)
      : Animation(textureUVs, spriteOffsets, nSecondsPerAnimation, true) {};

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation, const bool loop,
            const sf::Vector2i textureSize)
      : textureUVs(textureUVs), nSecondsPerAnimation(nSecondsPerAnimation),
        loop(loop), textureSize(textureSize) {
    spriteOffsets = std::vector<sf::Vector2f>();
    for (size_t i = 0; i < textureUVs.size(); i++) {
      spriteOffsets.push_back(sf::Vector2f(0.0f, 0.0f));
    }
  }

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation, const bool loop)
      : Animation(textureUVs, nSecondsPerAnimation, loop,
                  sf::Vector2i(16, 16)) {};

  Animation(const std::vector<sf::Vector2i>& textureUVs,
            const float nSecondsPerAnimation)
      : Animation(textureUVs, nSecondsPerAnimation, true,
                  sf::Vector2i(16, 16)) {};
};

struct FullBodyAnimation {
  const Animation bodyAnimation;
  const std::optional<Animation> armAnimation;

  FullBodyAnimation(Animation bodyAnimation, Animation armAnimation)
      : bodyAnimation(bodyAnimation), armAnimation(armAnimation) {};

  FullBodyAnimation(Animation bodyAnimation)
      : bodyAnimation(bodyAnimation),
        armAnimation(std::optional<Animation>()) {};
};
