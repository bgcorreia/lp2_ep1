/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include <atomic>
#include "include/Parque.h"
#include "include/Passageiro.h"

atomic<int> Parque::numPessoas = ATOMIC_VAR_INIT(10);

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
