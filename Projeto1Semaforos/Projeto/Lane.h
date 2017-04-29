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

namespace via {
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
private:
    Carro* carGenerate(int time);
    class Node;

    Node* head = NULL;  // nodo-cabeça
    Node* tail = NULL;  // nodo-fim
    std::size_t size_{0u};  // tamanho
	int current{0};  // atual
	int speed_,sizelimit_, lane_;
};

} /* namespace via */

#endif /* LANE_H_ */
