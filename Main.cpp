#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque;
	Carro carro;
	Passageiro *passageiros[10]; // Cria um array do tipo Passageiro

    for (int i = 0; i < 10; i++) { // Enquanto o i for menor que o nº de passageiros, faça
    	passageiros[i] = new Passageiro(i, &carro);
	/* 	Cria um novo objeto do tipo Passageiro e armazena o endereço no array passageiros[i]
    	então no caso irão ser criados 10 objetos ( 0 a 9 )	*/
    	parque.addPassageiro(passageiros[i]);
	/* Adiciona endereço armazenado em passageiros[i] no vector private na classe Parque */
    }

    thread tCarro(carro); // O que faz isso?

    vector<thread> tPassageiros; // Cria um vetor do tipo thread com nome tPassageiros
    for (auto &p : parque.getPassageiros()) tPassageiros.push_back(thread(&Passageiro::run, p)); // O que faz isso?

    tCarro.join(); // Pausa as demais, enquanto tCarro termina

    for (auto &th : tPassageiros) th.join(); // O que faz isso?

    for (int i = 0; i < 10; i++) {
    	delete passageiros[i];
    }

	return 0;
}
