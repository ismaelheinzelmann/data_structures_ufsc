#include "array_list.h"
#include <iostream>

namespace structures {

template <typename T> class BinaryTree {
  public:
    ~BinaryTree() { delete root; }

    void insert(const T &data) {
        if (empty()) {
            root = new Node(data);
            size_++;
            return;
        }
        if (root->insert(data)) {
            size_++;
        }
    }

    void remove(const T &data) {
        if (!empty() && root->remove(data)) {
            size_--;
        }
    }

    bool contains(const T &data) const {
        return empty() ? false : root->contains(data);
    }

    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

    ArrayList<T> pre_order() const {
        ArrayList<T> result = ArrayList<T>();
        if (empty()) {
            return result;
        }
        root->pre_order(result);
        return result;
    }

    ArrayList<T> in_order() const {
        ArrayList<T> result = ArrayList<T>();
        if (empty()) {
            return result;
        }
        root->in_order(result);
        return result;
    }

    ArrayList<T> post_order() const {
        ArrayList<T> result = ArrayList<T>();
        if (empty()) {
            return result;
        }
        root->post_order(result);
        return result;
    }

  private:
    struct Node {
        Node(const T &data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }

        ~Node() {
            if (this->left != nullptr) {
                delete this->left;
            }
            if (this->right != nullptr) {
                delete this->right;
            }
        }

        T data;
        Node *left;
        Node *right;

        bool insert(const T &data_) {
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    this->left = new Node(data_);
                    return true;
                } else {
                    return this->left->insert(data_);
                }
            } else if (data_ > this->data) {
                if (this->right == nullptr) {
                    this->right = new Node(data_);
                    return true;
                } else {
                    return this->right->insert(data_);
                }
            }
            return false; // Node already contains the data, no insertion needed
        }

        bool remove(const T &data_) {
            if (data_ == this->data) {
                if (left == nullptr && right == nullptr) {
                    delete this;
                    return true;
                } else if (left != nullptr && right != nullptr) {
                    this->data = right->data;
                    delete this->right;
                    this->right = nullptr;
                    return true;
                } else if (left != nullptr) {
                    this->data = left->data;
                    delete this->left;
                    this->left = nullptr;
                    return true;
                } else if (right != nullptr) {
                    this->data = right->data;
                    delete right;
                    this->right = nullptr;
                }
            } else if (data_ < this->data) {
                if (this->left == nullptr) {
                    return false;
                } else if (this->left->data == data_) {
                    delete this->left;
                    this->left = nullptr;
                    return true;
                }
                return this->left->remove(data_);
            } else if (data_ > this->data) {
                if (this->right == nullptr) {
                    return false;
                } else if (this->right->data == data_) {
                    delete this->right;
                    this->right = nullptr;
                    return true;
                }
                return this->right->remove(data_);
            }
            return false;
        }

        bool contains(const T &data_) const {
            if (data_ == this->data) {
                return true;
            } else if (data_ < this->data) {
                return this->left != nullptr && this->left->contains(data_);
            } else if (data_ > this->data) {
                return this->right != nullptr && this->right->contains(data_);
            }
            return false;
        }

        void pre_order(ArrayList<T> &v) const {
            v.push_back(this->data);
            if (this->left != nullptr) {
                this->left->pre_order(v);
            }
            if (this->right != nullptr) {
                this->right->pre_order(v);
            }
        }

        void in_order(ArrayList<T> &v) const {
            if (this->left != nullptr) {
                this->left->in_order(v);
            }
            v.push_back(this->data);
            if (this->right != nullptr) {
                this->right->in_order(v);
            }
        }

        void post_order(ArrayList<T> &v) const {
            if (this->left != nullptr) {
                this->left->post_order(v);
            }
            if (this->right != nullptr) {
                this->right->post_order(v);
            }
            v.push_back(this->data);
        }
    };

    Node *root;
    std::size_t size_;
};

} // namespace structures