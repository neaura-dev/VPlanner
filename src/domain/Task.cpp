#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "Task.hpp"

Task::Task(
    TaskId id, 
    std::string title, 
    std::string description, 
    TaskPriority priority,
    std::chrono::minutes estimated_duration,
    std::optional<TimePoint> deadline)
    : id_(id),
    title_(title),
    description_(description),
    priority_(priority),
    estimated_duration_(estimated_duration),
    deadline_(deadline),
    status_(TaskStatus::Pending) {
    const bool is_empty = std::all_of(
        title.begin(), 
        title.end(),
        [](unsigned char ch) { return std::isspace(ch); }
    );
    if (is_empty) {
        throw std::invalid_argument("Task: title cannot be empty");
    }
    if (estimated_duration <= std::chrono::minutes{0}) {
        throw std::invalid_argument("Task: estimated duration cannot be negative or equal zero");
    }
}

TaskId Task::id() const { return id_; }
const std::string& Task::title() const { return title_; }
const std::string& Task::description() const { return description_; }
TaskPriority Task::priority() const { return priority_; }
TaskStatus Task::status() const { return status_; }
std::chrono::minutes Task::estimated_duration() const { return estimated_duration_; }
const std::optional<TimePoint>& Task::deadline() const { return deadline_; }

bool check_space(unsigned char ch){
    return std::isspace(ch);
}

void Task::set_title(std::string title) {
    const bool is_empty = std::all_of(
        title.begin(), 
        title.end(),
        [](unsigned char ch) { return std::isspace(ch); }
    );
    if (is_empty) {
        throw std::invalid_argument("Task: title cannot be empty");
    }
    title_ = std::move(title);
}

void Task::set_description(std::string description) {
    description_ = std::move(description);
}

void Task::set_priority(TaskPriority priority) {
    priority_ = priority;
}

void Task::set_status(TaskStatus status) {
    status_ = status;
}

void Task::set_estimated_duration(std::chrono::minutes estimated_duration) {
    if (estimated_duration <= std::chrono::minutes{0}) {
        throw std::invalid_argument("Task: estimated duration cannot be negative or equal zero");
    }
    estimated_duration_ = estimated_duration;
}

void Task::set_deadline(std::optional<TimePoint> deadline) {
    deadline_ = deadline;
}

void Task::clear_deadline() {
    deadline_.reset();
}