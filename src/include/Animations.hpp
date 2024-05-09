#pragma once

#include "Aninmation.hpp"
#include "SFML/System/Vector2.hpp"

namespace Animations {

namespace Body {
const auto playerIdle =
    Animation({sf::Vector2i(0, 0), sf::Vector2i(1, 0)}, 0.5f, true);
const auto playerEndureMarsupialJump =
    Animation({sf::Vector2i(3, 4)}, 0.0f, false);
const auto playerDeath =
    Animation({sf::Vector2i(4, 0), sf::Vector2i(7, 1)}, 0.2f, false);
const auto playerAttack =
    Animation({sf::Vector2i(2, 0), sf::Vector2i(3, 0)}, 0.05, false);
} // namespace Body

namespace Arm {
const auto playerIdle = Animation({sf::Vector2i(6, 0)}, 0.0f, false);
const auto playerAttack = Animation({sf::Vector2i(7, 0)}, 0.0f, false);
} // namespace Arm

namespace FullBody {
const auto playerIdle = FullBodyAnimation(Body::playerIdle, Arm::playerIdle);
const auto playerEndureMarsupialJump =
    FullBodyAnimation(Body::playerEndureMarsupialJump);
const auto playerDeath = FullBodyAnimation(Body::playerDeath);
const auto playerAttack =
    FullBodyAnimation(Body::playerAttack, Arm::playerAttack);

} // namespace FullBody
} // namespace Animations
