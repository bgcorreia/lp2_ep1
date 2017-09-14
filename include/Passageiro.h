/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_



class Carro;
class Parque;

class Passageiro {
public:
	int vez;

	Passageiro(int id, Carro *c, Parque *p);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();

	//int getFicha();	

	void run();
private:
	
	Carro *carro;
	Parque *parque;

	int id;
};

#endif /* PASSAGEIRO_H_ */
