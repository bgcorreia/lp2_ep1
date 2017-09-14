/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include <atomic>

#define MAX_NUM_VOLTAS 4

using namespace std;

void delay(int);

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static atomic<int> numPassageiros;
	static std::atomic_flag lock;
	static bool voltaAcabou;

	Carro(Parque *);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

	void operator()()
	{
		run();
	}

private:
	int voltas;
	Parque *parque;

};

#endif /* CARRO_H_ */