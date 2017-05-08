/*
 * Semaforo.hpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#ifndef SEMAFORO_HPP_
#define SEMAFORO_HPP_

namespace std {

enum viasAberta : int {
	norte = 0, sul = 1, leste = 2, oeste = 3
};
/**
 * Classe Semaforo
 */
class Semaforo {
private:
	int openedTime;
	viasAberta via_;
public:
	/**
	 * Construtor de semaforo
	 * @param i valor que o semaforo recebe para transição de estados (tempo que fica aberto)
	 */
	Semaforo(int i = 30000) {
		via_ = norte;
		openedTime = i;
	}
	~Semaforo() {
	}
	/**
	 * Muda qual pista esta aberta caso o tempo esteja certo
	 * @param time recebe o tempo atual
	 */
	void ChangeOpenedLane(int time) {
		viasAberta arr[4] = {norte,sul,leste,oeste};
		viasAberta iterator = via_;
		if (time % openedTime == openedTime - 1)
			iterator = arr[via_+1%4];
		via_ = iterator;
	}
	/**
	 * Retorna a via aberta
	 * @return retorna a via aberta
	 */
	int viaAberta() {
		return via_;
	}
};
}

#endif /* SEMAFORO_HPP_ */
