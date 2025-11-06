#pragma once
#include "HomeworkRequirement.h"
#include <vector>
#include <memory>

class SkipList : public HomeworkRequirement
{
public:
    SkipList();
    SkipList(float probaility);
    ~SkipList();
    void insert(int id, int score) override;
    void insert(int id, int score, int level);
    void print() override;
    int height() override;
    double search_average(int id) override;

private:
    class Node
    {
    public:
        Node(int id) : index(id), data(StudentProfile(id)){}
        std::vector<Node *> next;
        const int index;
        StudentProfile data;
    };
    Node *head;
    const float probability = 0.5;
};