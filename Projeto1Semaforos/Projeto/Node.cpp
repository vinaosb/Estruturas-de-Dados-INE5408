/*
 * Node.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: vinicius
 */

#include "Node.h"

namespace via {

Node::Node(const Carro* data):
				data_{data}
			{};

Node::Node(const Carro* data, Node* next):
                    data_{data},
                    next_{next}
                {};

Node::~Node() {
	// TODO Auto-generated destructor stub
}

const Carro* Node::getData() const {
	return data_;
}

const Node* Node::getNext() const {
	return next_;
}

void Node::setNext(const Node* next)
{
	next_ = next;
}

} /* namespace via */
