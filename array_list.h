/* Copyright [2017] <Vinicius Schwinden Bberkenbrock>
 * ArrayList.h
 *
 *  Created on: 24 de mar de 2017
 *      Author: vinicius
 */

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>      // C++ exceptions

namespace structures {
template<typename T>
//! Classe
/*
 * Classe ArrayList
 */
class ArrayList {
 public:
	//! Construtor
	/*
	 * Construtor da Classe ArrayList
	 */
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size()];
        size_ = 0;
    }
	//! Construtor Parametrizavel
	/*
	 * Construtor da Classe ArrayList Parametrizado
	 * @param max
	 */
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size];
        size_ = 0;
    }
	//! Destrutor
	/*
	 * Destrutor da Classe
	 */
    ~ArrayList() {
	    delete[] contents;
	}
	//! Clear
	/*
	 * Limpa Lista
	 */
    void clear() {
		size_ = 0;
	}
	//!  Insire Atras
    void push_back(const T& data) {
        insert(data, size());
    }
    //!  Insere na Frente
    void push_front(const T& data) {
        insert(data, 0);
    }
    //!  Insere em uma posicao
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw(std::out_of_range("_"));
        } else if (index < max_size()) {
            for (std::size_t i = size(); i > index; i--) {
                contents[i] = contents[i-1];
            }
            contents[index] = data;
            size_++;
        } else {
            throw(std::out_of_range("_"));
        }
    }
    //!  Insere em ordem
    void insert_sorted(const T& data) {
        std::size_t i = 0;
        while (data > contents[i])
            i++;
        insert(data, i);
    }
    //!  Retira na Posicao
    T pop(std::size_t index) {
        if (empty()) {
            throw(std::out_of_range("_"));
        } else {
            T temp = contents[index];
            for (std::size_t i = index; i < max_size_; i++)
                contents[i] = contents[i+1];
            size_--;
            return temp;
        }
        return -1;
    }
    //!  Retira de Tras
    T pop_back() {
        return pop(size()-1);
    }
    //!  Retira da Frente
    T pop_front() {
        return pop(0);
    }
    //! Remove um valor
    void remove(const T& data) {
        if (contains(data)) {
            pop(find(data));
        } else {
            throw(std::out_of_range("_"));
        }
    }
	//! Full
	/*
	 * Retorna se a Fila esta Cheia
	 * @return bool
	 */
    const bool full()  {
		if (size() == max_size()) {
			return true;
		} else {
			return false;
		}
	}
	//! Empty
	/*
	 * Retora se a Fila esta vazia
	 * @return bool
	 */
    bool empty() const {
		if (size() == 0) {
			return true;
		} else {
			return false;
		}
	}
    //!  Verifica se o valor existe
    bool contains(const T& data) const {
        if (contents[find(data)] == data)
            return true;
        else
            return false;
    }
    //!  Procura o valor
    std::size_t find(const T& data) const {
        std::size_t i = 0;
        if (empty()) {
            throw(std::out_of_range("_"));
        } else {
            do {
                if (contents[i] == data)
                    break;
                else
                    i++;
            } while (i <= size());
                if (contents[i] == data)
                    return i;
        }
        return 0;
    }
	//! Size
	/*
	 * Retorna o tamanho da Fila
	 */
    std::size_t size() const {
		return size_;
	}
	//! MaxSize
	/*
	 * Retorna o tamanho maximo da Fila
	 */
    std::size_t max_size() const {
		return max_size_;
	}
    //!  Operador
    T& at(std::size_t index) {
        if (index >= 0) {
            if (index < size()) {
                return contents[index];
            } else {
                throw(std::out_of_range("_"));
            }
        } else {
            throw(std::out_of_range("_"));
        }
    }
    //!  Operador
    T& operator[](std::size_t index) {
        if (index >= 0) {
            if (index < size()) {
                return contents[index];
            } else {
                throw(std::out_of_range("_"));
            }
        } else {
            throw(std::out_of_range("_"));
        }
    }
    //!  Operador
    const T& at(std::size_t index) const {
        if (index >= 0) {
            if (index < size()) {
                return contents[index];
            } else {
                throw(std::out_of_range("_"));
            }
        } else {
            throw(std::out_of_range("_"));
        }
    }
    //!  Operador
    const T& operator[](std::size_t index) const {
        if (index >= 0) {
            if (index < size()) {
                return contents[index];
            } else {
                throw(std::out_of_range("_"));
            }
        } else {
            throw(std::out_of_range("_"));
        }
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};
}  // namespace structures
#endif /* ARRAYLIST_H_ */
