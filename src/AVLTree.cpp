#include "AVLTree.h"
#include <math.h>
#include <format>
#include <iostream>

AVLTree::AVLTree(int balance_factor_bound) : balance_factor_bound(balance_factor_bound) {}

AVLTree::~AVLTree()
{
    std::vector<std::unique_ptr<Node>> buffer;
    buffer.push_back(std::move(root));
    while (!buffer.empty())
    {
        auto node = std::move(buffer.back());
        buffer.pop_back();
        if (node->left)
            buffer.push_back(std::move(node->left));
        if (node->right)
            buffer.push_back(std::move(node->right));
    }
}

void AVLTree::insert(int id, int score)
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
            if (id < cur_id)
                cur_node = cur_node->left.get();
            else
                cur_node = cur_node->right.get();
        }
    }
    if (id < prev_node->data.get_id())
    {
        prev_node->left = std::make_unique<Node>(id, prev_node);
        prev_node->left->data.add_score(score);
    }
    else
    {
        prev_node->right = std::make_unique<Node>(id, prev_node);
        prev_node->right->data.add_score(score);
    }
    while (prev_node != nullptr)
    {
        int balance_factor = get_balance_factor(prev_node);
        if (std::abs(balance_factor) > balance_factor_bound)
        {
            if (cur_node == nullptr)
                continue;

            if (balance_factor > 0)
            {
                if (get_balance_factor(cur_node) < 0)
                    rotate_upward(cur_node->right.get());
                rotate_upward(prev_node->left.get());
            }
            else if (balance_factor < 0)
            {
                if (get_balance_factor(cur_node) > 0)
                    rotate_upward(cur_node->left.get());
                rotate_upward(prev_node->right.get());
            }
        }
        else if (balance_factor == 0)
        {
            return;
        }
        prev_node->height = get_subtree_height(prev_node);
        cur_node = prev_node;
        prev_node = prev_node->parent;
    }
}

void AVLTree::print()
{
    if (root == nullptr)
        return;

    int len = std::format("({:-7d}, {:-6.2f}) ", 1, 1.0).length();
    std::vector<std::pair<Node *, int>> buffer{{root.get(), 0}};
    while (!buffer.empty())
    {
        Node *cur_node = buffer.back().first;
        int depth = buffer.back().second;
        buffer.pop_back();

        if (depth > 0 && cur_node == cur_node->parent->left.get())
        {
            std::cout << "\n";
            for (int i = 0; i < depth; ++i)
            {
                for (int j = 0; j < len; ++j)
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::format("({:-7d}, {:-6.2f}) ", cur_node->data.get_id(), cur_node->data.get_scores_average());

        Node *left = cur_node->left.get(), *right = cur_node->right.get();
        if (left != nullptr)
            buffer.push_back({left, depth + 1});
        if (right != nullptr)
            buffer.push_back({right, depth + 1});
    }
}

int AVLTree::height()
{
    if (root == nullptr)
        return 0;

    return root->height;
}

double AVLTree::search_average(int id)
{
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

void AVLTree::rotate_upward(Node *node)
{
    if (node == nullptr || node->parent == nullptr)
        return;

    Node *grandparent = node->parent->parent;
    std::unique_ptr<Node> parent;
    bool is_left = false;
    if (node == node->parent->left.get())
        is_left = true;

    if (grandparent != nullptr)
    {
        if (node->parent == grandparent->left.get())
        {
            parent = std::move(grandparent->left);
            if (is_left)
            {
                grandparent->left = std::move(parent->left);
                if (grandparent->left != nullptr)
                    grandparent->left->parent = grandparent;
                parent->left = std::move(node->right);
                if (parent->left != nullptr)
                    parent->left->parent = parent.get();
                parent->height = get_subtree_height(parent.get());
                node->right = std::move(parent);
                if (node->right != nullptr)
                    node->right->parent = node;
            }
            else
            {
                grandparent->left = std::move(parent->right);
                if (grandparent->left != nullptr)
                    grandparent->left->parent = grandparent;
                parent->right = std::move(node->left);
                if (parent->right != nullptr)
                    parent->right->parent = parent.get();
                parent->height = get_subtree_height(parent.get());
                node->left = std::move(parent);
                if (node->left != nullptr)
                    node->left->parent = node;
            }
        }
        else
        {
            parent = std::move(grandparent->right);
            if (is_left)
            {
                grandparent->right = std::move(parent->left);
                if (grandparent->right != nullptr)
                    grandparent->right->parent = grandparent;
                parent->left = std::move(node->right);
                if (parent->left != nullptr)
                    parent->left->parent = parent.get();
                parent->height = get_subtree_height(parent.get());
                node->right = std::move(parent);
                if (node->right != nullptr)
                    node->right->parent = node;
            }
            else
            {
                grandparent->right = std::move(parent->right);
                if (grandparent->right != nullptr)
                    grandparent->right->parent = grandparent;
                parent->right = std::move(node->left);
                if (parent->right != nullptr)
                    parent->right->parent = parent.get();
                parent->height = get_subtree_height(parent.get());
                node->left = std::move(parent);
                if (node->left != nullptr)
                    node->left->parent = node;
            }
        }
        grandparent->height = get_subtree_height(grandparent);
    }
    else
    {
        parent = std::move(root);
        if (is_left)
        {
            root = std::move(parent->left);
            root->parent = nullptr;
            parent->left = std::move(node->right);
            if (parent->left != nullptr)
                parent->left->parent = parent.get();
            parent->height = get_subtree_height(parent.get());
            node->right = std::move(parent);
            if (node->right != nullptr)
                node->right->parent = node;
        }
        else
        {
            root = std::move(parent->right);
            root->parent = nullptr;
            parent->right = std::move(node->left);
            if (parent->right != nullptr)
                parent->right->parent = parent.get();
            parent->height = get_subtree_height(parent.get());
            node->left = std::move(parent);
            if (node->left != nullptr)
                node->left->parent = node;
        }
    }
    node->height = get_subtree_height(node);
}

int AVLTree::get_balance_factor(Node *node)
{
    int left_height = node->left == nullptr ? 0 : node->left->height;
    int right_height = node->right == nullptr ? 0 : node->right->height;
    return (left_height - right_height);
}

int AVLTree::get_subtree_height(Node *node)
{
    int left_height = node->left == nullptr ? 0 : node->left->height;
    int right_height = node->right == nullptr ? 0 : node->right->height;
    return std::max(left_height, right_height) + 1;
}
