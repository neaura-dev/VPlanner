#include <stdexcept>
#include "TimeRange.hpp"

TimeRange::TimeRange(TimePoint start, TimePoint end) : start_(start), end_(end) {
    if (start >= end) {
        throw std::invalid_argument("TimeRange: start must be earlier than end");
    }
}

TimePoint TimeRange::start() const { return start_; }
TimePoint TimeRange::end() const { return end_; }

std::chrono::minutes TimeRange::duration() const { return end_ - start_; }

bool TimeRange::contains(TimePoint point) const {
    return point >= start_ && point < end_;
}

bool TimeRange::overlaps(const TimeRange& other) const {
    return start_ < other.end() && other.start() < end_;
}