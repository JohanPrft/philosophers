# Philosophers - 42 project
This project is about creating a simulation of the dining philosophers problem.
It include use of multi-threading, mutex. And require a good optimisation of the code (it's a constant race against the clock).

First project done only on linux (stricter that on MacOS) -> pass valgrind and helgrind.

Use : `make && ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> (<nb_must_eat>)`
