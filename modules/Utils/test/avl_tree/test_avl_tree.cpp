
#include <iostream>
#include "slimenano/avl_tree.hpp"

auto main() -> int {

    slimenano::avl_tree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    std::cout << tree.size() << std::endl;
    tree.insert(8);
    std::cout << tree.size() << std::endl;

    tree.remove(1);
    tree.remove(2);
    tree.remove(3);
    std::cout << tree.size() << std::endl;

    tree.remove(3);
    std::cout << tree.size() << std::endl;

    tree.remove(3);
    std::cout << tree.size() << std::endl;

    tree.inorder_traversal([](const int& key, const int& height) -> void {
        std::cout << key << "(" << height << ")" << std::ends;
    });
    std::cout << std::endl;


    tree.bfs_traversal([](const int& key, const int& height) -> void {
        std::cout << key << "(" << height << ")" << std::ends;
    });

    std::cout << std::endl;

    return 0;

}