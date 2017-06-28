#!/bin/sh

echo "compiling..."
make

echo "running greedy approach for fractional knapsack..."
./mochila_frac

echo "running linear programming approach for fractional knapsack..."
./mochila_lp >> lp_gurobi.log

echo "running linear programming approach for 0-1 knapsack..."
./mochila_01 >> 01_gurobi.log
