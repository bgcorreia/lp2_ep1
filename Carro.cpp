/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include <thread>
#include <chrono>
#include "include/Carro.h"
#include "include/Parque.h"

#define TEMPO_DELAY 5

const int Carro::CAPACIDADE = 5;
int Carro::numPassageiros = 0;
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
	while (Carro::numPassageiros < Carro::CAPACIDADE) { delay(TEMPO_DELAY); } // Chama o delay
}

void Carro::daUmaVolta() {
	// Dorme por um tempo fixo
	delay(TEMPO_DELAY);
	voltaAcabou = true;
}

void Carro::esperaEsvaziar() {
	//while (Carro::numPassageiros > 0) { delay; }
	while (Carro::numPassageiros > 0) { delay(TEMPO_DELAY); }
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
