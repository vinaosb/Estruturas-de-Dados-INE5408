/*
 * Via.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#include "Lane.h"

namespace via {
Lane::Lane(){
	speed_ = -1;
	sizelimit_ = -1;
	lane_ = -1;
}
Lane::Lane(int vel, int lane, int lanesize) {
	speed_ = vel;
	sizelimit_ = lanesize;
	lane_ = lane;
}

Lane::~Lane() {
	clear();
}
void Lane::clear(){
    Node *previous = head;
    while (previous != NULL) {
        previous = previous->getNext();
        dequeue(0);
    }
    head = NULL;
    tail = NULL;
    size_ = 0;
}  // limpar
void Lane::enqueue(int time) {
    Carro* data = carGenerate(time);
	if (empty()) {
        head = new Node(data, NULL);
        tail = head;
    } else {
        tail->next(new Node(data, NULL));
        tail = tail->getNext();
    }
	current += data->Size();
	data->timeEntry(time);
    size_++;
}
void Lane::enqueue(Carro *data, int time){
	data.timeEntry(time);
    if (empty()) {
        head = new Node(data, NULL);
        tail = head;
    } else if (current + data.Size() <= sizelimit_) {
        tail->setNext(new Node(data, NULL));
        tail = tail->getNext();
    } else {
        throw(std::out_of_range("A pista esta cheia."));
    }
	current += data.Size();
    size_++;
}
Carro* Lane::dequeue(int time){
    Carro* back;
	if (empty()) {
        throw(std::out_of_range("A fila está vazia."));
    }
	if ((head->data().timeEntry()+(sizelimit_/speed_)) > time) {
		Node *n = head;
		back = n->data();
		head = head->next();
		delete n;
		size_--;
		current -= back->Size();
	}
    return back;
}
Carro* Lane::front() const {
    if (empty()) {
        throw(std::out_of_range("A fila está vazia."));
    }
    return head->data();
}
Carro* Lane::back() const {
    if (empty()) {
        throw(std::out_of_range("A fila está vazia."));
    }
    return tail->data();
}
bool Lane::empty() const {
	return !size_;
}
std::size_t Lane::size() const {
	return size_;
}
Carro* Lane::carGenerate(int time) {
	return new Carro(1,1,time);
}


class Lane::
} /* namespace via */
