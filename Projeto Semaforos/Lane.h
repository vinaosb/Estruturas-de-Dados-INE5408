/*
 * Via.h
 *
 *  Created on: 28 de abr de 2017
 *      Author: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador
 */

#ifndef LANE_H_
#define LANE_H_

#include "Carro.h"
#include "Node.h"
#include <cstddef>
#include <stdexcept>

namespace std {
/**
 * enumerador de Pistas para facilitar interpretação das mesmas
 */
enum LANE : int {N1S, /**<Pista Norte 1 Direção Sul*/
	S1N, /**<Pista Sul 1 Direção Norte*/
	L1O, /**<Pista Leste 1 Direção Oeste*/
	O1L, /**<Pista Oeste 1 Direção Leste*/
	C1O, /**<Pista Central 1 Direção Oeste*/
	N1N, /**<Pista Norte 1 Direção Norte*/
	S1S, /**<Pista Sul 1 Direção Sul*/
	L1L, /**<Pista Leste 1 Direção Leste*/
	O1O, /**<Pista Oeste 1 Direção Oeste*/
	C1L, /**<Pista Central 1 Direção Leste*/
	N2S, /**<Pista Norte 2 Direção Sul*/
	S2N, /**<Pista Sul 2 Direção Norte*/
	N2N, /**<Pista Norte 2 Direção Norte*/
	S2S /**<Pista Sul 2 Direção Sul*/
};
/**
 * enumerador de chances para facilitar leitura de codigo
 */
enum LaneChangeChance : int {oitenta10 = 8, /**<Oitenta Porcento*/
	dez80 = 9, /**<Dez Porcento*/
	quarenta30 = 7, /**<Quarenta Porcento*/
	trinta40 = 3 /**<Trinta Porcento*/
};
/**
 * Classe Pista
 */
class Lane {
public:
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
