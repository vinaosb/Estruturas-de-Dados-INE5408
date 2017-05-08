/*
 * Node.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador
 */

#include "Node.h"

namespace std {

Node::Node(Carro* data) :
		data_ { data } {
}
;

Node::Node(Carro* data, Node* next) :
		data_ { data }, next_ { next } {
}
;

Node::~Node() {
	// TODO Auto-generated destructor stub
}

Carro* Node::getData() {
	return data_;
}

Node* Node::getNext() {
	return next_;
}

void Node::setNext(Node* next) {
	next_ = next;
}

} /* namespace via */
