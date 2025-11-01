#define BLOCK_2

#include <iostream>
#include <random>
#include "BST.h"
#include "AVLTree.h"

const int MAX_ID = 1 << 20;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution random_id(1, MAX_ID);
std::uniform_int_distribution random_score(0, 100);

void generate_data(std::vector<std::pair<int, int>> &data, size_t count)
{
    data.clear();
    data.reserve(count + 5);
    for (size_t i = 0; i < count; ++i)
        data.emplace_back(random_id(gen), random_score(gen));
}

void generate_id(std::vector<int> &data, size_t count)
{
    data.clear();
    data.reserve(count + 5);
    for (size_t i = 0; i < count; ++i)
        data.push_back(random_id(gen));
}

#ifdef BLOCK_1
int main() {
    // BST test
    std::cout << "BST Test :\n";
    std::cout << "Insert data : (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)\n";
    BST bst;
    // (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)
    bst.insert(3, 100);
    bst.insert(2, 60);
    bst.insert(1, 70);
    bst.insert(5, 40);
    bst.insert(4, 70);
    bst.print();
    std::cout << "\n" << bst.height() << "\n";
    // BST test end

    //AVLTree test
    std::cout << "AVLTree Test:\n";
    std::cout << "Insert data: (1, 100)、(2, 60)、(3, 70)、(4, 40)、(5, 70)\n";
    AVLTree avl_tree;
    //(1, 100)、(2, 60)、(3, 70)、(4, 40)、(5, 70)
    avl_tree.insert(1, 100);
    avl_tree.insert(2, 60);
    avl_tree.insert(3, 70);
    avl_tree.insert(4, 40);
    avl_tree.insert(5, 70);
    avl_tree.print();
    std::cout << "\n" << avl_tree.height() << "\n";
    // AVL test end
    return 0;
}
#endif

#ifdef BLOCK_2
int main()
{
    AVLTree avl_tree;
    for (int i = 0; i < 10; ++ i) {
        int id = std::uniform_int_distribution(1, 100)(gen);
        std::cout << id << " ";
        avl_tree.insert(id, random_score(gen));
    }
    std::cout << "\n";
    avl_tree.print();
    return 0;
}

#endif