# Universidade Federal do Rio de Janeiro
# Programa de Engenharia de Sistemas e Computa√√o
# Author: Guilherme Iecker Ricardo

INC      = $(GUROBI_HOME)/include/
CPP      = g++
CARGS    = -m64 -g
CLIB     = -L$(GUROBI_HOME)/lib/ -lgurobi70
CPPLIB   = -L$(GUROBI_HOME)/lib/ -lgurobi_c++ -lgurobi70

all:
	$(CPP) $(CARGS) -std=c++11 mochila_frac.cpp -o mochila_frac -lm

clean:
	rm mochila_frac
	
clean-all: clean
	rm *.out
