// Copyright [2023] <Ismael Coral Hoepers Heinzelmann>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template <typename T> class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T &data);
    void push_front(const T &data);
    void insert(const T &data, std::size_t index);
    void insert_sorted(const T &data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T &data);
    bool full() const;
    bool empty() const;
    bool contains(const T &data) const;
    std::size_t find(const T &data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T &at(std::size_t index);
    T &operator[](std::size_t index);
    const T &at(std::size_t index) const;
    const T &operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T *contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

#endif

template <typename T> inline ArrayList<T>::ArrayList() {
    contents = new T[DEFAULT_MAX];
    size_ = 0;
    max_size_ = DEFAULT_MAX;
}

template <typename T> inline ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template <typename T> inline ArrayList<T>::~ArrayList() { delete[] contents; }

template <typename T> inline void ArrayList<T>::clear() { size_ = 0; }

template <typename T> inline void ArrayList<T>::push_front(const T &data) {
    if (full()) {
        throw std::out_of_range("list full");
    }
    size_++;
    for (size_t i = size() - 1; i > 0; i--) {
        contents[i] = contents[i - 1];
    }
    contents[0] = data;
}

template <typename T> inline void ArrayList<T>::push_back(const T &data) {
    if (full()) {
        throw std::out_of_range("list full");
    }
    size_++;
    contents[size() - 1] = data;
}

template <typename T>
inline void ArrayList<T>::insert(const T &data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("list full");
    }
    if (index >= size()) {
        throw std::out_of_range("out of bounds");
    }
    size_++;
    for (size_t i = size() - 1; i > index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
}

template <typename T> inline void ArrayList<T>::insert_sorted(const T &data) {
    if (full()) {
        throw std::out_of_range("list empty");
    }

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

template <typename T> inline T ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("list empty");
    }
    if (index >= size()) {
        throw std::out_of_range("index out of bounds");
    }

    T ret;
    memcpy(&ret, &contents[index], sizeof(T));
    size_--;

    for (size_t i = index; i < size(); i++) {
        contents[i] = contents[i + 1];
    }
    return ret;
}

template <typename T> inline T ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("list empty");
    }
    size_--;
    return contents[size()];
}

template <typename T> inline T ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("list empty");
    }
    T ret;
    memcpy(&ret, contents, sizeof(T));

    size_--;
    for (size_t i = 0; i < size(); i++) {
        contents[i] = contents[i + 1];
    }
    return ret;
}

template <typename T> inline void ArrayList<T>::remove(const T &data) {
    size_t index = find(data);

    if (index != max_size()) {
        for (size_t i = index; i < size(); i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
    }
}

template <typename T> inline bool ArrayList<T>::full() const {
    return max_size() == size() ? true : false;
}

template <typename T> inline bool ArrayList<T>::empty() const {
    return size() == 0 ? true : false;
}

template <typename T> inline bool ArrayList<T>::contains(const T &data) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    return find(data) == max_size() ? false : true;
}

template <typename T>
inline std::size_t ArrayList<T>::find(const T &data) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    for (size_t i = 0; i < size(); i++) {
        if (data == contents[i]) {
            return i;
        }
    }
    return max_size();
}

template <typename T> inline std::size_t ArrayList<T>::size() const {
    return size_;
}

template <typename T> inline std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T> inline T &ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    if (index >= size()) {
        throw std::out_of_range("out of bounds");
    }

    return contents[index];
}

template <typename T> inline T &ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template <typename T>
inline const T &ArrayList<T>::at(std::size_t index) const {
    return at(index);
}

template <typename T>
inline const T &ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
}  // namespace structures
