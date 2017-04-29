//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions
#include "array_list.h"

namespace structures {

template<typename T>

//! Arvore Binaria
class BinaryTree {
 public:
    //! Construtor
    BinaryTree() {
        root_ = nullptr;
        size_ = 0;
    }
    //! Destrutor
    ~BinaryTree() {
        destroy(root_);
        size_ = 0;
        root_ = nullptr;
    }

    //! Insersor
    void insert(T data) {
        inserter(data, root_);
        size_++;
    }
    //! Remoção
    void remove(T data) {
        if (contains(data)) {
            removes(data, root_);
            size_--;
        }
    }

    //! Contem
    bool contains(T data) {
        return contain_(data, root_);
    }
    //! Vazio
    bool empty() const {
        return !size();
    }

    //! Tamanho
    std::size_t size() const {
        return size_;
    }
    //! Ordenacao
    ArrayList<T> pre_order() const {
            return new ArrayList();
        }
    //! Ordenacao
    ArrayList<T> in_order() const {
            return new ArrayList();
        }
    //! Ordenacao
    ArrayList<T> post_order() const {
            return new ArrayList();
        }

 private:
    struct Node {
         public:
        explicit Node(T& data):
            data_{data}
        {}


        void data(T& data) {
            data_ = data;
        }

        bool remover(T& data) {
            if (contain(data)) {
                T* temp = &data_;
                delete temp;
                return true;
            }
            return false;
        }

        //!  Contem
        bool contain(T& data) {
            if (data_ == data) {
                return true;
            }
            return false;
        }

        //!  Acha o menor nodo
        Node* minimum() {
            if (this->left())
                return this->left()->minimum();
            return this;
        }

        //!  Ordena
        void pre_order(ArrayList<T>& v) const {
            true;
        }

        //!  Ordena
        void in_order(ArrayList<T>& v) const {
            true;
        }

        //!  Ordena
        void post_order(ArrayList<T>& v) const {
            true;
        }

        Node* left() {  // getter: próximo
            return left_;
        }
        const Node* left() const {  // getter const: próximo
            return left_;
        }
        void left(Node* node) {  // setter: próximo
            left_ = node;
        }

        Node* right() {  // getter: anterior
            return right_;
        }
        const Node* right() const {  // getter: anterior
            return right_;
        }
        void right(Node* node) {  // setter: anterior
            right_ = node;
        }
        T& data() {
            return data_;
        }

         private:
        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};
    };

    //! Contem
    bool contain_(T& data, Node* leaf) {
        if (leaf != nullptr) {
            if (leaf->contain(data)) {
                return true;
            } else if (leaf->data() < data) {
                return contain_(data, leaf->left());
            } else {
                return contain_(data, leaf->right());
            }
        }
        return false;
    }
    //! Procura Nodo
    Node* search(T& data, Node* leaf) {
        if (leaf != nullptr) {
            if (leaf->contain(data)) {
                return leaf;
            } else if (leaf->left()->contain(data)) {
                return leaf->left();
            } else if (leaf->right()->contain(data)) {
                return leaf->right();
            } else if (leaf->data() < data) {
                search(data, leaf->left());
            } else {
                search(data, leaf->right());
            }
        }
        return nullptr;
    }

    //! Insert Recursivo
    void inserter(T data, Node* leaf) {
        if (leaf == nullptr) {
            leaf = new Node(data);
        } else if (data <= leaf->data()) {
            if (leaf->left() == nullptr) {
                leaf->left(new Node(data));
            } else {
                inserter(data, leaf->left());
            }
        } else {
            if (leaf->right() == nullptr) {
                leaf->right(new Node(data));
            } else {
                inserter(data, leaf->right());
            }
        }
    }
    //! Remoção Recursiva
    void removes(T& data, Node* node) {
        if (contain_(data, node)) {
            Node* leaf = search(data, node);
            leaf->remover(data);
            if (leaf -> right() != nullptr && leaf -> left() != nullptr) {
                Node* temp = leaf->right()->minimum();
                leaf->data(temp->data());
                removes(temp->data(), temp);
            } else if (leaf -> right() != nullptr) {
                Node* temp = leaf -> right();
                leaf->left(temp -> left());
                leaf->right(temp ->right());
                delete temp;
            } else if (leaf -> left() != nullptr) {
                Node* temp = leaf -> left();
                leaf->left(temp -> left());
                leaf->right(temp ->right());
                delete temp;
            } else {
                delete leaf;
            }
        }
    }

    //! Funcao Recursiva Destruir
    void destroy(Node* leaf) {
        if (leaf != nullptr) {
            destroy(leaf->left());
            destroy(leaf->right());
            delete leaf;
        }
    }

    Node* root_;
    std::size_t size_;
};

}  //  namespace structures
#endif
