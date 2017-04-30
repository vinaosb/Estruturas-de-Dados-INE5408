/*
 * Node.h
 *
 *  Created on: 29 de abr de 2017
 *      Author: vinicius e thiago
 */

#ifndef NODE_H_
#define NODE_H_

#include "Carro.h"

namespace std {

class Node {
public:
	explicit Node(Carro* data);
	Node(Carro* data, Node* next);
	virtual ~Node();
	Carro* getData();
	Node* getNext();
	void setNext(Node* next);

private:
	Carro* data_ { NULL };
	Node* next_ { NULL };
};

} /* namespace via */

#endif /* NODE_H_ */
