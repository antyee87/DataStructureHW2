#define BLOCK_1

#include <iostream>
#include <random>
#include "BST.h"

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
    std::cout << "Insert data : (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70) \n";
    BST bst;
    // (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)
    bst.insert(3, 100);
    bst.insert(2, 60);
    bst.insert(1, 70);
    bst.insert(5, 40);
    bst.insert(4, 70);
    bst.print();
    std::cout << "\n" << bst.height();
    // BST test end

    return 0;
}
#endif