//
// Created by xzy54 on 2025/5/16.
//
#pragma once
#ifndef SLIMENANO_UTILS_SRC_AVL_TREE_HPP_
#define SLIMENANO_UTILS_SRC_AVL_TREE_HPP_
#include <cstddef>
#include <functional>
#include <stdexcept>

namespace slimenano {

    template <typename T>
    class avl_tree {
    public:
        using avl_visitor = std::function<void(const T& data, const int& height)>;
    private:
        class avl_node {
            friend avl_tree;

            struct modify_result {
                avl_node* node;
                bool modified;
            };

            static auto get_height(const avl_node* node) -> int;
            static auto right_rotate(avl_node* node) -> avl_node*;
            static auto left_rotate(avl_node* node) -> avl_node*;
            static auto rotate(avl_node* node) -> avl_node*;
            static auto insert_helper(avl_node* node, const T& key) -> modify_result;
            static auto remove_helper(avl_node* node, const T& key) -> modify_result;
            static auto destroy_helper(avl_node* node) -> void;
            static auto clone_helper(avl_node* node) -> avl_node*;
            static auto inorder_helper(avl_node* node, avl_visitor visitor) -> void;

            T key;
            int height = 0;
            avl_node* left = nullptr;
            avl_node* right = nullptr;

            explicit avl_node(const T& key) noexcept : key(key) {
            }

            void update_height();
            auto balance_factor() const -> int;
        };

    public:
        avl_tree() = default;
        avl_tree(const avl_tree& other);
        avl_tree(avl_tree&& other) noexcept;
        avl_tree& operator=(const avl_tree& other);
        avl_tree& operator=(avl_tree&& other) noexcept;
        ~avl_tree() noexcept;

        void insert(const T& key);
        void remove(const T& key);
        auto contains(const T& key) const -> bool;
        auto min() const -> T;
        auto max() const -> T;
        auto size() const -> size_t;
        auto empty() const -> bool;
        auto clear() -> void;
        auto inorder_traversal(avl_visitor visitor) const -> void;
        auto bfs_traversal(avl_visitor visitor) const -> void;

    private:
        avl_node* root = nullptr;
        size_t tree_size = 0;
    };

    template <typename T>
    auto avl_tree<T>::avl_node::get_height(const avl_node* node) -> int {
        return node != nullptr ? node->height : -1;
    }

    template <typename T>
    void avl_tree<T>::avl_node::update_height() {
        const int left_height = avl_node::get_height(this->left);
        const int right_height = avl_node::get_height(this->right);
        this->height = (left_height > right_height ? left_height : right_height) + 1;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::balance_factor() const -> int {
        return avl_node::get_height(this->left) - avl_node::get_height(this->right);
    }

    template <typename T>
    auto avl_tree<T>::avl_node::right_rotate(avl_node* node) -> avl_node* {
        avl_node* child = node->left;
        avl_node* grand_child = child->right;
        child->right = node;
        node->left = grand_child;
        node->update_height();
        child->update_height();
        return child;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::left_rotate(avl_node* node) -> avl_node* {
        avl_node* child = node->right;
        avl_node* grand_child = child->left;
        child->left = node;
        node->right = grand_child;
        node->update_height();
        child->update_height();
        return child;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::rotate(avl_node* node) -> avl_node* {
        const int balance_factor = node->balance_factor();
        if (balance_factor > 1) {
            if (node->left != nullptr && node->left->balance_factor() < 0) {
                node->left = left_rotate(node->left);
            }
            return right_rotate(node);
        }
        if (balance_factor < -1) {
            if (node->right != nullptr && node->right->balance_factor() > 0) {
                node->right = right_rotate(node->right);
            }
            return left_rotate(node);
        }
        return node;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::insert_helper(avl_node* node, const T& key) -> modify_result {
        if (node == nullptr) {
            return {new avl_node(key), true};
        }
        modify_result result = {nullptr, false};
        if (key < node->key) {
            modify_result left_result = insert_helper(node->left, key);
            node->left = left_result.node;
            result.modified = left_result.modified;
            result.node = node;
        } else if (key > node->key) {
            modify_result right_result = insert_helper(node->right, key);
            node->right = right_result.node;
            result.modified = right_result.modified;
            result.node = node;
        } else {
            return {node, false};
        }
        if (result.node != nullptr) {
            result.node->update_height();
            result.node = rotate(result.node);
        }
        return result;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::remove_helper(avl_node* node, const T& key) -> modify_result {
        if (node == nullptr) {
            return {nullptr, false};
        }
        modify_result result = {nullptr, false};
        if (key < node->key) {
            modify_result left_result = remove_helper(node->left, key);
            node->left = left_result.node;
            result.modified = left_result.modified;
            result.node = node;
        } else if (key > node->key) {
            modify_result right_result = remove_helper(node->right, key);
            node->right = right_result.node;
            result.modified = right_result.modified;
            result.node = node;
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                avl_node* child = node->left != nullptr ? node->left : node->right;
                if (child == nullptr) {
                    delete node;
                    return {nullptr, true};
                }
                delete node;
                result.modified = true;
                result.node = child;
            } else {
                avl_node* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                const T& tempVal = successor->key;
                node->key = successor->key;
                modify_result right_result = remove_helper(node->right, tempVal);
                node->right = right_result.node;
                result.modified = right_result.modified;
                result.node = node;
            }
        }
        if (result.node != nullptr) {
            result.node->update_height();
            result.node = rotate(result.node);
        }
        return result;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::destroy_helper(avl_node* node) -> void {
        if (node == nullptr) {
            return;
        }
        destroy_helper(node->left);
        destroy_helper(node->right);
        delete node;
    }


    template <typename T>
    auto avl_tree<T>::avl_node::clone_helper(avl_node* node) -> avl_node* {
        if (node == nullptr) {
            return nullptr;
        }
        auto* clone = new avl_node(node->key);
        clone->left = clone_helper(node->left);
        clone->right = clone_helper(node->right);
        clone->update_height();
        return clone;
    }

    template <typename T>
    auto avl_tree<T>::avl_node::inorder_helper(avl_node* node, avl_visitor visitor) -> void {
        if (node == nullptr) {
            return;
        }
        inorder_helper(node->left, visitor);
        visitor(node->key, node->height);
        inorder_helper(node->right, visitor);
    }

    template <typename T>
    avl_tree<T>::~avl_tree() noexcept {
        if (this->root != nullptr) {
            avl_node::destroy_helper(this->root);
            this->root = nullptr;
            this->tree_size = 0;
        }
    }

    template <typename T>
    avl_tree<T>::avl_tree(const avl_tree& other) {
        this->root = avl_node::clone_helper(other.root);
        this->tree_size = other.tree_size;
    }

    template <typename T>
    avl_tree<T>::avl_tree(avl_tree&& other) noexcept {
        this->root = other.root;
        other.root = nullptr;
        this->tree_size = other.tree_size;
        other.tree_size = 0;
    }

    template <typename T>
    avl_tree<T>& avl_tree<T>::operator=(const avl_tree& other) {
        if (this == &other) {
            return *this;
        }
        if (this->root != nullptr) {
            avl_node::destroy_helper(this->root);
        }
        this->root = avl_node::clone_helper(other.root);
        this->tree_size = other.tree_size;
        return *this;
    }

    template <typename T>
    avl_tree<T>& avl_tree<T>::operator=(avl_tree&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        if (this->root != nullptr) {
            avl_node::destroy_helper(this->root);
        }
        this->root = other.root;
        other.root = nullptr;
        this->tree_size = other.tree_size;
        other.tree_size = 0;
        return *this;
    }

    template <typename T>
    auto avl_tree<T>::contains(const T& key) const -> bool {
        avl_node* node = this->root;
        while (node != nullptr) {
            if (key < node->key) {
                node = node->left;
            } else if (key > node->key) {
                node = node->right;
            } else {
                return true;
            }
        }
        return false;
    }

    template <typename T>
    auto avl_tree<T>::min() const -> T {
        if (this->empty()) {
            throw std::out_of_range("AVL_TREE is a empty tree");
        }
        avl_node* node = this->root;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->key;
    }

    template <typename T>
    auto avl_tree<T>::max() const -> T {
        if (this->empty()) {
            throw std::out_of_range("AVL_TREE is a empty tree");
        }
        avl_node* node = this->root;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node->key;
    }

    template <typename T>
    auto avl_tree<T>::size() const -> size_t {
        return this->tree_size;
    }

    template <typename T>
    auto avl_tree<T>::empty() const -> bool {
        return this->size() == 0;
    }

    template <typename T>
    auto avl_tree<T>::clear() -> void {
        avl_node::destroy_helper(this->root);
        this->root = nullptr;
        this->tree_size = 0;
    }

    template <typename T>
    void avl_tree<T>::insert(const T& key) {
        auto result = avl_node::insert_helper(this->root, key);
        this->root = result.node;
        if (result.modified) {
            ++this->tree_size;
        }
    }

    template <typename T>
    void avl_tree<T>::remove(const T& key) {
        auto result = avl_node::remove_helper(this->root, key);
        this->root = result.node;
        if (result.modified) {
            --this->tree_size;
        }
    }

    template <typename T>
    auto avl_tree<T>::inorder_traversal(avl_visitor visitor) const -> void {
        avl_node::inorder_helper(this->root, visitor);
    }

    template <typename T>
    auto avl_tree<T>::bfs_traversal(avl_visitor visitor) const -> void {
        if (this->empty()) {
            return;
        }
        struct linked_queue {
            avl_node* node = nullptr;
            linked_queue* next = nullptr;
        };

        auto* head = new linked_queue();
        auto* tail = head;
        head->node = this->root;

        while (head != nullptr) {
            auto node = head->node;
            visitor(node->key, node->height);
            if (node->left != nullptr) {
                tail->next = new linked_queue();
                tail = tail->next;
                tail->node = node->left;
            }
            if (node->right != nullptr) {
                tail->next = new linked_queue();
                tail = tail->next;
                tail->node = node->right;
            }
            auto next = head->next;
            delete head;
            head = next;
        }

    }


}

#endif //SLIMENANO_UTILS_SRC_AVL_TREE_HPP_