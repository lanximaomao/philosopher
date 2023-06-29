# <center>Philosophers - 42 School project</center>

## Description

The Dining Philosophers Problem is a well-known synchronization problem in computer science that illustrates challenges in concurrent programming. The problem is based on the analogy of a group of philosophers who sit around a circular table with a bowl of spaghetti and a single fork between each pair of adjacent philosophers. The philosophers alternate between thinking and eating and sleeping. While they eat, they need both forks to eat. The challenge arises when multiple philosophers attempt to pick up the chopsticks simultaneously, leading to potential deadlock or starvation scenarios.

This project is all about philosophers with threads and mutexes. Specific rules are:
- [x] **Each philosopher should be one thread.**
- [x] To prevent philosophers from duplicating forks, **mutex should be used to protect each of the forks.**

This program should take the following arguments:
- [x] **number_of_philosophers:** The number of philosophers and also the number of forks.
- [x] **time_to_die (in milliseconds):** If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
- [x] **time_to_eat (in milliseconds):** The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- [x] **time_to_sleep (in milliseconds):** The time a philosopher will spend sleeping
- [ ] **number_of_times_each_philosopher_must_eat (optional argument)**: If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

<br>

## Language used
[![Language used](https://skills.thijs.gg/icons?i=c)](https://skills.thijs.gg)

<br>

## Usage
**1- To compile the programme:**

    Make

**2- Run your program with arguments:**

	./philo 1 800 200 200   (Hint: the philosopher shoud not eat and should die!)
	./philo 4 310 200 100   (Hint: a philosopher should die!)
    ./philo 4 410 200 200   (Hint:no one should die!)
	./philo 5 800 200 200 7 (Hint:no one should die and the simulation should stop after all philosophers have eaten 7 times.)
