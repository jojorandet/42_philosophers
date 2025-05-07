#/!/bin/bash

make re
./philo a b c
valgrind --leak-check=full ./philo