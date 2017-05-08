/*
 * Carro.h
 *
 *  Created on: 28 de abr de 2017
 *      Author: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador
 */

#ifndef CARRO_H_
#define CARRO_H_
#include <cstdlib>

namespace std {
/**
 * Classe Carro
 */
class Carro {
public:
	/**
	 * Construtor de Carro
	 * @param s1_ Seta a curva do semaforo 1
	 * @param s2_ Seta a curva do semaforo 2
	 * @param time Seta o tempo em que o carro entra na pista
	 */
	Carro(int s1_, int s2_, int time);
	/**
	 * Destrutor
	 */
	virtual ~Carro();
	/**
	 * Pega o valor da entrada do carro na pista
	 */
	int timeEntry();
	/**
	 * Seter do valor de entrada na pista
	 * @param i
	 */
	void timeEntry(int i);
	/**
	 * Retorna o valor da curva do semaforo 1
	 * @return retorna o valor para a pista que ira virar
	 */
	int Semaphore1();
	/**
	 * Seter da curva
	 * @param i valor da pista em que ira virar
	 */
	void Semaphore1(int i);
	/**
	 * Retorna o valor da curva do semaforo 2
	 * @return retorna o valor para a pista que ira virar
	 */
	int Semaphore2();
	/**
	 * Seter da curva
	 * @param i valor da pista em que ira virar
	 */
	void Semaphore2(int i);
	/**
	 * Retorna o tamanho do carro
	 * @return tamanho do carro
	 */
	int Size() {
		return size_;
	}
private:
	int size_;
	int s1, s2;
	int time_entry;
};

} /* namespace via */

#endif /* CARRO_H_ */
