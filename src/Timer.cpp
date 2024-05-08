#include "include/Timer.hpp"
#include "SFML/System/Time.hpp"

Timer::Timer(void)
    : m_isRunning(false), m_timeLeft(0.0f),
      m_callback(std::function<void()>()) {};

void Timer::start(const float duration, std::function<void()> callback) {
  m_timeLeft = duration;
  m_callback = callback;
  m_isRunning = true;
}

void Timer::stop(void) { m_isRunning = false; }

bool Timer::isRunning(void) const { return m_isRunning; }

void Timer::tick(const float delta) {
  if (!m_isRunning)
    return;

  m_timeLeft -= delta;
  if (m_timeLeft < 0.0f) {
    m_isRunning = false;
    m_callback();
  }
}
