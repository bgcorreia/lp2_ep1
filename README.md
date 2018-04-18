# Project - LP2 / EP1 - UFPB

## Description

This project implements the multithreading technique using mutual exclusion in C++.

## Compilation/Linker

To compile/linker execute `make` in the clone directory.

Example:

```bash
user@host:~/lp2_ep1$ make
[ -d OBJ ] || mkdir OBJ
g++ -c Main.cpp -std=c++11 -lpthread -o OBJ/Main.o -std=c++11 -lpthread
g++ -c Parque.cpp -o OBJ/Parque.o -std=c++11 -lpthread
g++ -c Carro.cpp -o OBJ/Carro.o -std=c++11 -lpthread
g++ -c Passageiro.cpp -o OBJ/Passageiro.o -std=c++11 -lpthread
g++ OBJ/Main.o OBJ/Parque.o OBJ/Carro.o OBJ/Passageiro.o -o AbreParque -std=c++11 -lpthread
rm -rf OBJ
user@host:~/lp2_ep1$
```

## Execution

Then, execute the generated binary:

```bash
user@host:~/lp2_ep1$ ./AbreParque
```

