/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Parque.h"
#include "include/Passageiro.h"

int Parque::numPessoas = 10;

Parque::Parque() {
}

Parque::~Parque() {
}

void Parque::addPassageiro(Passageiro *p) { // Recebe endereço/ponteiro do tipo Passageiro
	passageiros.push_back(p); // Adiciona o endereço recebido no fim do vector private passageiros
}

vector<Passageiro*>& Parque::getPassageiros() {
	return passageiros;

}
