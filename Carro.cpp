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

#define TEMPO_DELAY 2

using namespace std;

const int Carro::CAPACIDADE = 5;
atomic<int> Carro::numPassageiros = ATOMIC_VAR_INIT(0);
bool Carro::voltaAcabou = false;

/*
 Função de delay
 Recebe o tempo em segundos
*/
void delay(int sec) {
    chrono::seconds time(sec); // Define tempo em segundos
    this_thread::sleep_for(time); // Faz o delay
}

Carro::Carro() {
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {

	cout << endl << "Pré-esperando encher..." << endl;

	while (Carro::numPassageiros < Carro::CAPACIDADE) {
		cout << endl << "Aguardando encher... " << "Passageiros: " << Carro::numPassageiros << endl;
		delay(TEMPO_DELAY); // Chama o delay
	}
}

void Carro::daUmaVolta() {
	// Dorme por um tempo fixo
	cout << endl << "Thread [" << id << "] - Dando uma volta." << " Nº Passageiros: " << Carro::numPassageiros << endl;
	delay(10);
	voltaAcabou = true;
	voltas++;
}

void Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0) { 
		cout << endl << "Esperando esvaziar..." << endl;
		cout << endl << "Thread [" << id << "] - Sai do carro." << " Nº Passageiros: " << Carro::numPassageiros << endl;
		delay(TEMPO_DELAY); 
	}
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}
