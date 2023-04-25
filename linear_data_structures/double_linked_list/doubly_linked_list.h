/// Copyright [2021] <Ismael Coral Hoepers Heinzelmann>
#include <cstdint>
#include <stdexcept>
#include <stdio.h>
namespace structures {

template <typename T> class DoublyLinkedList {
  public:
    DoublyLinkedList() {
        size_ = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~DoublyLinkedList() { clear(); }

    void clear() {
        while (size() > 0) {
            pop_front();
        }
    }

    void push_back(const T &data) {
        if (empty()) {
            Node *new_tail = new Node(data);
            head = new_tail;
            tail = new_tail;
            size_++;
            return;
        }
        Node *new_tail = new Node(data, tail, nullptr);
        tail->next(new_tail);
        tail = new_tail;
        size_++;
    }
    void push_front(const T &data) {
        if (empty()) {
            Node *new_head = new Node(data);
            head = new_head;
            tail = new_head;
            size_++;
            return;
        }
        Node *new_head = new Node(data, nullptr, head);
        head->prev(new_head);
        head = new_head;
        size_++;
        return;
    }
    void insert(const T &data, std::size_t index) {
        if (index > size()) {
            throw std::out_of_range("");
            return;
        }
        if (index == 0) {
            push_front(data);
            return;
        }
        if (index == size()) {
            push_back(data);
            return;
        }
        if (index < size() / 2) {
            Node *current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next();
            }
            Node *new_node = new Node(data, current->prev(), current);
            current->prev()->next(new_node);
            current->prev(new_node);
            size_++;
            return;
        }
        Node *current = tail;
        for (size_t i = size() - 1; i > index; i--) {
            current = current->prev();
        }
        Node *new_node = new Node(data, current->prev(), current);
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
        return;
    }
    void insert_sorted(const T &data) {
        if (empty()) {
            push_front(data);
            return;
        }
        Node *current = head;
        for (size_t i = 0; i < size(); i++) {
            if (data < current->data()) {
                insert(data, i);
                return;
            }
            current = current->next();
        }
        push_back(data);
        return;
    }

    T pop(std::size_t index) {
        if (index >= size()) {
            throw std::out_of_range("");
        }
        if (index == 0) {
            return pop_front();
        }
        if (index == size() - 1) {
            return pop_back();
        }
        if (index < size() / 2) {
            Node *current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next();
            }
            T data = current->data();
            current->prev()->next(current->next());
            current->next()->prev(current->prev());
            delete current;
            size_--;
            return data;
        } else {
            Node *current = tail;
            for (size_t i = size() - 1; i > index; i--) {
                current = current->prev();
            }
            T data = current->data();
            current->prev()->next(current->next());
            current->next()->prev(current->prev());
            delete current;
            size_--;
            return data;
        }
    }
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (size() == 1) {
            T ret = head->data();
            delete head;
            size_--;
            return ret;
        }

        Node *old_tail = tail;
        Node *new_tail = tail->prev();
        T ret = old_tail->data();

        new_tail->next(nullptr);
        tail = new_tail;
        size_--;
        delete old_tail;
        return ret;
    }
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (size() == 1) {
            T ret = head->data();
            delete head;
            size_--;
            return ret;
        }
        Node *old_head = head;
        Node *new_head = old_head->next();
        T ret = old_head->data();
        new_head->prev(nullptr);
        head = new_head;
        size_--;
        delete old_head;
        return ret;
    }
    void remove(const T &data) {
        Node *current = head;
        for (size_t i = 0; i < size(); i++) {
            if (current->data() == data) {
                Node *prev = current->prev();
                Node *next = current->next();
                prev->next(next);
                next->prev(prev);
                delete current;
                size_--;
                return;
            }
            current = current->next();
        }
    }

    bool empty() const { return size_ == 0 ? true : false; }
    bool contains(const T &data) const {
        return find(data) == size() ? false : true;
    }

    T &at(std::size_t index) {
        if (empty() || index >= size()) {
            throw std::out_of_range("");
        }
        if (index < size() / 2) {
            Node *current = head;
            for (std::size_t i = 0; i < index; i++) {
                current = current->next();
            }
            return current->data();
        }
        Node *current = tail;
        for (std::size_t i = size() - 1; i > index; i--) {
            current = current->prev();
        }
        return current->data();
    }
    const T &at(std::size_t index) const {
        if (empty() || index >= size()) {
            throw std::out_of_range("");
        }
        if (index <= size() / 2) {
            Node *current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next();
            }
            return current->data();
        }
        Node *current = tail;
        for (size_t i = size() - 1; i >= index; i--) {
            current = current->prev();
        }
        return current->data();
    }

    std::size_t find(const T &data) const {
        Node *current = head;
        if (current->data() == data) {
            return 0;
        }
        for (size_t i = 1; i < size(); i++) {
            current = current->next();
            if (current->data() == data) {
                return i;
            }
        }
        return size();
    }
    std::size_t size() const { return size_; }

  private:
    class Node { // implementar cada um dos métodos de Node
      public:
        explicit Node(const T &data) {
            data_ = data;
            prev_ = nullptr;
            next_ = nullptr;
        }
        Node(const T &data, Node *next) {
            data_ = data;
            prev_ = nullptr;
            next_ = next;
        }
        Node(const T &data, Node *prev, Node *next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T &data() { return data_; }
        const T &data() const { return data_; }

        Node *prev() { return prev_; }
        const Node *prev() const { return prev_; }

        void prev(Node *node) { prev_ = node; }

        Node *next() { return next_; }
        const Node *next() const { return next_; }

        void next(Node *node) { next_ = node; }

      private:
        T data_;
        Node *prev_;
        Node *next_;
    };

    Node *head; // primeiro da lista
    Node *tail; // ultimo da lista
    std::size_t size_;
};

} // namespace structures
