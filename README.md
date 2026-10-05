## Domain Specifications

### TimeRange

**Purpose**

`TimeRange` is a value object representing a continuous interval between two points in time.

`TimeRange` is independent os tasks, events, schedules, and the planner itself. It is responsible only for representing and operating on time intervals.

**Invariants**

Every `TimeRange` must satisfy the following conditions:

- `start` and `end` must both be defined.
- `start` must be strictly earlier than `end`.
- Zero-length ranges (`start == end`) are not allowed.
- The duration of a range is always positive.
- A range is treated as half-open: `[start, end)`.
- A `TimeRange` is logically immutable after creation.

**Operations**

`TimeRange` must provide operations to:

- retrieve the start of the range;
- retrieve the end of the range;
- retrieve the duration;
- check whether it overlaps another `TimeRange`;
- check whether a specific point in time falls within the range.

**Boundary Cases**

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

**Out of Scope for v0.1**

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

**Responsibility**

`TimeRange` is responsible exclusively for representing and performing basic operations on a time interval.

Scheduler logic, conflict resolution, and task allocation must be handled by other VPlanner components.