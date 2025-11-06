#pragma once
#include "HomeworkRequirement.h"
#include <memory>

class BST : public HomeworkRequirement
{
public:
    BST() = default;
    ~BST();
    void insert(int id, int score) override;
    void print() override;
    int height() override;
    double search_average(int id) override;

private:
    class Node
    {
    public:
        Node(int id) : index(id), data(StudentProfile(id)){}
        Node(int id, Node *parent) : index(id), data(StudentProfile(id)), parent(parent){}
        Node *parent = nullptr;
        std::unique_ptr<Node> left = nullptr, right = nullptr;
        const int index;
        StudentProfile data;
    };
    std::unique_ptr<Node> root = nullptr;
};