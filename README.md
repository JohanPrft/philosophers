# Philosophers - 42 project
This project is about creating a simulation of the dining philosophers problem.
It include use of multi-threading, mutex. And require a good optimisation of the code (it's a constant race against the clock).

First project done only on linux (stricter that on MacOS) -> pass valgrind and helgrind.

Use : `make && ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> (<nb_must_eat>)`

p.s : to devs using this, sometimes valgrind trows an error about an uninitialized value, if you have any hint of how can i fix this i would like to hear from you
