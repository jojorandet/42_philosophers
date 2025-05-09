#/!/bin/bash

make re
./philo 5 4 3 2 1
valgrind --leak-check=full ./philo