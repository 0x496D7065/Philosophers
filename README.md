*This project has been created as part of the 42 curriculum*

# Philosophers

## Description

Philosophers is a concurrency project based on Dijkstra's classic dining philosophers problem. Several philosophers sit around a round table with one fork between each pair. A philosopher must hold two forks to eat, then sleeps, then thinks. If a philosopher doesn't start eating within a given time since their last meal, they die.

The goal is to simulate this with threads and mutexes, so that no philosopher starves when it can be avoided, with no data races and no deadlocks.

## Rules

- Each philosopher is a **thread**.
- There is one **fork** between each pair of philosophers, and each fork is protected by a **mutex**.
- A philosopher alternates between eating, sleeping, and thinking.
- The simulation stops when a philosopher dies, or when every philosopher has eaten the required number of times (if specified).
- Every state change is logged with a timestamp, and log lines must never be mixed up.

## Instructions

### Requirements

- A C compiler (`cc`) and `make`
- A POSIX system with pthreads (Linux or macOS)

### Build

```bash
cd philo
make          # builds the philo executable
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # rebuilds everything
```

The project compiles with `cc -Wall -Wextra -Werror`.

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms after which a philosopher who hasn't started eating dies |
| `time_to_eat` | Time in ms it takes to eat (holding two forks) |
| `time_to_sleep` | Time in ms spent sleeping |
| `number_of_times_each_philosopher_must_eat` | *(optional)* The simulation stops once every philosopher has eaten this many times |

All values must be positive integers that fit in an `int`. Invalid input prints `error`.

### Examples

```bash
./philo 5 800 200 200       # nobody should die
./philo 5 800 200 200 7     # stops once everyone has eaten 7 times
./philo 4 310 200 100       # a philosopher should die
```

## Implementation

- **Threads.** One thread per philosopher, plus one **monitor** thread that watches the whole table.
- **Forks.** Each philosopher owns one fork mutex, and their left fork is the right fork of the previous philosopher, with the first philosopher's left fork being the last philosopher's right fork.
- **Deadlock avoidance.** Philosophers with an even id wait briefly before starting, so neighbors don't all grab their first fork at the same time.
- **Monitor.** The monitor thread repeatedly checks two things:
  - whether a philosopher has gone longer than `time_to_die` since their last meal (and isn't currently eating), in which case it logs `died` and raises a shared death flag;
  - whether every philosopher has eaten the required number of times.
- **Synchronization.** Shared data is protected by dedicated mutexes: one for the death flag, one for meal timestamps and counters, and one for printing.
- **Timing.** Time is measured in milliseconds, with a custom sleep function (`ft_usleep`) for better precision than `usleep`.

## Project structure

```
.
└── philo/
    ├── Makefile
    ├── includes/    # headers
    └── srcs/
        ├── main.c      # argument checks, initialization, thread creation
        ├── init.c      # initialization of philosophers and shared data
        ├── routine.c   # philosopher and monitor routines
        ├── action.c    # eating, sleeping and thinking
        └── helper.c    # utilities (time, parsing, output)
```

## Resources

- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`
- [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- The 42 Philosophers subject PDF
