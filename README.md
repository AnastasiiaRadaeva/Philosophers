# Philosophers
School Project

## Task

**You will have to write 3 different programs but they will have the same _basic rules_:**
- This project is to be coded in C, following the Norm. Any leak, crash, undefined
behavior or norm error means 0 to the project.
- A number of philosophers are sitting at a round table doing one of three things:
eating, thinking or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating
or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- As spaghetti is difficult to serve and eat with a single fork, it is assumed that a
philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving.
- Every philosopher needs to eat.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- Each program should have the same options: number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
	- number_of_philosophers: is the number of philosophers and also the number of forks
	- time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies
	- time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.
	- time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
	- number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
- Each philosopher should be given a number from 1 to ’number_of_philosophers’.
- Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
Any other philosopher with number N is seated between philosopher N - 1 and
philosopher N + 1
- Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds)
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died
- The status printed should not be scrambled or intertwined with another philosopher’s status.
- You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.
- Again, philosophers should avoid to die!

**Non common rules for philo_one:**
- One fork between each philosopher, therefore there will be a fork at the right and
at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.
- Each philosopher should be a thread

**Non common rules for philo_two:**
- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a thread.

**Non common rules for philo_three:**
- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

## Theory
- [Введение в Операционные системы (Столяров)](http://www.stolyarov.info/books/pdf/osintro.pdf) - стр. 148-182
- [Измерение временных интервалов](http://www.ccfit.nsu.ru/~kireev/lab1/lab1time.htm)
- [Потоки](https://habr.com/ru/post/326138/)


