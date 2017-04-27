//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions
#include "array_list.h"

namespace structures {

template<typename X>

//! Arvore Binaria
class BinaryTree {
 public:
    //! Construtor
    BinaryTree() {
        root = nullptr;
        size_ = 0;
    }
    //! Destrutor
    ~BinaryTree() {
        destroy(root);
        size_ = 0;
        root = nullptr;
    }

    //! Insersor
    void insert(const X& data) {
        insert(data, root);
        size_++;
    }
    //! Remoção
    void remove(const X& data) {
        removes(data, root);
        size_--;
    }

    //! Contem
    bool contains(const X& data) const {
        return contains(root, data);
    }
    //! Vazio
    bool empty() const {
        return !size();
    }

    //! Xamanho
    std::size_t size() const {
        return size_;
    }
    //! Ordenacao
    /*ArrayList<X> pre_order() const {
            return new ArrayList();
        }
    //! Ordenacao
    ArrayList<X> in_order() const {
            return new ArrayList();
        }
    //! Ordenacao
    ArrayList<X> post_order() const {
            return new ArrayList();
        }*/

 private:
    struct Node {
         public:
        explicit Node(X& data_):
            data{data_}
        {}


        void insert(const X& data_) {
            data = data_;
        }

        bool remove(const X& data_) {
            if (contains(data_)) {
                delete *data;
                return true;
            }
            return false;
        }

        //!  Contem
        bool contains(const X& data_) const {
            if (data == data_) {
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
        void pre_order(ArrayList<X>& v) const {
            true;
        }

        //!  Ordena
        void in_order(ArrayList<X>& v) const {
            true;
        }

        //!  Ordena
        void post_order(ArrayList<X>& v) const {
            true;
        }

        Node* left() {  // getter: próximo
            return left;
        }
        const Node* left() const {  // getter const: próximo
            return left;
        }
        void left(Node* node) {  // setter: próximo
            left = node;
        }

        Node* right() {  // getter: anterior
            return right;
        }
        const Node* right() const {  // getter: anterior
            return right;
        }
        void right(Node* node) {  // setter: anterior
            right = node;
        }
        X& data() {
            return data;
        }
        const X& data() const {
            return data;
        }

         private:
        X data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    //! Contem
    bool contains(Node* leaf, X& data) const {
        if (leaf != nullptr) {
            if (leaf->contains(data)) {
                return true;
            } else if (leaf->data < data) {
                contains(leaf->left(), data);
            } else {
                contains(leaf->right(), data);
            }
        }
        return false;
    }
    //! Procura Nodo
    Node* search(Node* leaf, X& data) {
        if (leaf != nullptr) {
            if (leaf->contains(data)) {
                return leaf;
            } else if (leaf->left()->contains(data)) {
                return leaf->left();
            } else if (leaf->right()->contains(data)) {
                return leaf->right();
            } else if (leaf->data() < data) {
                search(leaf->left(), data);
            } else {
                search(leaf->right(), data);
            }
        }
        return nullptr;
    }

    //! Insert Recursivo
    void insert(X& data, Node* leaf) {
        if (leaf == nullptr) {
            leaf = new Node(data);
        } else if (data <= leaf->data) {
            if (leaf->left() == nullptr) {
                leaf->left(new Node(data));
            } else {
                insert(data, leaf->left());
            }
        } else {
            if (leaf->right() == nullptr) {
                leaf->right(new Node(data));
            } else {
                insert(data, leaf->right());
            }
        }
    }
    //! Remoção Recursiva
    void removes(const X& data, Node* node) {
        if (contains(node, data)) {
            Node* leaf = search(node, data);
            leaf->remove(data);
            if (leaf -> right() != nullptr & leaf -> left() != nullptr) {
                Node* temp = leaf->right()->minimum();
                leaf->insert(temp->data);
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

    Node* root;
    std::size_t size_;
};

}  //  namespace structures
#endif
