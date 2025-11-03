#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <nlohmann/json.hpp>
#include "BST.h"
#include "AVLTree.h"
#include "Treap.h"
#include "SkipList.h"

#define BLOCK_3

using json = nlohmann::ordered_json;
const std::pair<int, int> k_range(10, 20); // Include end
const int NUMBER_OF_EXPERIMENTS = 3;
const int EXPERIMENT_ROUNDS = 10;
const int NUMBER_OF_SEARCHS = 1 << 20;
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

// Homework Test
#ifdef BLOCK_1
int main() {
    // BST test
    std::cout << "BST Test :\n";
    std::cout << "Insert data : (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)\n";
    BST bst;
    // (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)
    bst.insert(3, 100);
    bst.insert(2, 60);
    bst.insert(1, 70);
    bst.insert(5, 40);
    bst.insert(4, 70);
    bst.print();
    std::cout << "\n" << bst.height() << "\n";
    for (int i = 0; i <= 5; ++i) 
    {
        std::cout << "Id " << i << " average " << bst.search_average(i) << "\n";
    }
    // BST test end
    std::cout << "\n";
    // AVLTree test
    std::cout << "AVLTree Test:\n";
    std::cout << "Insert data: (1, 100)、(2, 60)、(3, 70)、(4, 40)、(5, 70)\n";
    AVLTree avl_tree;
    //(1, 100)、(2, 60)、(3, 70)、(4, 40)、(5, 70)
    avl_tree.insert(1, 100);
    avl_tree.insert(2, 60);
    avl_tree.insert(3, 70);
    avl_tree.insert(4, 40);
    avl_tree.insert(5, 70);
    avl_tree.print();
    std::cout << "\n" << avl_tree.height() << "\n";
    for (int i = 0; i <= 5; ++i)
    {
        std::cout << "Id " << i << " average " << avl_tree.search_average(i) << "\n";
    }
    // AVL test end
    std::cout << "\n";
    // Treap test
    std::cout << "Treap Test:\n";
    std::cout << "Insert data: (3,100)[0.9]、(2,60)[0.5]、(1,70)[0.3]、(5,60)[0.2]、(4,80)[0.1]\n";
    Treap treap;
    //(3,100)[0.9]、(2,60)[0.5]、(1,70)[0.3]、(5,60)[0.2]、(4,80)[0.1]
    treap.insert(3, 100, 0.9);
    treap.insert(2, 60, 0.5);
    treap.insert(1, 70, 0.3);
    treap.insert(5, 60, 0.2);
    treap.insert(4, 80, 0.1);
    treap.print();
    std::cout << "\n" << treap.height() << "\n";
    for (int i = 0; i <= 5; ++i)
    {
        std::cout << "Id " << i << " average " << treap.search_average(i) << "\n";
    }
    // Treap test end
    std::cout << "\n";
    // SkipList test
    std::cout << "SkipList Test:\n";
    std::cout << "Insert data: (1, 100)[HHT]、(2,60)[T]、(3, 70)[HT]、(4,80)[HHHT]、(5,60)[T]、(6,80)[T]、(7,90)[HHT]\n";
    SkipList skip_list;
    // (1, 100)[HHT]、(2,60)[T]、(3, 70)[HT]、(4,80)[HHHT]、(5,60)[T]、(6,80)[T]、(7,90)[HHT]
    skip_list.insert(1, 100, 2);
    skip_list.insert(2, 60, 0);
    skip_list.insert(3, 70, 1);
    skip_list.insert(4, 80, 3);
    skip_list.insert(5, 60, 0);
    skip_list.insert(6, 80, 0);
    skip_list.insert(7, 90, 2);
    skip_list.print();
    std::cout << "\n" << skip_list.height() << "\n";
    for (int i = 0; i <= 5; ++i)
    {
        std::cout << "Id " << i << " average " << skip_list.search_average(i) << "\n";
    }
    // SkipList test end
    return 0;
}
#endif

// Test
#ifdef BLOCK_2
int main()
{
    SkipList data_structure(0.75);
    for (int i = 0; i < 1000; ++i)
    {
        int id = std::uniform_int_distribution(1, 10)(gen);
        //std::cout << id << " ";
        data_structure.insert(id, random_score(gen));
    }
    std::cout << "\n";
    data_structure.print();
    std::cout << "\n" << data_structure.height();
    return 0;
}
#endif

// Homework expiriment
#ifdef BLOCK_3
json result_json;
const std::string filename = "result_k_" + std::to_string(k_range.first) + "_" + std::to_string(k_range.second) + ".json";
const std::filesystem::path file_path = std::filesystem::current_path() / filename;
int main()
{
    auto experiment_start_time = std::chrono::high_resolution_clock::now();
    std::cout << "\033[2J" << "\033[s";
    // Load experiment result
    if (!std::filesystem::exists(file_path))
    {
        std::ofstream ofs(file_path);
        ofs.close();
    }
    std::ifstream ifs(file_path);
    try
    {
        result_json = nlohmann::json::parse(ifs);
    }
    catch (...)
    {
    }
    ifs.close();

    std::vector<std::pair<int, int>> data;
    std::vector<int> search_ids;
    search_ids.reserve(NUMBER_OF_SEARCHS);

    for (int k = k_range.first; k <= k_range.second; ++k)
    {
        size_t n = 1 << k;
        for (int i = 0; i < EXPERIMENT_ROUNDS; ++i)
        {
            auto round_start_time = std::chrono::high_resolution_clock::now();

            std::cout << "Testing : k = " << k << ", Round : " << i + 1 << "\n";
            std::vector<std::pair<HomeworkRequirement *, std::string>> data_structures = {
                {new BST(), "BST"},
                {new AVLTree(), "AVLTree"},
                {new Treap(), "Treap"},
                {new SkipList(), "SkipList"},
                {new AVLTree(3), "AVLTree(3)"},
                {new SkipList(0.25), "SkipList(0.25)"},
                {new SkipList(0.75), "SkipList(0.75)"}
            };

            generate_data(data, n);
            generate_id(search_ids, NUMBER_OF_SEARCHS);

            std::cout << "Test info :\n";
            for (int data_structure_type = 0; data_structure_type < data_structures.size(); ++data_structure_type)
            {
                const std::vector<std::string> keys = {"k=" + std::to_string(k), "round=" + std::to_string(i + 1), data_structures[data_structure_type].second};
                json *tmp_json = &result_json;
                bool contained_object = true;
                for (const auto &key : keys)
                {
                    if (!tmp_json->contains(key) || !(*tmp_json)[key].is_object())
                    {
                        contained_object = false;
                        break;
                    }
                    tmp_json = &((*tmp_json)[key]);
                }
                if (contained_object)
                    continue;

                std::cout << data_structures[data_structure_type].second << ":\n";
                json part_result_json;
                for (int experiment_number = 0; experiment_number < NUMBER_OF_EXPERIMENTS; ++experiment_number)
                {
                    std::cout << "\tExperiment " << experiment_number + 1;
                    if (experiment_number == 0)
                    {
                        auto start_time = std::chrono::high_resolution_clock::now();
                        for (const auto &d : data)
                            data_structures[data_structure_type].first->insert(d.first, d.second);
                        auto end_time = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                        std::cout << " time : " << duration.count() << "(µs)\n";
                        if (data_structure_type >= 4)
                            continue;
                        part_result_json[std::to_string(experiment_number + 1)] = duration.count();
                    }
                    else if (experiment_number == 1)
                    {
                        auto start_time = std::chrono::high_resolution_clock::now();
                        for (const auto &search_id : search_ids)
                            data_structures[data_structure_type].first->search_average(search_id);
                        auto end_time = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
                        std::cout << " time : " << duration.count() << "(µs)\n";
                        if (data_structure_type >= 4)
                            continue;
                        part_result_json[std::to_string(experiment_number + 1)] = duration.count();
                    }
                    else if (experiment_number == 2)
                    {
                        std::cout << " height : " << data_structures[data_structure_type].first->height() << "\n";
                        part_result_json[std::to_string(experiment_number + 1)] = data_structures[data_structure_type].first->height();
                    }
                }
                // Save experiment result
                result_json["k=" + std::to_string(k)]["round=" + std::to_string(i + 1)][data_structures[data_structure_type].second] = part_result_json;
                std::ofstream ofs(file_path);
                ofs << result_json.dump(4);
                ofs.close();

                delete data_structures[data_structure_type].first;
            }

            auto round_end_time = std::chrono::high_resolution_clock::now();
            auto round_duration = std::chrono::duration_cast<std::chrono::milliseconds>(round_end_time - round_start_time);

            std::cout << "Total time : " << round_duration.count() << "(ms)\n";
        }
    }

    auto experiment_end_time = std::chrono::high_resolution_clock::now();
    auto experiment_duration = std::chrono::duration_cast<std::chrono::milliseconds>(experiment_end_time - experiment_start_time);
    std::cout << "\nExperiment total time : " << experiment_duration.count() << "(ms)";

    return 0;
}
#endif