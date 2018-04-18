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
    this->ficha=1;

    for(auto &processamento : parque->getPassageiros()){ // percorre todos os passageiros
    		// Processamento irá ser cada uma das threads
            if( processamento->ficha > max ){ //se o valor da ficha de alguma das thread for maior que max
                    max = processamento->ficha; //atribui o valor para max
            }
    }
    
    this->ficha = max + 1; // incrementa o valor máximo + 1
    
    for(auto &processamento : parque->getPassageiros()){ // percorre todos os passageiros
            if( this->id != processamento->id ){ // 
                    while(( processamento->ficha !=0 && ( this->ficha > processamento->ficha || 
                    	(this->ficha == processamento->ficha && this->id > processamento->id) )) || 
                    			(carro->Carro::numPassageiros) >= (Carro::CAPACIDADE) || (carro->voltaAcabou)){}
                    	// condições p/ não entrar no Carro
            }
    }
    
    // secao critica
    Carro::numPassageiros.fetch_add(1, memory_order_relaxed); //Incrementa o numero de passageiros no carro de forma atomica
    this->ficha=0;
	
	
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
		
		if (RANDOM){
			srand(time(NULL));

			// Dorme um tempo aleatorio
			delay( rand() % MAX_TEMPO + 1 );
		} else {

			// Dorme fixo
			delay(TEMPO_PASSEIO);
		}
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
        cout << endl << "Passageiro: " << this->id << " | Entrei no Carro" <<endl;
        Carro::lock.clear();
        
        esperaVoltaAcabar();
        
        saiDoCarro(); // protocolo de saida
        
        n++;

        while (Carro::lock.test_and_set()) {}
        if (carro->getNVoltas() != MAX_NUM_VOLTAS){
        	cout << endl << "Passageiro: " << this->id <<" | Sai do Carro - Vou passear pelo parque!"<<endl;
        } else {
        	cout << endl << "Passageiro: " << this->id <<" | Sai do Carro"<<endl;
        }

        Carro::lock.clear();

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque de forma atomica
	Parque::numPessoas.fetch_sub(1, memory_order_relaxed);

	while (Carro::lock.test_and_set()) {}
	cout << endl << "Passageiro: " << this->id << " | Terminei - Dei "<< n <<" voltas" << endl;
	Carro::lock.clear();
}

