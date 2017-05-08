/*
 * main.h
 *
 *  Created on: 8 de mai de 2017
 *      Author: vinicius
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "Semaforo.hpp"
#include "Lane.h"

using namespace std;

/**
 * Mostra informações de uso do programa
 * Use o argumento -h ou --help para executa-lo
 * @param s recebe o argumento do programa
 */
void showhelpinfo(char *s);
/**
 * Inicializa um array de ponteiros para as pistas
 * @param laness_ recebe o array de array para inicializa-las
 * @return retorna as pistas inicializadas
 */
Lane** LaneGenerator(Lane** laness_);
/**
 * Facilitador de parser para usar os comandos
 * @param argc Conta quantos argumentos
 * @param argv Da os argumentos
 */
void parserChecker(int argc, char* argv[]);
/**
 * Gerador de carros para as pistas fonte
 * @param time tempo atual do programa
 * @param lanes array das pistas
 */
void createCars(int time, Lane** lanes);
/**
 * Move os carros de uma pista para a outra de acordo com os semaforos
 * @param time Tempo atual do programa
 * @param lanes Array de Pistas
 * @param sem Ponteiro para o semaforo
 * @param sem2 Segundo semaforo
 */
void semaphoreMover(int time, Lane** lanes, Semaforo* sem, Semaforo* sem2);
/**
 * Removedor de carros para pistas sumidouro
 * @param time Tempo atual do programa
 * @param lanes Array de Pistas
 */
void carsRemover(int time, Lane** lanes);
/**
 * Conta quantos carros entraram e sairam de cada pista e do sistema
 * @param lanes Array de Pistas
 */
void carsCounter(Lane** lanes);

int simulationTimeMiliseconds = 3600000, /**<Tempo limite da simulação em Milisegundos */
		semaphoreTimeMiliseconds = 30000, /**<Tempo de abertura do semaforo 1 */
		semaphoreTimeMiliseconds2 = 0 /**<Tempo de abertura do semaforo 2 */
		;
vector<int> counterCars/**<Vetor para contar os carros que entraram e sairam,
28 e 29 entrada/saida global, 0-13 entrada, 14-27 saidas */
		;

enum speed {
	EastS = 8, /**<Velocidade da pista Leste*/
	RightSide = 11, /**<Velocidade das pistas do lado Direito do mapa*/
	LeftSide = 17, /**<Velocidade das pistas do lado Esquerdo do mapa*/
	WestS = 22 /**<Velocidade da pista Oeste*/
};



#endif /* MAIN_H_ */
