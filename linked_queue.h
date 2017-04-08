//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions


namespace structures {


template<typename T>
//! Fila
class LinkedQueue {
 public:
//! construtor padrão
    LinkedQueue() {
        size_ = 0u;
        head = nullptr;
        tail = nullptr;
    }
    ~LinkedQueue() {  // destrutor
        clear();
        delete[] head;
        delete[] tail;
    }
    //! limpar lista
    void clear() {
        for (auto i = 0u; i < size(); i++)
            dequeue();
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }
    //! enfileirar
    void enqueue(const T& data) {
        if (empty()) {
            tail = new Node(data);
            head = tail;
        } else {
            tail -> next(new Node(data));
            tail = tail->next();
        }
        size_++;
    }
    //! desenfileirar
    T dequeue() {
		if (empty()) throw (std::out_of_range("_"));
		auto temp = head -> data();
		head = head->next();
        --size_;
        return temp;
    }
    //! primeiro dado
    T& front() const {
		if (empty()) throw (std::out_of_range("_"));
		return head->data();
    }
    //! ultimo dado
    T& back() const {
		if (empty()) throw (std::out_of_range("_"));
		return tail->data();
    }
    //! fila vazia
    bool empty() const {
        return !size();
    }
    //! tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  //  namespace structures
#endif
