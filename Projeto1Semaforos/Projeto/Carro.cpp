/*
 * Carro.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#include "Carro.h"

namespace via {

Carro::Carro(int s1_, int s2_, int time) {
    time_entry = time;
    size_ = 3 + (rand()%5);
    s1 = s1_;
    s2 = s2_;
}

Carro::~Carro() {
	// TODO Auto-generated destructor stub
}

void Carro::timeEntry(int i) {
	time_entry = i;
}
int Carro::timeEntry() {
    return time_entry;
}
void Carro::Semaphore1(int i) {
	s1 = i;
}
int Carro::Semaphore1() {
	return s1;
}
void Carro::Semaphore2(int i) {
	s2 = i;
}
int Carro::Semaphore2() {
	return s2;
}



} /* namespace via */
