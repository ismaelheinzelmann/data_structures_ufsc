// Copyright 2023 <Ismael Coral Hoepers Heinzelmann>
namespace structures {

template <typename T> class DoublyCircularList {
 public:
    DoublyCircularList() {
        head = nullptr;
        size_ = 0;
    }
    ~DoublyCircularList() { clear(); }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_front(const T &data) {
        if (empty()) {
            Node *new_node = new Node(data);
            head = new_node;
            head->next(new_node);
            head->prev(new_node);
            size_++;
            return;
        }
        Node *new_node = new Node(data, head->prev(), head);
        head->prev()->next(new_node);
        head->prev(new_node);
        head = new_node;
        size_++;
    }
    void push_back(const T &data) {
        if (empty()) {
            push_front(data);
            return;
        }
        Node *tail = head->prev();
        Node *new_node = new Node(data, tail, head);
        tail->next(new_node);
        head->prev(new_node);
        size_++;
    }
    void insert(const T &data, std::size_t index) {
        if (index > size()) {
            throw std::out_of_range("");
        }
        if (index == 0) {
            push_front(data);
            return;
        }
        if (index == size()) {
            push_back(data);
            return;
        }
        Node *current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next();
        }
        Node *new_node = new Node(data, current->prev(), current);
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }
    void insert_sorted(const T &data) {
        if (empty()) {
            push_front(data);
            return;
        }
        Node *current = head;
        size_t index = 0;
        while (current->data() < data) {
            current = current->next();
            index++;
            if (index == size()) {
                break;
            }
        }
        insert(data, index);
    }

    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (index >= size()) {
            throw std::out_of_range("");
        }
        if (index == 0) {
            return pop_front();
        }
        if (index == size() - 1) {
            return pop_back();
        }
        Node *current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next();
        }
        T data = current->data();
        current->prev()->next(current->next());
        current->next()->prev(current->prev());
        size_--;
        delete current;
        return data;
    }
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (size() == 1) {
            return pop_front();
        }
        Node *current = head->prev();
        T data = current->data();
        current->prev()->next(head);
        head->prev(current->prev());
        size_--;
        delete current;
        return data;
    }
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("");
        }
        Node *current = head;
        T data = current->data();
        head = current->next();
        head->prev(current->prev());
        current->prev()->next(head);
        size_--;
        delete current;
        return data;
    }
    void remove(const T &data) {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (head->data() == data) {
            pop_front();
            return;
        }
        Node *current = head;
        while (current->data() != data) {
            current = current->next();
            if (current == head) {
                throw std::out_of_range("");
            }
        }
        current->prev()->next(current->next());
        current->next()->prev(current->prev());
        size_--;
        delete current;
    }

    bool empty() const { return size() == 0; }
    bool contains(const T &data) const {
        if (empty()) {
            throw std::out_of_range("");
        }
        Node *current = head;
        while (current->data() != data) {
            current = current->next();
            if (current == head) {
                return false;
            }
        }
        return true;
    }

    T &at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (index >= size()) {
            throw std::out_of_range("");
        }
        Node *current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
    const T &at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("");
        }
        if (index >= size()) {
            throw std::out_of_range("");
        }
        Node *current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }

    std::size_t find(const T &data) const {
        if (empty()) {
            throw std::out_of_range("");
        }
        Node *current = head;
        size_t index = 0;
        while (current->data() != data) {
            current = current->next();
            index++;
            if (index == size()) {
                break;
            }
        }
        return index;
    }
    std::size_t size() const { return size_; }

 private:
    class Node {  // implementar cada um dos métodos de Node
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

    Node *head;
    std::size_t size_;
};

}  // namespace structures
