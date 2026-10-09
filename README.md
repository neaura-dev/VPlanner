## Domain Specifications

### TimeRange

#### Purpose

`TimeRange` is a value object representing a continuous interval between two points in time.

`TimeRange` is independent os tasks, events, schedules, and the planner itself. It is responsible only for representing and operating on time intervals.

#### Invariants

Every `TimeRange` must satisfy the following conditions:

- `start` and `end` must both be defined.
- `start` must be strictly earlier than `end`.
- Zero-length ranges (`start == end`) are not allowed.
- The duration of a range is always positive.
- A range is treated as half-open: `[start, end)`.
- A `TimeRange` is logically immutable after creation.

#### Operations

`TimeRange` must provide operations to:

- retrieve the start of the range;
- retrieve the end of the range;
- retrieve the duration;
- check whether it overlaps another `TimeRange`;
- check whether a specific point in time falls within the range.

#### Boundary Cases

| Case | Expected result |
| - | - |
| `start < end` | Valid range |
| `start == end` | Invalid range |
| `start > range` | Invalid range |
| `[10:00, 11:00)` and `[11:00, 12:00)` | Do not overlap |
| `[10:00, 11:00)` and `[10:30, 12:00)` | Overlap |
| `[10:00, 12:00)` and `[11:00, 11:30)` | Overlap |
| `[10:00, 12:00)` and `[10:00, 12:00)` | Overlap |
| `10:00` within `[10:00, 12:00)` | Contained |
| `11:59` within `[10:00, 12:00)` | Contained |
| `12:00` within `[10:00, 12:00)` | Not contained |

#### Out of Scope for v0.1

The following features are explicity out of scope for `TimeRange` in v0.1:

- time zones;
- daylight saving time transitons;
- recurring intervals;
- calendar rules;
- working days and working hours;
- breaks;
- automatic scheduling;
- integration with `Task`, `Event`, or `Scheduler`;
- serealization and file persistence.

#### Responsibility

`TimeRange` is responsible exclusively for representing and performing basic operations on a time interval.

Scheduler logic, conflict resolution, and task allocation must be handled by other VPlanner components.

### Task

#### Purpose

`Task` represents a single unit of work that a user intends to complete. It stores the task's identity, descriptive information, priority, status, estimated duration, and optional deadline.

The class is responsible for maintaining the validity of its own state. It does not manage collections of tasks, generate identifiers, schedule tasks, or perform input/output operations.

#### Data members

- `id` (`TaskId`) - unique identifier assigned externally.
- `title` (`std::string`) - short name of the task.
- `description` (`std::string`) - additional information about the task; may be empty.
- `priority` (`TaskPriority`) - task priority: `Low`, `Medium`, or `High`.
- `status` (`TaskStatus`) - current status: `Pending`, `InProgress`, or `Completed`.
- `estimated_duration` (`std::chrono::minutes`) - estimated time required to complete the task.
- `deadline` (`std::optional<TimePoint>`) - optional deadline; may be absent.

#### Invariants

A valid `Task` must satisfy the following conditions:
- The identifier is valid and cannot be changed after construction.
- The title must not be empty or contain only whitespace characters.
- The estimated duration must be greater than zero.
- The priority must be a valid `TaskPriority` value.
- The priority must be a valid `TaskStatus` value.
- The deadline may be absent.
- The description may be empty.

Task identifiers must be unique within the application, but identifier uniqueness is the responsibility of the component that manages tasks, not `Task` itself.

The initial status is `Pending`.

#### Operations

**Construction**

Creates a task using the supplied identifiers, title, description, priority, estimated duration, and optional deadline.

The status is initialized to `Pending`.

Construction must fail if the supplied data violates the class invariants.

**Accessors**

The class provides read-only access to all data members.

The identifier has no public mutator.

**Modifires**

- `set_title()` - updates the title after validating it.
- `set_description()` - updates the description.
- `set_priority()` - updates the priority after validating the value.
- `set_status()` - updates the task status after validating the value.
- `set_estimated_duration()` - updates the estimated duration after validating it.
- `set_deadline()` - assigns a deadline.
- `clear_deadline()` - removes the deadline.

A failed modification must not leave the object in an invalid state.

#### Edge Cases

- An empty or whitespace-only title must be rejected.
- A zero or negative estimated duration must be rejected.
- A task without a deadline is valid.
- An empty description is valid.
- An invalid priority or status value must be rejected.
- An identifier that violates the chosen identifier policy must be rejected.
- Updating a field with invalid data must preserve the previous valid value.

#### Out of Scope for v0.1

The `Task` class does not implement:
- Identifier generation or global uniqueness enforcement.
- Task collections or searching and filttering.
- Automatic scheduling or calendar integration.
- Recurring tasks, subtasks, tags, or task dependencies.
- Time tracking or progress estimation beyond the task status.
- Data presistence or serialization.
- User interface or input/output hadling.
- Restrictions on status transitions beyond validating the status value.

#### Design Notes

`Task` follows Rule of Zero. It does not define custom destructos, copy constructors, move constructors, or assignment operators unless future requirements justify them.

The class is independent of the user interface, persistance layer, and scheduling logic.