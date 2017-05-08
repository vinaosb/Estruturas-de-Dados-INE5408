/*
 * Node.h
 *
 *  Created on: 29 de abr de 2017
 *      Author: Vinícius Schwinden Berkenbrock e Thiago Martendal Salvador
 */

#ifndef NODE_H_
#define NODE_H_

#include "Carro.h"

namespace std {

/**
 * Classe nodo utilizada em Pista
 */
class Node {
public:
	/**
	 * Contrutor do Nodo da pista que armazena o carro
	 * @param data recebe o carro ja alocado
	 */
	explicit Node(Carro* data);
	/**
	 * Contrutor do Nodo da pista que armazena o carro
	 * @param data recebe o carro a set alocado
	 * @param next recebe o nodo seguinte ja alocado
	 */
	Node(Carro* data, Node* next);
	virtual ~Node();
	/**
	 * Retorna o carro alocado
	 * @return Retorna o carro
	 */
	Carro* getData();
	/**
	 * Retorna o proximo nodo
	 * @return Retorna o proximo nodo
	 */
	Node* getNext();
	/**
	 * Seta o proximo nodo
	 * @param next nodo a ser apontado como proximo nodo
	 */
	void setNext(Node* next);

private:
	Carro* data_ { NULL };
	Node* next_ { NULL };
};

} /* namespace via */

#endif /* NODE_H_ */
