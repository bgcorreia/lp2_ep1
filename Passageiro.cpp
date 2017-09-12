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

#define MAX_NUM_VOLTAS 50

using namespace std;

Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
}

Passageiro::~Passageiro() {
}

int Passageiro::getID() {
	return id;
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	// Incrementa o numero de passageiros no carro (use a funcao fetch_add)
	
	bool entrando[Carro::CAPACIDADE] = {false};
	int num[Carro::CAPACIDADE] = {0}, max = 0;

	entrando[id] = true;

	// Pega maior valor
	for (int i = 0 ; i < Carro::CAPACIDADE ; i++){
		if (num[i] > max){
			max = num[i];
		}
	}

	num[id] = 1 + max;
	entrando[id] = false;

	//cout << endl << "Pré-for Passageiros... Nº " << id << endl;
	//delay(2);

	for (int j = 1; j < Carro::CAPACIDADE; j++){
		// Espera enquanto thread j receber os números
		//cout << endl << "Entrou no for Passageiros... Nº " << id << endl;
		//delay(2);

		while (entrando[j]) { 
			//cout << endl << "Valor de J dentro do while: " << j << endl;
        	//delay(1);
        	/* While vazio */ 
        }

        //cout << endl << "Saiu do while" << endl;
        //delay(2);

		while (num[j] != 0 && (num[j] < num[id] || num[id] == num[j] && j < id)){ 
			/* While vazio */
		}
		
	}

	cout << endl << " Thread:" << id << " | "  << "/+/ Antes Passageiros... Nº: " << Carro::numPassageiros << endl;
	Carro::numPassageiros.fetch_add(1, memory_order_relaxed);
	cout << endl << " Thread:" << id << " | "  << "/+/ Depois Passageiros... Nº: " << Carro::numPassageiros << endl;
	
    //delay(2);

	// TESTE IMPLEMENTAÇÃO
	/*
	int escolhendo[Carro::CAPACIDADE], num[Carro::CAPACIDADE], j = 0;
	
	escolhendo[id] = true;

	cout << endl << "Pré-for Passageiros... Nº " << id << endl;
	delay(2);

	for (j = 0; j < Carro::CAPACIDADE; j++) {
        
		cout << endl << "Pró-for Passageiros... Nº " << id << endl;
		delay(2);

		cout << endl << "J: " << j << endl;
		delay(2);

    	while (escolhendo[j]) {
        	cout << endl << "Valor de J dentro do while: " << j << endl;
        	delay(2);
        }

        cout << endl << "Saiu do while" << endl;
        delay(2);
    }

    cout << endl << "Saiu do for" << endl;
    cout << endl << "num[j]: " << num[j] << " / num[id]: " << num[id] << endl; 
    delay(2);
           
    while (num[j] != 0 && (num[j] < num[id] || num[id] == num[j] && j < id)){
       	cout << endl << "Incremento Passageiros..." << endl;
       	delay(2);
       	Carro::numPassageiros.fetch_add(1, memory_order_relaxed);
    }
	*/
}

void Passageiro::esperaVoltaAcabar() {
	while (!Carro::voltaAcabou) {
		cout << endl << " Thread:" << id << " | " << "Aguardando volta acabar..." << endl;
		delay(2); 
	}
	//cout << endl << "Volta ACABOU!" << endl;
}

void Passageiro::saiDoCarro() {
	// Protocolo de saida do Algoritmo da Padaria
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
	//num[id]--;
	cout << endl << " Thread:" << id << " | " << "/-/ Antes Passageiros... Nº: " << Carro::numPassageiros << endl;
	Carro::numPassageiros.fetch_sub(1, memory_order_relaxed);
	cout << endl << " Thread:" << id << " | "  << "/-/ Depois Passageiros... Nº: " << Carro::numPassageiros << endl;
}

void Passageiro::passeiaPeloParque() {
	// Dorme um tempo aleatorio
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

