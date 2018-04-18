/*
 * Parque.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PARQUE_H_
#define PARQUE_H_

#include <vector>
#include <atomic>

class Passageiro;

using namespace std;

class Parque {
public:
	static atomic<int> numPessoas;

	Parque();
	virtual ~Parque();

	void addPassageiro(Passageiro *p);
	vector<Passageiro*>& getPassageiros();

private:
	vector<Passageiro*> passageiros;
};

#endif /* PARQUE_H_ */
