/*
 * Via.h
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#ifndef LANE_H_
#define LANE_H_

#include "Carro.h"
#include "Node.h"
#include <stdexcept>

namespace std {
enum LANE : int {N1S,S1N,L1O,O1L,C1O,N1N,S1S,L1L,O1O,C1L,N2S,S2N,N2N,S2S};
enum LaneChangeChance : int {oitenta10 = 8, dez80 = 9, quarenta30 = 40, trinta40 = 30};
class Lane {
public:
	Lane();
	Lane(int vel, int lane, int lanesize);
	virtual ~Lane();
	void clear();
	void enqueue(int time);
	void enqueue(Carro* data, int time);
	Carro* dequeue(int time);
	Carro* front() const;
	Carro* back() const;
	bool empty() const;
	std::size_t size() const;
	int carsEntered();
	int carsExited();
private:
	Carro* carGenerate(int time);
	LANE turnGeneration(int i);

	Node* head = NULL;  // nodo-cabeça
	Node* tail = NULL;  // nodo-fim
	std::size_t size_ { 0u };  // tamanho
	int current { 0 };  // atual
	int speed_, sizelimit_, lane_,carsentered_{0},carsexited_{0};
};

} /* namespace via */

#endif /* LANE_H_ */
