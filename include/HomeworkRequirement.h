#pragma once
#include <vector>

class StudentProfile {
public:
    StudentProfile(int id) : id(id) {}
    void add_score(int score) { scores.push_back(score); }
    double get_scores_average() {
        if (scores.size() == 0)
            return -1;
        int sum = 0;
        for (const auto& score : scores)
            sum += score;
        return static_cast<double>(sum) / scores.size();
    }
    const int get_id() const {
        return id;
    };

private:
    int id;
    std::vector<int> scores;
};

class HomeworkRequirement {
    virtual void insert(int id, int score) = 0;
    virtual void print() = 0;
    virtual int height() = 0;
    virtual double search_average(int id) = 0;
};