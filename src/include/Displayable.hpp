#pragma once

#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

// This is basically an overload of sf::Drawable but with no "const" to the draw
// function In Character for example, I need to mutate the state of my sprite
// before drawing I am not sure yet if it is the cleanest way to do it
class Displayable {
public:
  virtual void display(sf::RenderTarget &target) = 0;
};
