/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include <atomic>
#include <iostream>
#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"

#define TEMPO_PASSEIO 5
#define TEMPO_VOLTA 2

using namespace std;

Passageiro::Passageiro(int id, Carro *c, Parque *p) {
	this->id = id;
	this->carro = c;
	this->parque = p;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
			
	// Protocolo de entrada o Algoritmo da Padaria
        int max=0; //Valor maximo ou fim da fila
        for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
                if(tred->vez>max){ //se a vez de alguem que está esperando for maior que o maximo
                        max+=tred->vez;//o maximo passa a ser o maior mais 1
                }
        }
        this->vez=max + 1; //passa o valor maximo para ser a vez do passageiro 
        for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
                if(this->id!=tred->id){
                        while((tred->vez!=0 && ( this->vez > tred->vez || (vez == tred->vez && this->id > tred->id) ) ) || (carro->Carro::numPassageiros) >= (Carro::CAPACIDADE) || (carro->voltaAcabou)){}
                }
        }
        
        Carro::numPassageiros.fetch_add(1, memory_order_relaxed); //Incrementa o numero de passageiros no carro
        this->vez=0;
	
	
 }

void Passageiro::esperaVoltaAcabar() {
	while (!Carro::voltaAcabou) {

		// Dorme um tempo fixo
		delay(TEMPO_VOLTA);

	}
}

void Passageiro::saiDoCarro() {

	// Protocolo de saida do Algoritmo da Padaria
	Carro::numPassageiros.fetch_sub(1, memory_order_relaxed);

}

void Passageiro::passeiaPeloParque() {

	if(carro->getNVoltas() < MAX_NUM_VOLTAS){
		
		// Dorme um tempo aleatorio
		delay(TEMPO_PASSEIO);
	}
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS){
		return false;
	}

	return true;
}

void Passageiro::run() {
	int n = 0;

	while (!parqueFechado()) {

		entraNoCarro(); // protocolo de entrada

        while (Carro::lock.test_and_set()) {}
        cout << endl << "Thread: " << this->id << " | Entrei no Carro" <<endl;
        Carro::lock.clear();
        
        esperaVoltaAcabar();
        
        saiDoCarro(); // protocolo de saida
        
        n++;

        while (Carro::lock.test_and_set()) {}
        cout << endl << "Thread: " << this->id <<" | Sai do Carro"<<endl;
        Carro::lock.clear();

        while (Carro::lock.test_and_set()) {}
		cout << endl << "Thread: " << this->id << " | " << " Vou passear pelo parque!" << endl;
		Carro::lock.clear();
		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque
	Parque::numPessoas.fetch_sub(1, memory_order_relaxed);

	while (Carro::lock.test_and_set()) {}
		cout << endl << "Thread: " << this->id << " | Terminei - Dei "<< n <<" voltas" << endl;
		Carro::lock.clear();
}

