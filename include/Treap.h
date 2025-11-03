#pragma once
#include "HomeworkRequirement.h"
#include <memory>

class Treap : public HomeworkRequirement
{
public:
    Treap() = default;
    ~Treap();
    void insert(int id, int score) override;
    void insert(int id, int score, float priority);
    void print() override;
    int height() override;
    double search_average(int id) override;

private:
    class Node
    {
    public:
        Node(int id, float priority) : data(StudentProfile(id)), priority(priority) {}
        Node(int id, float priority, Node *parent) : data(StudentProfile(id)), priority(priority), parent(parent) {}
        Node *parent = nullptr;
        std::unique_ptr<Node> left = nullptr, right = nullptr;
        float priority = 0.0;
        StudentProfile data;
    };
    std::unique_ptr<Node> root = nullptr;
    void rotate_upward(Node *node);
};