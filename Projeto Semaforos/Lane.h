/*
 * Via.h
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#ifndef LANE_H_
#define LANE_H_

#include "Carro.h"
#include "Node.h"
#include <cstddef>
#include <stdexcept>

namespace std {
/**
 * enumerador de Pistas para facilitar interpretação
 */
enum LANE : int {N1S,S1N,L1O,O1L,C1O,N1N,S1S,L1L,O1O,C1L,N2S,S2N,N2N,S2S};
/**
 * enumerador de chances para facilitar leitura de codigo
 */
enum LaneChangeChance : int {oitenta10 = 8, dez80 = 9, quarenta30 = 40, trinta40 = 30};
/**
 * Classe Pista
 */
class Lane {
public:
	/**
	 * Construtor default de pista
	 */
	Lane();
	/**
	 * Construtor de pista
	 * @param vel define a velocidade da pista
	 * @param lane define qual o valor da pista pelo enumerador
	 * @param lanesize define o tamanho da pista
	 */
	Lane(int vel, int lane, int lanesize);
	virtual ~Lane();
	/**
	 * Funcao que limpa os carros da pista
	 */
	void clear();
	/**
	 * Funcao para criar um carro e alocar o mesmo na pista
	 * @param time parametro de tempo
	 */
	void enqueue(int time);
	/**
	 * Funcao para alocar um carro na pista e setar seu tempo de entrada
	 * @param data recebe o carro para ser alocado
	 * @param time recebe o tempo atual
	 */
	void enqueue(Carro* data, int time);
	/**
	 * Funcao para desalocar o carro caso o tempo esteja correto
	 * @param time tempo atual
	 * @return retorna um carro ou um nullptr
	 */
	Carro* dequeue(int time);
	/**
	 * retorna o carro que esta na frente dos outros
	 * @return retorna o carro na frente
	 */
	Carro* front() const;
	/**
	 * retorna o carro atras dos outros
	 * @return retorna o carro atras
	 */
	Carro* back() const;
	/**
	 * confere se a lista está vazia
	 * @return verdadeiro se tiver vazio, falso caso nao esteja
	 */
	bool empty() const;
	/**
	 * retorna o tamanho da pista
	 * @return tamanho da pista
	 */
	size_t size() const;
	/**
	 * retorna quantos carros entraram na pista
	 * @return numero de carros que entraram
	 */
	int carsEntered();
	/**
	 * retorna o numero de carros que sairam da pista
	 * @return numero de carros que sairam
	 */
	int carsExited();
private:
	Carro* carGenerate(int time);
	LANE turnGeneration(int i);

	Node* head = NULL;  // nodo-cabeça
	Node* tail = NULL;  // nodo-fim
	size_t size_ { 0u };  // tamanho
	int current { 0 };  // atual
	int speed_, sizelimit_, lane_,carsentered_{0},carsexited_{0};
};

} /* namespace via */

#endif /* LANE_H_ */
