#pragma once

#include "SFML/System/Clock.hpp"
#include <functional>

class Timer {
private:
  bool m_isRunning;
  float m_timeLeft;
  std::function<void()> m_callback;

public:
  Timer(void);
  ~Timer(void) = default;

  void start(const float duration, std::function<void()> callback);
  void stop(void);
  void tick(const float delta);
  bool isRunning(void) const;
};
