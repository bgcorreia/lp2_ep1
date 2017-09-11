/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 50

Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	// Incrementa o numero de passageiros no carro (use a funcao fetch_add)
}

void Passageiro::esperaVoltaAcabar() {
	// while (!voltaAcabou) { delay; }
}

void Passageiro::saiDoCarro() {
	// Protocolo de saida do Algoritmo da Padaria
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
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

