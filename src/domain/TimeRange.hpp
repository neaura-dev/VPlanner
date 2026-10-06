#pragma once

#include <chrono>

using TimePoint = std::chrono::sys_time<std::chrono::minutes>;

class TimeRange {
public:
    TimeRange(TimePoint start, TimePoint end);

    TimePoint start() const;
    TimePoint end() const;

    std::chrono::minutes duration() const;
    
    bool contains(TimePoint point) const;
    bool overlaps(const TimeRange& other) const;

private:
    TimePoint start_;
    TimePoint end_;
};