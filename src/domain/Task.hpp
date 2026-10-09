#pragma once

#include <string>
#include "TimeRange.hpp"

using TaskId = int;

enum class TaskPriority {
    Low,
    Medium,
    High
};

enum class TaskStatus {
    Pending,
    InProgress,
    Completed
};

class Task {
public:
    Task(
        TaskId id, 
        std::string title, 
        std::string description, 
        TaskPriority priority,
        std::chrono::minutes estimated_duration,
        std::optional<TimePoint> deadline
    );

    TaskId id() const;
    const std::string& title() const;
    const std::string& description() const;
    TaskPriority priority() const;
    TaskStatus status() const;
    std::chrono::minutes estimated_duration() const;
    const std::optional<TimePoint>& deadline() const;

    void set_title(std::string title);
    void set_description(std::string description);
    void set_priority(TaskPriority priority);
    void set_status(TaskStatus status);
    void set_estimated_duration(std::chrono::minutes estimated_duration);
    void set_deadline(std::optional<TimePoint> deadline);

    void clear_deadline();

private:
    TaskId id_;
    std::string title_;
    std::string description_;
    TaskPriority priority_;
    TaskStatus status_;
    std::chrono::minutes estimated_duration_;
    std::optional<TimePoint> deadline_;
};