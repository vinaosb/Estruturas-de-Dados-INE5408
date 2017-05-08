/*
 * main.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador
 */
#include "main.h"


int main(int argc, char* argv[]) {
	Lane* laness_[14];
	parserChecker(argc, argv);

	/** Gerador de Semaforos*/
	Semaforo* sem = new Semaforo(semaphoreTimeMiliseconds);
	Semaforo* sem2;
	if(semaphoreTimeMiliseconds2 == 0)
		sem2 = sem;
	else
		sem2 = new Semaforo(semaphoreTimeMiliseconds2);

	/** Gerador de Pistas*/
	Lane** lanes = LaneGenerator(laness_);

	/**Relogio de Simulação*/
	for (int clock = 0; clock < simulationTimeMiliseconds; clock++){
		createCars(clock,lanes);
		semaphoreMover(clock,lanes,sem,sem2);
		carsRemover(clock,lanes);
	}

	/**Contador de Carros*/
	carsCounter(lanes);

	/**Mostra saidas*/
	for(int i = 0; i < 14; i++){
		cout<<counterCars[i]<<" carros entraram na pista "<< static_cast<LANE>(i) << endl;
		cout<<counterCars[i+14]<<" carros sairam da pista "<< static_cast<LANE>(i) << endl;
	}
	cout<<counterCars[28]<<" carros entraram no sistema " << endl;
	cout<<counterCars[29]<<" carros sairam do sistema " << endl;

	return 0;
}

Lane** LaneGenerator(Lane** laness_) {
	laness_[N1S] = new Lane(LeftSide,N1S,500);
	laness_[S1N] = new Lane(LeftSide,S1S,500);
	laness_[L1O] = new Lane(EastS,L1O,400);
	laness_[O1L] = new Lane(WestS,O1L,2000);
	laness_[C1O] = new Lane(LeftSide,C1O,300);
	laness_[N1N] = new Lane(LeftSide,N1N,500);
	laness_[S1S] = new Lane(LeftSide,S1S,500);
	laness_[L1L] = new Lane(EastS,L1L,400);
	laness_[O1O] = new Lane(WestS,O1O,2000);
	laness_[C1L] = new Lane(LeftSide,C1L,300);
	laness_[N2S] = new Lane(RightSide,N2S,500);
	laness_[S2N] = new Lane(RightSide,S2N,500);
	laness_[N2N] = new Lane(RightSide,N2N,500);
	laness_[S2S] = new Lane(RightSide,S2S,500);
	return laness_;
}

void parserChecker(int argc, char* argv[]) {
	if(argc == 1){
		 showhelpinfo(argv[0]);
	 }

	char temp;

	while((temp = getopt(argc,argv,"ht:m:x:z:s:o:d")) != -1) {
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
		case 'x':
			semaphoreTimeMiliseconds2 = atoi(optarg)*1000;
			break;
		case 'z':
			semaphoreTimeMiliseconds2 = atoi(optarg)*1000*60;
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

void semaphoreMover(int time, Lane** lanes, Semaforo* sem, Semaforo* sem2){
	sem->ChangeOpenedLane(time);
	if(sem != sem2)
		sem2->ChangeOpenedLane(time);
	auto ViaAbertaSemaforo1 = sem->viaAberta();
	auto ViaAbertaSemaforo2 = sem2->viaAberta();
	Carro* CarroSemaforo1 = nullptr;
	Carro* CarroSemaforo2 = nullptr;

	if(ViaAbertaSemaforo1 == norte) {
		CarroSemaforo1 = lanes[N1S]->dequeue(time);
	} else if(ViaAbertaSemaforo1 == sul) {
		CarroSemaforo1 = lanes[S1N]->dequeue(time);
	} else if(ViaAbertaSemaforo1 == leste) {
		CarroSemaforo1 = lanes[C1O]->dequeue(time);
	} else {
		CarroSemaforo1 = lanes[O1L]->dequeue(time);
	}

	if(ViaAbertaSemaforo2 == norte) {
		CarroSemaforo2 = lanes[N2S]->dequeue(time);
	} else if(ViaAbertaSemaforo2 == sul) {
		CarroSemaforo2 = lanes[S2N]->dequeue(time);
	} else if(ViaAbertaSemaforo2 == leste) {
		CarroSemaforo2 = lanes[L1O]->dequeue(time);
	} else {
		CarroSemaforo2 = lanes[C1L]->dequeue(time);
	}

	if(CarroSemaforo1 != nullptr)
		lanes[CarroSemaforo1->Semaphore1()]->enqueue(CarroSemaforo1,time);
	if(CarroSemaforo2 != nullptr)
		lanes[CarroSemaforo2->Semaphore2()]->enqueue(CarroSemaforo2,time);
}

void carsRemover(int time, Lane** lanes) {
	auto temp1 = lanes[S1S]->dequeue(time);
	auto temp2 = lanes[S2S]->dequeue(time);
	auto temp3 = lanes[N1N]->dequeue(time);
	auto temp4 = lanes[N2N]->dequeue(time);
	auto temp5 = lanes[O1O]->dequeue(time);
	auto temp6 = lanes[L1L]->dequeue(time);
	if(temp1 != nullptr)
		delete temp1;
	if(temp2 != nullptr)
		delete temp2;
	if(temp3 != nullptr)
		delete temp3;
	if(temp4 != nullptr)
		delete temp4;
	if(temp5 != nullptr)
		delete temp5;
	if(temp6 != nullptr)
		delete temp6;
}

void carsCounter(Lane** lanes){
	for(int i = N1S; i <= S2S; i=i+1){
		counterCars.push_back(lanes[i]->carsEntered());
	}
	for(int i = N1S; i <= S2S; i=i+1){
		counterCars.push_back(lanes[i]->carsExited());
	}
	counterCars.push_back(counterCars[0]+counterCars[1]+counterCars[2]+counterCars[3]+counterCars[10]+counterCars[11]);
	counterCars.push_back(counterCars[19]+counterCars[20]+counterCars[21]+counterCars[22]+counterCars[26]+counterCars[27]);
}

void showhelpinfo(char *s)
{
  cout<<"Usage:   "<<s<<" [-option] [argument]"<<endl;
  cout<<"option:  "<<"-h	show help information"<<endl;
  cout<<"         "<<"-t	Simulation Time InHours"<<endl;
  cout<<"         "<<"-m	Simulation Time In Minutes"<<endl;
  cout<<"         "<<"-s	Semaphore Open Time In Seconds"<<endl;
  cout<<"         "<<"-o	Semaphore Open Time In Minutes"<<endl;
  cout<<"         "<<"-x	Semaphore 2 Open Time In Seconds (Optional)"<<endl;
  cout<<"         "<<"-y	Semaphore 2 Open Time In Minutes (Optional)"<<endl;
  cout<<"         "<<"-d	Use default Settings"<<endl;
  cout<<"example: "<<s<<" -t1 -s30"<<endl;
}
