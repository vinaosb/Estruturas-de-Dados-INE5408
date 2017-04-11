//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions



namespace structures {

template<typename T>
//! pilha
class LinkedStack {
 public:
//! construtor padrão
    LinkedStack() {
        size_ = 0u;
        top_ = nullptr;
    }
    ~LinkedStack() {   // destrutor
        clear();
        size_ = 0u;
    }
    //! limpar lista
    void clear() {
        for (auto i = 0u; i < size(); i++)
            pop();
        top_ = nullptr;
        size_ = 0;
    }
    //! inserir no início
    void push(const T& data) {
        Node* temp = new Node(data, top_);
        top_ = temp;
        size_++;
    }
    //! retirar do início
    T pop() {
		if (empty()) throw (std::out_of_range("_"));
		auto temp2 = top_ -> data();
		auto temp = top_;
		top_ = top_->next();
		delete temp;
        --size_;
        return temp2;
    }
    //! acessar um elemento no topo
    T& top() const {
        if (!empty())
            return top_ -> data();
        else
            throw(std::out_of_range("_"));
    }
    //! lista vazia
    bool empty() const {
        return !size();
    }
    //! tamanho da lista
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
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
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  //  namespace structures
#endif
