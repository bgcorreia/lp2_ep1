#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque;
	Carro carro(&parque);
	Passageiro *passageiros[10]; // Cria um array do tipo Passageiro

    for (int i = 0; i < 10; i++) { // Enquanto o i for menor que o nº de passageiros, faça
    	passageiros[i] = new Passageiro(i, &carro, &parque);
	/* 	Cria um novo objeto do tipo Passageiro e armazena o endereço no array passageiros[i]
    	então no caso irão ser criados 10 objetos ( 0 a 9 )	*/
    	parque.addPassageiro(passageiros[i]);
	/* Adiciona endereço armazenado em passageiros[i] no vector private na classe Parque */
    }

    //thread tCarro(carro); // O que faz isso?
    thread tCarro(&Carro::run,&carro); // inicia thread carro

    vector<thread> tPassageiros; // Cria um vetor do tipo thread com nome tPassageiros
    //for (auto &p : parque.getPassageiros()) tPassageiros.push_back(thread(&Passageiro::run, p)); // O que faz isso?
    for (auto &p : parque.getPassageiros()){ //for ate tamanho do vector
        tPassageiros.push_back(thread(&Passageiro::run, p)); //inicia a thread do passageiro e joga no final do vector tPassageiros
    }

    tCarro.join(); // Pausa as demais, enquanto tCarro termina

    cout << endl << "Carro parado, parque fechou! Até amanhã!" << endl;

    for (auto &th : tPassageiros){
        th.join();
    }

    for (int i = 0; i < 10; i++) {
    	delete passageiros[i];
    }

	return 0;
}
