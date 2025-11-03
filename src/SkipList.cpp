#include "SkipList.h"
#include <iostream>
#include <random>
#include <limits>
#include <format>

SkipList::SkipList()
{
    head = new Node(std::numeric_limits<int>::min());
    head->next.push_back(nullptr);
}

SkipList::SkipList(float probability) : probability(probability)
{
    head = new Node(std::numeric_limits<int>::min());
    head->next.push_back(nullptr);
}

SkipList::~SkipList()
{
    Node *cur_node = head;
    while (cur_node != nullptr) {
        Node *tmp = cur_node;
        cur_node = cur_node->next[0];
        delete tmp;
    }
}

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> random_priority(0, 1);

void SkipList::insert(int id, int score)
{
    int insert_level = 0;
    while (random_priority(gen) < probability)
        ++insert_level;
    insert(id, score, insert_level);
}

void SkipList::insert(int id, int score, int insert_level)
{
    std::vector<Node *> corner;
    int level = static_cast<int>(head->next.size()) - 1;
    Node *prev_node = head, *cur_node = head->next[level];
    while (true)
    {
        if (cur_node == nullptr || id < cur_node->data.get_id())
        {
            if (prev_node == nullptr)
                return;
            corner.push_back(prev_node);
            --level;
            if (level < 0) {
                level = 0;
                break;
            }
            cur_node = prev_node->next[level];
            continue;
        }
        else if (id == cur_node->data.get_id())
        {
            cur_node->data.add_score(score);
            return;
        }
        else
        {
            prev_node = cur_node;
            cur_node = cur_node->next[level];
        }
    }
    Node *new_node = new Node(id);
    new_node->data.add_score(score);
    while (level <= insert_level)
    {
        if (!corner.empty())
        {
            Node *prev_node = corner.back();
            corner.pop_back();
            new_node->next.push_back(prev_node->next[level]);
            prev_node->next[level] = new_node;
            ++level;
        }
        else
        {
            new_node->next.push_back(nullptr);
            head->next.push_back(new_node);
            ++level;
        }
    }
}

void SkipList::print()
{
    int max_level = static_cast<int>(head->next.size()) - 1;
    int len = std::format("({:-7d}, {:-6.2f}) ", 1, 1.0).length();
    for (int level = max_level; level >= 0; --level)
    {
        Node *cur_node = head->next[0];
        while(cur_node != nullptr)
        {
            if (static_cast<int>(cur_node->next.size()) - 1 >= level) {
                std::cout << std::format("({:-7d}, {:-6.2f}) ", cur_node->data.get_id(), cur_node->data.get_scores_average());
            }
            else
            {
                for (int j = 0; j < len; ++j)
                {
                    std::cout << " ";
                }
            }
            cur_node = cur_node->next[0];
        }
        if (level > 0)
            std::cout << "\n";
    }
}

int SkipList::height()
{
    return static_cast<int>(head->next.size()) - 1;
}

double SkipList::search_average(int id)
{
    int level = static_cast<int>(head->next.size()) - 1;
    Node *prev_node = nullptr, *cur_node = head;
    while (true)
    {
        if (cur_node == nullptr || id < cur_node->data.get_id())
        {
            if (prev_node == nullptr)
                return -1;
            --level;
            if (level < 0)
                return -1;
            cur_node = prev_node->next[level];
            continue;
        }
        else if (id == cur_node->data.get_id())
        {
            return cur_node->data.get_scores_average();
        }
        else
        {
            prev_node = cur_node;
            cur_node = cur_node->next[level];
        }
    }
}
