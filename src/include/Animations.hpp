#pragma once

#include "Aninmation.hpp"
#include "SFML/System/Vector2.hpp"

namespace Animations {

const auto playerIdle = Animation{
    {sf::Vector2i(0, 0), sf::Vector2i(1, 0)}, sf::Vector2i(16, 16), 0.5f, true};
const auto playerEndureMarsupialJump =
    Animation{{sf::Vector2i(3, 4)}, sf::Vector2i(16, 16), 0.0f, false};
const auto playerDeath = Animation{{sf::Vector2i(4, 0), sf::Vector2i(7, 1)},
                                   sf::Vector2i(16, 16),
                                   0.2f,
                                   false};
const auto playerAttack = Animation{{sf::Vector2i(2, 0), sf::Vector2i(3, 0)},
                                    sf::Vector2i(16, 16),
                                    0.05,
                                    false};
} // namespace Animations
