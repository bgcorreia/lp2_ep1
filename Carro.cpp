/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>
#include "include/Carro.h"
#include "include/Parque.h"
#include "include/Passageiro.h"

// TODOS EM SEGUNDOS
#define TEMPO_DELAY 2
#define TEMPO_VOLTA 2
#define TEMPO_ENCHER_ESVAZIAR 3

using namespace std;

const int Carro::CAPACIDADE = 5;
atomic<int> Carro::numPassageiros = ATOMIC_VAR_INIT(0);
atomic_flag Carro::lock = ATOMIC_FLAG_INIT;

bool Carro::voltaAcabou = false;

/*
 Função de delay
 Recebe o tempo em segundos
*/
void delay(int sec) {
    chrono::seconds time(sec); // Define tempo em segundos
    this_thread::sleep_for(time); // Faz o delay
}

Carro::Carro(Parque *p) {
	this->voltas = 1;
	this->parque = p;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {

	while (Carro::numPassageiros < Carro::CAPACIDADE && this->voltas < MAX_NUM_VOLTAS) {
		delay(TEMPO_ENCHER_ESVAZIAR);
		//
	}
}

void Carro::daUmaVolta() {
	
	Carro::voltaAcabou = false;

	// Dorme por um tempo fixo
	delay(TEMPO_VOLTA);
	
	Carro::voltaAcabou = true;
	
}

void Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0) {

		// Dorme por um tempo fixo
		delay(TEMPO_ENCHER_ESVAZIAR); 
	}
}

int Carro::getNVoltas() {
	return this->voltas;
}

void Carro::run() {
	while (parque->numPessoas.load(std::memory_order_relaxed) > 0) {

		// COLOCAR O BREAK
		//if(voltas == 0) break;

		/* ENCHER CARRO - INICIO */
		
		while (Carro::lock.test_and_set()) {}
		cout<< endl << "Aguardando carro encher..." << endl;
		Carro::lock.clear();

		esperaEncher();

		while (Carro::lock.test_and_set()) {}
		cout<< endl << "Carro cheio!" << endl;
		Carro::lock.clear();

		/* ENCHER CARRO - FIM */

		//if(parque->numPessoas.load(std::memory_order_relaxed) == 0) break;
		
		/* DAR VOLTA CARRO - INICIO */

		while (Carro::lock.test_and_set()) {}
		cout << endl << "Carro | Iniciando Volta Nº: " << voltas << endl;
		Carro::lock.clear(); // SAIDA

		daUmaVolta();

		while (Carro::lock.test_and_set()) {}
		cout << endl <<"Carro | Terminei Volta Nº: " << voltas << endl;
		Carro::lock.clear();

		/* DAR VOLTA CARRO - FIM */

		/* ESPERA ESVAZIAR CARRO - INICIO */

		while (Carro::lock.test_and_set()) {}
		cout<< endl << "Esvaziando carro..." << endl;
		Carro::lock.clear();

		esperaEsvaziar();

		while (Carro::lock.test_and_set()) {}
		cout<< endl << "Carro vazio!" << endl;
		Carro::lock.clear();

		/* ESPERA ESVAZIAR CARRO - FIM */

		Carro::voltaAcabou = false;

		this->voltas++;
	}
}
