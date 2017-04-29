/*
 * Node.h
 *
 *  Created on: 29 de abr de 2017
 *      Author: vinicius
 */

#ifndef NODE_H_
#define NODE_H_


namespace via {

class Node {
public:
    explicit Node(const Carro* data);
    Node(const Carro* data, Node* next);
	virtual ~Node();
	const Carro* getData() const;
	const Node* getNext() const;
	void setNext(const Node* next);

private:
   Carro* data_{NULL};
   Node* next_{NULL};
};

} /* namespace via */

#endif /* NODE_H_ */
