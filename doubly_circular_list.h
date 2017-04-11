//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef STRUCTURES_DOUBLE_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLE_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions


namespace structures {

template<typename T>
//! lista encadeada circular
class DoublyCircularList {
 public:
//! construtor padrão
    DoublyCircularList() {
        size_ = 0u;
        head = nullptr;
    }
    ~DoublyCircularList() {  // destrutor
        clear();
        delete[] head;
    }
    //! limpar lista
    void clear() {
        for (auto i = 0u; i < size(); i++)
            pop_back();
        head = nullptr;
        size_ = 0;
    }
    //! inserir no fim
    void push_back(const T& data) {
		if (empty()) {
			return push_front(data);
		} else {
		    auto temp = new Node(data, end(), head);
			end()->next(temp);
			head->prev(temp);
		}
        ++size_;
    }
    //! inserir no início
    void push_front(const T& data) {
        auto temp = new Node(data);
        if (empty()) {
            head = temp;
            head->prev(temp);
            head->next(temp);
        } else if (size() == 1) {
            temp->next(head);
            temp->prev(head);
            head->prev(temp);
            head->next(temp);
            head = temp;
        } else {
            temp->next(head);
            temp->prev(end());
            head->prev(temp);
            head = temp;
        }
        size_++;
    }
    //! inserir na posição
    void insert(const T& data, std::size_t index) {
		if (index < 0 || index > size()) throw(std::out_of_range("_"));
		if (index == 0) return push_front(data);
		if (index == size()) return push_back(data);
		auto temp = indexNode(index);
		auto novo = new Node(data, temp->prev(), temp);
		temp->prev(novo);
		novo->prev()->next(novo);
        ++size_;
    }
    //! inserir em ordem
    void insert_sorted(const T& data) {
		if (empty()) return push_front(data);
		if (size() == 1) {
		    if (head->data() >= data) return push_front(data);
		    else
		        return push_back(data);
		}
		if(end()->data() <= data)
		    return push_back(data);
		if(head->data() >= data)
		    return push_front(data);
		auto current = head;
		auto i = 0u;
		while (current != end()) {
		    current = current->next();
		    i++;
		    if (current->data() >= data) break;
		}
		insert(data, i);
    }
    //! retirar da posição
    T pop(std::size_t index) {
		++index;
		if (empty()) throw (std::out_of_range("_"));
		if (index < 0 || index > size()) throw(std::out_of_range("_"));
		if (index == 0) return pop_front();
		if (index == size()) return pop_back();
		auto current = indexNode(index-1);
		T retorno = current->data();
		current->prev()->next(current->next());
		current->next()->prev(current->prev());
		delete current;
		--size_;
        return retorno;
    }
    //! retirar do fim
    T pop_back() {
		if (empty()) throw (std::out_of_range("_"));
		if (size() == 1) return pop_front();
		auto current = end();
		T retorno = current->data();
		auto temp = current->prev();
		temp->next(head);
		head->prev(temp);
		delete current;
		--size_;
        return retorno;
    }
    //! retirar do início
    T pop_front() {
		if (empty()) throw (std::out_of_range("_"));
		auto current = head;
		T retorno = current->data();
		if(size() == 1) {
		    head = nullptr;
		} else if (head->next()) {
    		current->prev()->next(current->next());
    		current->next()->prev(current->prev());
    		head = current->next();
		}
		delete current;
		--size_;
        return retorno;
    }
    //! remover específico
    void remove(const T& data) {
        if (contains(data))
            pop(find(data));
        else
            throw(std::out_of_range("_"));
    }
    //! lista vazia
    bool empty() const {
        if (size() == 0) return true;
        else
            return false;
    }
    //! contém
    bool contains(const T& data) const {
        auto temp = head;
		for (auto i = 0u; i < size(); i++) {
		    temp = temp->next();
		    if (temp->data() == data) return true;
		}
        return false;
    }
    //! acessar um elemento na posição index
    T& at(std::size_t index) {
		if (empty()) throw (std::out_of_range("_"));
		if (index < 0 || index > size()) throw(std::out_of_range("_"));
		return indexNode(index)->data();
    }
    //!  posição do dado
    std::size_t find(const T& data) const {
        auto temp = head;
		for (auto i = 0u; i <= size(); i++) {
		    if (temp->data() == data) return i;
		    temp = temp->next();
		}
		return size();  //  se tiver na ultima posicao
    }
    //! tamanho da lista
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

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
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

        Node* prev() {  // getter: anterior
            return prev_;
        }
        const Node* prev() const {  // getter: anterior
            return prev_;
        }

        void prev(Node* node) {  // setter: anterior
            prev_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
        Node* prev_{nullptr};
    };


    Node* end() {  // último nodo da lista
        return head->prev();
    }

    Node* indexNode(std::size_t index) {  // nodo da lista no index
		auto i = 0u;
		auto current = head;
		while (i < index) {
			current = current->next();
			++i;
		}
		return current;
    }

    Node* head;
    std::size_t size_;
};

}  //  namespace structures
#endif
