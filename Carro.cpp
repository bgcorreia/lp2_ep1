/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"

const int Carro::CAPACIDADE = 5;
int Carro::numPassageiros = 0;

Carro::Carro() {
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	//while (Carro::numPassageiros < Carro::CAPACIDADE) { delay; }
}

void Carro::daUmaVolta() {
	// Dorme por um tempo fixo
	// voltaAcabou = true
}

void Carro::esperaEsvaziar() {
	//while (Carro::numPassageiros > 0) { delay; }
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
