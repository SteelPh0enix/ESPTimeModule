#pragma once
#include <Arduino.h>
#include <functional>

template <typename Task>
class DelayedTask {
 public:
  static auto platform_time_ms() { return millis(); }
  using TimeType = decltype(platform_time_ms());

  template <typename... Arguments>
  void schedule(Task task, TimeType delay, Arguments... taskArguments) {
    m_taskCallback = [task, taskArguments...]() { task(taskArguments...); };
    reschedule(delay);
  }

  bool try_running() {
    if (m_taskCallback && !has_run()) {
      auto const current_time = platform_time_ms();
      auto const scheduled_time_difference = current_time - m_taskScheduleTime;
      if (scheduled_time_difference >= m_taskDelay) {
        m_taskCallback();
        m_hasRun = true;
        return true;
      }
    }

    return false;
  }

  bool has_run() const { return m_hasRun; }

  void reschedule() {
    m_taskScheduleTime = platform_time_ms();
    m_hasRun = false;
  }

  void reschedule(TimeType delay) {
    m_taskDelay = delay;
    reschedule();
  }

  bool reschedule_if_ran() {
    if (has_run()) {
      reschedule();
      return true;
    }
    return false;
  }

  bool reschedule_if_ran(TimeType delay) {
    if (has_run()) {
      reschedule(delay);
      return true;
    }
    return false;
  }

 private:
  std::function<void()> m_taskCallback{};
  TimeType m_taskDelay{};
  TimeType m_taskScheduleTime{};
  bool m_hasRun{false};
};
