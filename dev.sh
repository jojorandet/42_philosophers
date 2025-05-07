#/!/bin/bash

make re
./philo 1 2 3 4 5
valgrind --leak-check=full ./philo