/*
 * Carro.h
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius e thiago
 */

#ifndef CARRO_H_
#define CARRO_H_
#include <cstdlib>

namespace std {

class Carro {
public:
	Carro(int s1_, int s2_, int time);
	virtual ~Carro();
	int timeEntry();
	void timeEntry(int i);
	int Semaphore1();
	void Semaphore1(int i);
	int Semaphore2();
	void Semaphore2(int i);
	int Size() {
		return size_;
	}
private:
	int size_;
	int s1, s2;
	int time_entry;
};

} /* namespace via */

#endif /* CARRO_H_ */
