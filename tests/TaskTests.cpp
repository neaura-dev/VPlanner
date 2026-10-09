#include <gtest/gtest.h>
#include "../src/domain/Task.hpp"

TEST(TaskTests, CreatesTaskWithValidData) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );

    EXPECT_EQ(task.id(), 0);
    EXPECT_EQ(task.title(), "Task");
    EXPECT_EQ(task.description(), "Description");
    EXPECT_EQ(task.priority(), TaskPriority::Low);
    EXPECT_EQ(task.estimated_duration(), std::chrono::minutes{30});
    EXPECT_EQ(task.deadline(), std::nullopt);
}

TEST(TaskTests, InitializeStatusAsPending) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );

    EXPECT_EQ(task.status(), TaskStatus::Pending);
}

TEST(TaskTests, ThrowsWhenInitializedTitleIsEmpty) {
    EXPECT_THROW(
        Task task(
        0,
        "",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
        ),
        std::invalid_argument
    );
}

TEST(TaskTests, ThrowsWhenInitializedTitleContainsOnlyWhitespace) {
    EXPECT_THROW(
        Task task(
        0,
        "   ",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
        ),
        std::invalid_argument
    );
}

TEST(TaskTests, ThrowsWhenInitializedDurationIsZero) {
    EXPECT_THROW(
        Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{0},
        std::nullopt
        ),
        std::invalid_argument
    );
}

TEST(TaskTests, ThrowsWhenInitializedDurationIsNegative) {
    EXPECT_THROW(
        Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{-10},
        std::nullopt
        ),
        std::invalid_argument
    );
}

TEST(TaskTests, PreservesOldTitleWhenNewTitleIsInvalid) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    try {
        task.set_title("   ");
    }
    catch(std::invalid_argument) {}

    EXPECT_EQ(task.title(), "Task");
}

TEST(TaskTests, ChangesEstimatedDuration) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    task.set_estimated_duration(std::chrono::minutes{60});

    EXPECT_EQ(task.estimated_duration(), std::chrono::minutes{60});
}

TEST(TaskTests, ThrowsWhenDurationIsZero) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    

    EXPECT_THROW(
        task.set_estimated_duration(std::chrono::minutes{0});,
        std::invalid_argument
    );
}

TEST(TaskTests, ThrowsWhenDurationIsNegative) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    

    EXPECT_THROW(
        task.set_estimated_duration(std::chrono::minutes{-30});,
        std::invalid_argument
    );
}

TEST(TaskTests, PreservesOldDurationWhenNewDurationIsInvalid) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    try {
        task.set_estimated_duration(std::chrono::minutes{0});
    }
    catch(std::invalid_argument) {}

    EXPECT_EQ(task.estimated_duration(), std::chrono::minutes{30});
}

TEST(TaskTests, ChangesTitle) {
    Task task (
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    task.set_title("Another task");

    EXPECT_EQ(task.title(), "Another task");
}

TEST(TaskTests, ThrowsWhenTitleIsEmpty) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );

    EXPECT_THROW(task.set_title(""), std::invalid_argument);
}

TEST(TaskTests, ThrowsWhenTitleContainsOnlyWhitespace) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );

    EXPECT_THROW(task.set_title("   "), std::invalid_argument);
}

TEST(TaskTests, ChangesDescription) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    task.set_description("Another description");

    EXPECT_EQ(task.description(), "Another description");
}

TEST(TaskTests, ChangesPriority) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    task.set_priority(TaskPriority::High);

    EXPECT_EQ(task.priority(), TaskPriority::High);
}

TEST(TaskTests, ChangesStatus) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    task.set_status(TaskStatus::InProgress);

    EXPECT_EQ(task.status(), TaskStatus::InProgress);
}

TEST(TaskTests, ChangesDeadline) {
    Task task(
        0,
        "Task",
        "Description",
        TaskPriority::Low,
        std::chrono::minutes{30},
        std::nullopt
    );
    TimePoint point = std::chrono::sys_days{std::chrono::year{2026}/10/6}
        + std::chrono::minutes{30};
    task.set_deadline(point);

    EXPECT_EQ(task.deadline(), point);
}