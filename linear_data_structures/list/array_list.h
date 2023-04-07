#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template <typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template <typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = (size_t)(-1);
}

template <typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size];
    size_ = (size_t)(-1);
}

template <typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template <typename T>
void structures::ArrayList<T>::clear() {
    delete[] contents;
    contents = new T[max_size_];
    size_ = (size_t)(-1);
}

template <typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    size_++;
    contents[size_] = data;
}

template <typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    size_++;
    for (int i = size_; i > 0; i--) {
        contents[i] = contents[i - 1];
    }
    contents[0] = data;
}

template <typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (static_cast<int>(index) < 0 || index >= size()) {
        throw std::out_of_range("out of bounds");
    }
    size_++;
    for (size_t i = size_; i > index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
}

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    }
    if (data < contents[0]) {
        push_front(data);
        return;
    }
    if (data > contents[size_]) {
        push_back(data);
        return;
    }

    for (int i = 1; i <= static_cast<int>(size_); i++) {
        if (data > contents[i - 1] && data < contents[i]) {
            insert(data, i);
            return;
        }
    }
}

template <typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    int at_index = at(index);

    remove(at_index);
    return at_index;
}

template <typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    size_--;
    return contents[size_ + 1];
}

template <typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    T ret = contents[0];
    for (int i = 0; i < static_cast<int>(size_); i++) {
        contents[i] = contents[i + 1];
    }
    size_--;
    return ret;
}

template <typename T>
void structures::ArrayList<T>::remove(const T& data) {
    int index = find(data);
    if (index == -1) {
        return;
    }

    for (int i = index; i < static_cast<int>(size_); i++) {
        contents[i] = contents[i + 1];
    }
    size_--;
}

template <typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < static_cast<int>(size()); i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template <typename T>
inline std::size_t structures::ArrayList<T>::find(const T& data) const {
    for (size_t i = 0; i <= size_; i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return (size_t)(-1);
}

template <typename T>
inline std::size_t structures::ArrayList<T>::size() const {
    return size_ + 1;
}

template <typename T>
inline std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
inline T& structures::ArrayList<T>::at(std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("index fora do alcance permitido");
    }

    return contents[index];
}

template <typename T>
inline T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template <typename T>
inline const T& structures::ArrayList<T>::at(std::size_t index) const {
    return at(index);
}

template <typename T>
inline const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}

template <typename T>
bool structures::ArrayList<T>::full() const {
    if (size() == max_size()) {
        return true;
    } else {
        return false;
    }
}
template <typename T>
bool structures::ArrayList<T>::empty() const {
    if (size_ == (size_t)(-1)) {
        return true;
    } else {
        return false;
    }
}
