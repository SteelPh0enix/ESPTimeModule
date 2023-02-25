#pragma once
#include <Arduino.h>
#include <array>
#include <cstddef>
#include <functional>

class Scheduler {
 public:
  using Task = std::function<void(void* const)>;
  static constexpr size_t MaxTasksScheduled{5};

  size_t currentlyScheduledTasks() const { return m_currentlyScheduledTasks; }

  bool scheduleTask(Task const taskFunction, unsigned long const intervalMs, void* const argument = nullptr) {
    if (currentlyScheduledTasks() >= MaxTasksScheduled)
      return false;

    m_scheduledTasks[m_currentlyScheduledTasks] = ScheduledTask{
        .taskFunction = taskFunction,
        .argument = argument,
        .intervalMs = intervalMs,
        .lastRunTimestamp = millis(),
    };
    m_currentlyScheduledTasks++;
    return true;
  }

  void execute() {
    for (size_t i = 0; i < currentlyScheduledTasks(); i++) {
      auto& task = m_scheduledTasks[i];
      if (task.taskFunction) {
        auto const currentTime = millis();
        auto const timeSinceLastRun = currentTime - task.lastRunTimestamp;
        if (timeSinceLastRun >= task.intervalMs) {
          task.taskFunction(task.argument);
          task.lastRunTimestamp = currentTime;
        }
      }
    }
  }

 private:
  struct ScheduledTask {
    Task taskFunction{};
    void* argument{};
    unsigned long intervalMs{};
    unsigned long lastRunTimestamp{};
  };

  std::array<ScheduledTask, MaxTasksScheduled> m_scheduledTasks{};
  size_t m_currentlyScheduledTasks{};
};
