/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include <iostream>
#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 5
#define TEMPO_PASSEIO 8
#define TEMPO_VOLTA 4

using namespace std;

Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	// Incrementa o numero de passageiros no carro (use a funcao fetch_add)
	
	bool entra[Parque::numPessoas] = {false};
	int numFicha[Parque::numPessoas] = {0}, max = 0;

	entra[id] = true;

	// Pega maior valor
	for (int i = 0 ; i < Parque::numPessoas; i++){  // VERIFICA MAIOR FICHA    
		if (numFicha[i] > max){
			max = numFicha[i];
		}
	}

	numFicha[id] = 1 + max; // PEGA FICHA
	
	entra[id] = false; 

	//cout << endl << "Pré-for Passageiros... Nº " << id << endl;
	//delay(2);

	for (int j = 0; j < Parque::numPessoas; j++){
		// Espera enquanto thread j receber os números
		//cout << endl << "Entrou no for Passageiros... Nº " << id << endl;
		//delay(2);

		while (entra[j]) { 
			//cout << endl << "Valor de J dentro do while: " << j << endl;
        	//delay(1);
        	/* While vazio */ 
        }

        //cout << endl << "Saiu do while" << endl;
        //delay(2);

		while (numFicha[j] != 0 && (numFicha[j] < numFicha[id] || numFicha[id] == numFicha[j] && j < id)){ 
			/* While vazio */
		}
		
	}

	//cout << endl << " Thread:" << id << " | "  << "/+/ [Entrada] Antes Passageiros... Nº: " << Carro::numPassageiros << endl;
	Carro::numPassageiros.fetch_add(1, memory_order_relaxed);

	while (Carro::lock.test_and_set()) {}
	cout << endl << " Thread:" << id << " | "  << "Entrei no carro... Passageiro Nº: " << Carro::numPassageiros << endl;
	Carro::lock.clear();
	
 }

void Passageiro::esperaVoltaAcabar() {
	while (!Carro::voltaAcabou) {
		while (Carro::lock.test_and_set()) {}
		cout << endl << " Thread:" << id << " | " << "Aguardando volta acabar..." << endl;
		Carro::lock.clear();

		delay(TEMPO_VOLTA); 
	}
	//cout << endl << "Volta ACABOU!" << endl;
}

void Passageiro::saiDoCarro() {
	// Protocolo de saida do Algoritmo da Padaria
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
	//num[id]--;
	//cout << endl << " Thread:" << id << " | " << "/-/ [Protocolo de Saída] Antes Passageiros... Nº: " << Carro::numPassageiros << endl;
	Carro::numPassageiros.fetch_sub(1, memory_order_relaxed);

	while (Carro::lock.test_and_set()) {}
	cout << endl << " Thread:" << id << " | "  << "Sai do carro... Restam [" << Carro::numPassageiros << "] Passageiros." << endl;
	Carro::lock.clear();
}

void Passageiro::passeiaPeloParque() {
	// Dorme um tempo aleatorio

	while (Carro::lock.test_and_set()) {}
	cout << endl << " Thread:" << id << " | " << "Passeando pelo parque!" << endl;
	Carro::lock.clear();	

	delay(TEMPO_PASSEIO);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque
}

