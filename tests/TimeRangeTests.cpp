#include <gtest/gtest.h>
#include "../src/domain/TimeRange.hpp"

TEST(TimeRangeTests, ValidConstruction) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);

    EXPECT_EQ(range.start(), start);
    EXPECT_EQ(range.end(), end);
}

TEST(TimeRangeTests, ThrowWhenStartEqualEnd) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = start;

    EXPECT_THROW(TimeRange range(start, end), std::invalid_argument);
}

TEST(TimeRangeTests, ThrowWhenStartIsAfterEnd) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};

    EXPECT_THROW(TimeRange range(start, end), std::invalid_argument);
}

TEST(TimeRangeTests, ReturnsCorrectDuration) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11} + std::chrono::minutes{30};
    TimeRange range(start, end);
    
    EXPECT_EQ(range.duration(), std::chrono::minutes{90});
}

TEST(TimeRangeTests, ContainsStart) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);

    EXPECT_TRUE(range.contains(start));
}

TEST(TimeRangeTests, ContainsPointInsideRange) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);
    TimePoint point = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10} + std::chrono::minutes{30};

    EXPECT_TRUE(range.contains(point));
}

TEST(TimeRangeTests, ContainsEnd) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);

    EXPECT_FALSE(range.contains(end));
}

TEST(TimeRangeTests, DoesNotContainPointBeforeStart) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);
    TimePoint point = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{9};

    EXPECT_FALSE(range.contains(point));
}

TEST(TimeRangeTests, DoesNotContainPointAfterEnd) {
    TimePoint start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange range(start, end);
    TimePoint point = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{12};

    EXPECT_FALSE(range.contains(point));
}

TEST(TimeRangeTests, DetectsContainedRangeAsOverlapping) {
    TimePoint first_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint first_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint second_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10} + std::chrono::minutes{30};
    TimePoint second_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{12};
    TimeRange first_range(first_start, first_end);
    TimeRange second_range(second_start, second_end);

    EXPECT_TRUE(first_range.overlaps(second_range));
}

TEST(TimeRangeTests, DetectsIdenticalRangesAsOverlapping) {
    TimePoint first_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint first_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint second_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint second_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimeRange first_range(first_start, first_end);
    TimeRange second_range(second_start, second_end);

    EXPECT_TRUE(first_range.overlaps(second_range));
}

TEST(TimeRangeTests, DoesNotDetectAdjacentRangesAsOverlapping) {
    TimePoint first_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint first_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint second_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint second_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{12};
    TimeRange first_range(first_start, first_end);
    TimeRange second_range(second_start, second_end);

    EXPECT_FALSE(first_range.overlaps(second_range));
}

TEST(TimeRangeTests, DoesNotDetectDisjointRangesAsOverlapping) {
    TimePoint first_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{10};
    TimePoint first_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{11};
    TimePoint second_start = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{12};
    TimePoint second_end = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::hours{13};
    TimeRange first_range(first_start, first_end);
    TimeRange second_range(second_start, second_end);

    EXPECT_FALSE(first_range.overlaps(second_range));
}
