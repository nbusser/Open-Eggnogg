#pragma once

#include "Aninmation.hpp"
#include "SFML/System/Vector2.hpp"

namespace Animations {

const auto playerIdleAnimation = Animation{
    {sf::Vector2i(0, 0), sf::Vector2i(1, 0)}, sf::Vector2i(16, 16), 0.5f, true};
const auto playerEndureMarsupialJump =
    Animation{{sf::Vector2i(3, 4)}, sf::Vector2i(16, 16), 0.0f, false};
} // namespace Animations
