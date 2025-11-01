#pragma once
#include "HomeworkRequirement.h"
#include <memory>

class BST : public HomeworkRequirement {
public:
    BST();
    BST(int id, int score);
    void insert(int id, int score) override;
    void print() override;
    int height() override;
    double search_average(int id) override;
private:
    class Node {
    public:
        Node(int id) : data(StudentProfile(id)), parent(nullptr), left(nullptr), right(nullptr) {}
        Node(int id, Node *parent) : data(StudentProfile(id)), parent(parent), left(nullptr), right(nullptr) {}
        Node *parent;
        std::unique_ptr<Node> left, right;
        StudentProfile data;
    };
    std::unique_ptr<Node> root;
};