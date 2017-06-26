#ifndef FILE_NO_AVL_HPP
#define FILE_NO_AVL_HPP
#include "definitions.hpp"

//!  Struct do elemento nó.
/*!  Implementação do nó AVL, que será inserido
 *   na árvore de índices em arquivo.
 */
typedef struct Node {
	char command[100];
	int height, right, left, data;

	bool operator==(const Node& rhs) const {
		if (strcmp(command, rhs.command) == 0) {
			return true;
		}
		return false;
	}

	bool operator<(const Node& rhs) const {
		if (strcmp(command, rhs.command) < 0) {
			return true;
		}
		return false;
	}

	bool operator>(const Node& rhs) const {
		if (strcmp(command, rhs.command) > 0) {
			return true;
		}
		return false;
	}

} Node;

//!  Classe do elemento da estrutura de dado: Arvore AVL.
/*!  Implementação do nó AVL com especialização para
 *   operações em disco, realizada na disciplina de
 *   Estrutura de Dados - INE5408 como trabalho de implementação II do semestre.
 *   \author Vinícius Schwinden Berkenbrock e Thiago Martendal
 *   \since 26/06/2017
 *   \version 1.0
 */
class FileNoAVL {
private:
	FILE *indexDat; /*!< Ponteiro para o arquivo que possui a árvore */
	Node node; /*!< Struct Node que contém as informações do nó */
public:
//! Contrutor com argumentos.
	/*! Sempre que usado, este construtor criará um
	 *  nó AVL, que possuirá filhos nulos, e seu dado conforme
	 *  valor passado por parâmetro, além de altura 1;
	 *  \param data posição do comando ou da palavra no manpage.dat ou no inverted.dat.
	 *  \param command nome do comando ou da palavra a ser inserido/a.
	 *  \param file ponteiro para o arquivo da árvore.
	 */
	FileNoAVL(int data, char command[100], FILE* file) {
		node.height = 1;
		node.right = 0;
		node.left = 0;
		node.data = data;
		for (int j = 0; j < 100; j++) {
			node.command[j] = ' ';
		}
		strcpy(node.command, command);
		indexDat = file;
	}

//! Destrutor.
	/*! Tem a função de destruir o nó AVL e fechar o arquivo da árvore.
	 */
	~FileNoAVL() {
		fclose(indexDat);
	}

//!  Função getHeight, informa a altura do nó.
	int getHeight() {
		return node.height;
	}

//!  Função getLeft, informa o ponteiro para o filho da esquerda.
	int getLeft() {
		return node.left;
	}

//!  Função getRight, informa o ponteiro para o filho da direita.
	int getRight() {
		return node.right;
	}

//!  Função getNode, informa o nodo.
	Node& getNode() {
		return node;
	}

	//!  Função getData, informa o ponteiro para o dado do nó.
	int getData() {
		return node.data;
	}

//!  Função insert, insere um dado em uma árvore AVL.
	/*!
	 *   \param node o nó a ser inserido na árvore.
	 *   \param root ponteiro para raiz da árvore.
	 *   \return um ponteiro para o nó inserido.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int insert(Node &node, int root) {
		if (root == 0) {
			fseek(indexDat, 0, SEEK_END);
			root = ftell(indexDat);
			fwrite(&node, sizeof(Node), 1, indexDat);
			return root;
		}

		fseek(indexDat, root, SEEK_SET);
		Node nodeTmp;
		fread(&nodeTmp, sizeof(Node), 1, indexDat);

		if (node < nodeTmp) {
			nodeTmp.left = insert(node, nodeTmp.left);
		} else {
			nodeTmp.right = insert(node, nodeTmp.right);
		}
		fseek(indexDat, root, SEEK_SET);
		fwrite(&nodeTmp, sizeof(Node), 1, indexDat);

		nodeTmp.height = std::max(heightAVL(nodeTmp.left),
				heightAVL(nodeTmp.right)) + 1;

		fseek(indexDat, root, SEEK_SET);
		fwrite(&nodeTmp, sizeof(Node), 1, indexDat);

		int balance = getBalance(nodeTmp);

		Node nodeTmpRight, nodeTmpLeft;

		if (nodeTmp.left != 0) {
			fseek(indexDat, nodeTmp.left, SEEK_SET);
			fread(&nodeTmpLeft, sizeof(Node), 1, indexDat);
		}

		if (nodeTmp.right != 0) {
			fseek(indexDat, nodeTmp.right, SEEK_SET);
			fread(&nodeTmpRight, sizeof(Node), 1, indexDat);
		}

		// Caso Esquerda-Esquerda
		if (balance > 1 && node < nodeTmpLeft) {
			return rightRotation(nodeTmp, root);
		}

		// Caso Esquerda-Direita
		if (balance > 1 && node > nodeTmpLeft) {
			nodeTmp.left = leftRotation(nodeTmpLeft, nodeTmp.left);
			fseek(indexDat, root, SEEK_SET);
			fwrite(&nodeTmp, sizeof(Node), 1, indexDat);
			return rightRotation(nodeTmp, root);
		}

		// Caso Direita-Direita
		if (balance < -1 && node > nodeTmpRight) {
			return leftRotation(nodeTmp, root);
		}

		// Caso Direita-Esquerda
		if (balance < -1 && node < nodeTmpRight) {
			nodeTmp.right = rightRotation(nodeTmpRight, nodeTmp.right);
			fseek(indexDat, root, SEEK_SET);
			fwrite(&nodeTmp, sizeof(Node), 1, indexDat);
			return leftRotation(nodeTmp, root);
		}
		return root;
	}

//!  Função search, busca por um dado em uma árvore AVL.
	/*!
	 *   \param node nó a ser buscado na árvore.
	 *   \return a posição do dado no arquivo principal.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int search(Node node) {
		Node temp;
		int root;
		fseek(indexDat, 0, SEEK_SET);
		fread(&root, sizeof(int), 1, indexDat);

		fseek(indexDat, root, SEEK_SET);
		fread(&temp, sizeof(Node), 1, indexDat);

		while (root != 0 && !(node == temp)) {
			if (node < temp) {
				fseek(indexDat, temp.left, SEEK_SET);
				root = temp.left;
				fread(&temp, sizeof(Node), 1, indexDat);
			} else {
				fseek(indexDat, temp.right, SEEK_SET);
				root = temp.right;
				fread(&temp, sizeof(Node), 1, indexDat);
			}
		}

		if (root == 0) {
			return -1;
		} else {
			return temp.data;
		}
	}

//!  Função heightAVL, informa altura de um nó.
	/*!
	 *   \param node posição do nó no arquivo
	 *   \return o valo da altura do nó.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int heightAVL(int node) {
		if (node == 0) {
			return 0;
		} else {
			fseek(indexDat, node, SEEK_SET);
			Node nodeTmp;
			fread(&nodeTmp, sizeof(Node), 1, indexDat);
			return nodeTmp.height;
		}
	}
//!  Função rightRotation, realiza uma rotação simples para direita.
	/*!
	 *   \param y o nó raiz da rotação.
	 *   \param root a posição do nó no arquivo.
	 *   \return posicao do nó raiz no arquivo ao final da rotação.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int rightRotation(Node y, int root) {
		Node x;

		fseek(indexDat, y.left, SEEK_SET);
		fread(&x, sizeof(Node), 1, indexDat);

		int rootNew = y.left;
		int aux = x.right;

		x.right = root;
		fseek(indexDat, y.left, SEEK_SET);
		fwrite(&x, sizeof(Node), 1, indexDat);

		y.left = aux;
		fseek(indexDat, root, SEEK_SET);
		fwrite(&y, sizeof(Node), 1, indexDat);

		//  Atualiza altura
		y.height = std::max(heightAVL(y.left), heightAVL(y.right)) + 1;
		fseek(indexDat, root, SEEK_SET);
		fwrite(&y, sizeof(Node), 1, indexDat);

		x.height = std::max(heightAVL(x.left), heightAVL(x.right)) + 1;
		fseek(indexDat, rootNew, SEEK_SET);
		fwrite(&x, sizeof(Node), 1, indexDat);

		// Retorna nova raiz
		return rootNew;
	}

//!  Função leftRotation, realiza uma rotação simples para esquerda.
	/*!
	 *   \param x o nó raiz da rotação.
	 *   \param root a posição do nó no arquivo.
	 *   \return posicao do nó raiz no arquivo ao final da rotação.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int leftRotation(Node x, int root) {
		Node y;

		fseek(indexDat, x.right, SEEK_SET);
		fread(&y, sizeof(Node), 1, indexDat);

		int rootNew = x.right;
		int aux = y.left;

		y.left = root;
		fseek(indexDat, x.right, SEEK_SET);
		fwrite(&y, sizeof(Node), 1, indexDat);

		x.right = aux;
		fseek(indexDat, root, SEEK_SET);
		fwrite(&x, sizeof(Node), 1, indexDat);

		//  Atualiza altura
		x.height = std::max(heightAVL(x.left), heightAVL(x.right)) + 1;
		fseek(indexDat, root, SEEK_SET);
		fwrite(&x, sizeof(Node), 1, indexDat);

		y.height = std::max(heightAVL(y.left), heightAVL(y.right)) + 1;
		fseek(indexDat, rootNew, SEEK_SET);
		fwrite(&y, sizeof(Node), 1, indexDat);
		// Retorna nova raíz
		return rootNew;
	}

//!  Função getBalance, calcula a diferença das alturas dos nós filhos.
	/*!
	 *   \param nodo o nó pai.
	 *   \return um inteiro que informa a diferença das alturas dos nós filhos.
	 *   \sa FileNoAVL(int data, char command[100])
	 */
	int getBalance(Node &node) {
		return heightAVL(node.left) - heightAVL(node.right);
	}

};

#endif /* FILE_NO_AVL_HPP */
