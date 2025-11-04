#pragma once
#include "HomeworkRequirement.h"
#include <memory>

class AVLTree : public HomeworkRequirement
{
public:
    AVLTree() = default;
    AVLTree(int balance_factor_bound);
    ~AVLTree();
    void insert(int id, int score) override;
    void print() override;
    int height() override;
    double search_average(int id) override;

private:
    class Node
    {
    public:
        Node(int id) : data(StudentProfile(id)) {}
        Node(int id, Node *parent) : data(StudentProfile(id)), parent(parent) {}
        Node *parent = nullptr;
        std::unique_ptr<Node> left = nullptr, right = nullptr;
        int height = 1;
        StudentProfile data;
    };
    std::unique_ptr<Node> root = nullptr;
    void rotate_upward(Node *node);
    int get_balance_factor(Node *node);
    int get_subtree_height(Node *node);
    const int balance_factor_bound = 1;
};