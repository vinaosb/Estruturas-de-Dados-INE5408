/*
 * Semaforo.hpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#ifndef SEMAFORO_HPP_
#define SEMAFORO_HPP_

namespace via {

enum viaAberta {norte = 0, sul = 1, leste = 2, oeste = 3};
template<typename L>
class Semaforo {
private:
	int openedTime = 30000;
	viaAberta via_;
public:
	Semaforo(){
		via_ = norte;
	}
	~Semaforo(){
	}
	void MudaViaLiberada(int time) {
		if(time % openedTime == openedTime-1)
			via_ = (via_+1)%4;
	}
	int viaAberta(){
		return via;
	}
};
}

#endif /* SEMAFORO_HPP_ */
