/*
 * main.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: vinicius e thiago
 */
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "Semaforo.hpp"
#include "Lane.h"

namespace std {

void showhelpinfo(char *s);
Lane** LaneGenerator(Lane** laness_);
void parserChecker(int argc, char* argv[]);
void createCars(int time, Lane** lanes);
void semaphoreMover(int time, Lane** lanes, Semaforo* sem);
void carsRemover(int time, Lane** lanes);
void carsCounter(Lane** lanes);


int simulationTimeMiliseconds = 3600000, semaphoreTimeMiliseconds = 30000;
std::vector<int> counterCars(30,0); // 14 e 15 entrada/saida global, 0-13 entrada, 16-29 saidas

enum LaneType {
	Creater = 0, Disposer = 1
};
enum LaneFromTo {
	North = 0, South = 1, East = 2, West = 3, Central = 4
};
enum speed {
	EastS = 8, RightSide = 11, LeftSide = 17, WestS = 22
};

int main(int argc, char* argv[]) {
	Lane* laness_[14];
	parserChecker(argc, argv);
	Semaforo* sem =new Semaforo(semaphoreTimeMiliseconds);
	Lane** lanes = LaneGenerator(laness_);
	for (int clock = 0; clock < simulationTimeMiliseconds; clock++){
		createCars(clock,lanes);
		semaphoreMover(clock,lanes,sem);
		carsRemover(clock,lanes);
	}
	carsCounter(lanes);
	for(int i = 0; i < 14; i++){
		cout<<counterCars[i]<<" carros entraram na pista "<< static_cast<LANE>(i) << endl;
		cout<<counterCars[i+16]<<" carros sairam da pista "<< static_cast<LANE>(i) << endl;
	}
	cout<<counterCars[14]<<" carros entraram no sistema " << endl;
	cout<<counterCars[15]<<" carros sairam do sistema " << endl;

	return 0;
}

Lane** LaneGenerator(Lane** laness_) {
	int lanesize[160];
	int speeds[160];
	for (int from = North; from <= Central; from++)
		for (int type = Creater; type <= Disposer; type++)
			switch (from) {
			case North:
				for (auto side = 0; side <= 1; side++) {
					lanesize[type & from & side] = 500;
					if (side == 0)
						speeds[type & from & side] = RightSide;
					else
						speeds[type & from & side] = LeftSide;
				}
				break;
			case South:
				for (auto side = 0; side <= 1; side++) {
					lanesize[type & from & side] = 500;
					if (side == 0)
						speeds[type & from & side] = RightSide;
					else
						speeds[type & from & side] = LeftSide;
				}
				break;
			case East:
				lanesize[type & from & 0] = 400;
				speeds[type & from & 0] = EastS;
				break;
			case West:
				lanesize[type & from & 0] = 2000;
				speeds[type & from & 0] = WestS;
				break;
			case Central:
				lanesize[type & from & 0] = 300;
				speeds[type & from & 0] = LeftSide;
				break;
			}
	for (int from = North; from <= Central; from++)
		for (int type = Creater; type <= Disposer; type++) {
			int A = type * 100 + from * 10 + 0;
			auto temp = new Lane(speeds[A], 2 * from + type, lanesize[A]);
			laness_[2 * from + type] = temp;
		}
	for (int from = North; from <= South; from++)
		for (int type = Creater; type <= Disposer; type++) {
			int A = type * 100 + from * 10 + 1;
			auto temp = new Lane(speeds[A], 2 * from + type, lanesize[A]);
			laness_[2 * from + type + 10] = temp;
		}
	return laness_;
}

void parserChecker(int argc, char* argv[]) {
	if(argc == 1){
		 showhelpinfo(argv[0]);
		 exit(1);
	 }

	char temp;

	while((temp = getopt(argc,argv,"ht:m:s:o:d")) != -1) {
		switch (temp) {
		case 'h':
			showhelpinfo(argv[0]);
			break;
		case 't':
			simulationTimeMiliseconds = atoi(optarg)*1000*60*60;
			break;
		case 'm':
			simulationTimeMiliseconds = atoi(optarg)*1000*60;
			break;
		case 's':
			semaphoreTimeMiliseconds = atoi(optarg)*1000;
			break;
		case 'o':
			semaphoreTimeMiliseconds = atoi(optarg)*1000*60;
			break;
		case 'd':
			break;
		default:
			showhelpinfo(argv[0]);
			break;
		}
	}
}

void createCars(int time, Lane** lanes){
	if(time%(80000 + (rand()%4000)) == 1)
		lanes[O1L]->enqueue(time);
	if(time%(23000 + (rand()%14000)) == 1)
		lanes[S1N]->enqueue(time);
	if(time%(45000 + (rand()%30000)) == 1)
		lanes[S2N]->enqueue(time);
	if(time%(8000 + (rand()%4000)) == 1)
		lanes[L1O]->enqueue(time);
	if(time%(15000 + (rand()%10000)) == 1)
		lanes[N2S]->enqueue(time);
	if(time%(15000 + (rand()%10000)) == 1)
		lanes[N1S]->enqueue(time);
}

void semaphoreMover(int time, Lane** lanes, Semaforo* sem){
	sem->ChangeOpenedLane(time);
	auto temp = sem->viaAberta();
	Carro* temp2;
	Carro* temp3;
	if(temp == norte) {
		temp2 = lanes[N1S]->dequeue(time);
		temp3 = lanes[N2S]->dequeue(time);
	} else if(temp == sul) {
		temp2 = lanes[S1N]->dequeue(time);
		temp3 = lanes[S2N]->dequeue(time);
	} else if(temp == leste) {
		temp2 = lanes[L1O]->dequeue(time);
		temp3 = lanes[C1O]->dequeue(time);
	} else {
		temp2 = lanes[O1L]->dequeue(time);
		temp3 = lanes[C1L]->dequeue(time);
	}
	lanes[temp2->Semaphore1()]->enqueue(temp2,time);
	lanes[temp3->Semaphore2()]->enqueue(temp3,time);
}

void carsRemover(int time, Lane** lanes) {
	delete lanes[S1S]->dequeue(time);
	delete lanes[S2S]->dequeue(time);
	delete lanes[N1N]->dequeue(time);
	delete lanes[N2N]->dequeue(time);
	delete lanes[O1O]->dequeue(time);
	delete lanes[L1L]->dequeue(time);
}

void carsCounter(Lane** lanes){
	for(int i = N1S; i <= S2S; i=i+1){
		counterCars[i] = lanes[i]->carsEntered();
		counterCars[i+16] = lanes[i]->carsExited();
		counterCars[14] = counterCars[0]+counterCars[1]+counterCars[2]+counterCars[3]+counterCars[10]+counterCars[11];
		counterCars[15] = counterCars[21]+counterCars[22]+counterCars[23]+counterCars[24]+counterCars[28]+counterCars[29];
	}
}

void showhelpinfo(char *s)
{
  cout<<"Usage:   "<<s<<" [-option] [argument]"<<endl;
  cout<<"option:  "<<"-h	show help information"<<endl;
  cout<<"         "<<"-t	Simulation Time InHours"<<endl;
  cout<<"         "<<"-m	Simulation Time In Minutes"<<endl;
  cout<<"         "<<"-s	Semaphore Open Time In Seconds"<<endl;
  cout<<"         "<<"-o	Semaphore Open Time In Minutes"<<endl;
  cout<<"         "<<"-d	Use default Settings"<<endl;
  cout<<"example: "<<s<<" -t1 -s30"<<endl;
}
}
