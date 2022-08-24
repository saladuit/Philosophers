#!/bin/bash
make
echo
echo "test_1"
./philo 2 100 100 100 5
echo
echo "test_2"
./philo 5 100 100 100 5
