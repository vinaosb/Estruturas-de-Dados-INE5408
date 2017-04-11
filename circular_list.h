//! Copyright [2017] <Vinicius Schwinden Berkenbrock>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>      // C++ exceptions


namespace structures {

template<typename T>
//! lista circular
class CircularList {
 public:
//! construtor padrão
    CircularList() {
        size_ = 0u;
        head = nullptr;
    }
    ~CircularList() {  // destrutor
        clear();
        delete head;
    }
    //! limpar lista
    void clear() {
        for (auto i = 0u; !empty(); i++)
            pop_front();
        head = nullptr;
        size_ = 0;
    }
    //! inserir no fim
    void push_back(const T& data) {
		if (empty()) {
			return push_front(data);
		} else {
			end()->next(new Node(data, head));
		}
        ++size_;
    }
    //! inserir no início
    void push_front(const T& data) {
        if (empty()) {
            head = new Node(data);
            head->next(head);
        } else {
            head = new Node(data, head);
        }
        size_++;
    }
    //! inserir na posição
    void insert(const T& data, std::size_t index) {
		if (index < 0 || index > size()) throw(std::out_of_range("_"));
		if (index == 0) return push_front(data);
		if (index == size()) return push_back(data);
		indexNode(index-1)->next(new Node(data, indexNode(index)));
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
		if(head->data() >= data)
		    return push_front(data);
		if(end()->data() <= data)
		    return push_back(data);
		auto current = head;
		auto i = 0u;
		while (current != end()) {
		    current = current->next();
		    i++;
		    if (current->data() >= data) break;
		}
		insert(data, i);
    }
    //! acessar um elemento na posição index
    T& at(std::size_t index) {
		if (empty()) throw (std::out_of_range("_"));
		if (index < 0 || index > size()) throw(std::out_of_range("_"));
		return indexNode(index)->data();
    }
    //! retirar da posição
    T pop(std::size_t index) {
		if (empty()) throw (std::out_of_range("_"));
		if (index < 0 || index >= size()) throw(std::out_of_range("_"));
		if (index == 0) return pop_front();
		if (index == size()-1) return pop_back();
		auto current = indexNode(index);
		auto old = indexNode(index-1);
		T retorno = current->data();
		old->next(current->next());
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
		auto old = indexNode(size()-2);
		old -> next(head);
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
		} else {
    		end()->next(head->next());
    		head = head->next();
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
        return !size();
    }
    //! contém
    bool contains(const T& data) const {
		auto current = head;
		while (current) {
			if (current->data() == data) return true;
			current = current->next();
			if (current == head) break;
		}
        return false;
    }
    //!  posição do dado
    std::size_t find(const T& data) const {
		auto i = 0u;
		auto current = head;
		while (current) {
			if (current->data() == data) return i;
			if (i == size()) break;
			current = current->next();
			++i;
		}
		return size();
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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
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

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  //  namespace structures
#endif

