#include "BST.h"
#include <format>
#include <iostream>

BST::BST() : root(nullptr) {}
BST::BST(int id, int score)
{
}

void BST::insert(int id, int score)
{
    if (root == nullptr)
    {
        root = std::make_unique<Node>(id);
        root->data.add_score(score);
        return;
    }

    Node *prev_node = nullptr, *cur_node = root.get();
    while (cur_node != nullptr)
    {
        int cur_id = cur_node->data.get_id();
        if (cur_id == id)
        {
            cur_node->data.add_score(score);
            return;
        }
        else
        {
            prev_node = cur_node;
            if (id > cur_id)
                cur_node = cur_node->right.get();
            else
                cur_node = cur_node->left.get();
        }
    }
    if (prev_node->data.get_id() < id)
    {
        prev_node->right = std::make_unique<Node>(id, prev_node);
        prev_node->right->data.add_score(score);
    }
    else
    {
        prev_node->left = std::make_unique<Node>(id, prev_node);
        prev_node->left->data.add_score(score);
    }
}

void BST::print()
{
    std::vector<std::pair<Node *, int>> buffer{{root.get(), 0}};
    while (!buffer.empty())
    {
        Node *cur_node = buffer.back().first;
        int depth = buffer.back().second;
        buffer.pop_back();

        if (depth > 0 && cur_node == cur_node->parent->left.get()){
            std::cout << "\n";
            for (int i = 0; i < depth; ++i)
                std::cout << "        ";
        }
        std::cout << std::format("{:07d} ", cur_node->data.get_id());

        Node *left = cur_node->left.get(), *right = cur_node->right.get();
        if (left != nullptr)
            buffer.push_back({ left, depth + 1});
        if (right != nullptr) 
            buffer.push_back({right, depth + 1});
    }
}

int BST::height() {
    int max_depth = 0;
    std::vector<std::pair<Node *, int>> buffer{{root.get(), 0}};
    while (!buffer.empty())
    {
        Node *cur_node = buffer.back().first;
        int depth = buffer.back().second;
        max_depth = std::max(max_depth, depth);
        buffer.pop_back();
        Node *left = cur_node->left.get(), *right = cur_node->right.get();
        if (left != nullptr)
            buffer.push_back({left, depth + 1});
        if (right != nullptr)
            buffer.push_back({right, depth + 1});
    }
    return max_depth;
}

double BST::search_average(int id) {
    Node *cur_node = root.get();
    while (cur_node != nullptr)
    {
        int cur_id = cur_node->data.get_id();
        if (cur_id == id)
        {
            return cur_node->data.get_scores_average();
        }
        else
        {
            if (id < cur_id)
                cur_node = cur_node->left.get();
            else
                cur_node = cur_node->right.get();
        }
    }
    return -1.0;
}