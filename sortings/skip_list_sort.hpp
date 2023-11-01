#include <iostream>
#include <vector>
#include <random>
#include <climits>
using namespace std;

class skip_list {
    static const int MAX_LVL = 32;
    constexpr static double p = 0.5;

    mt19937 gen;
    uniform_real_distribution<> coin;

    int rand_lvl() {
        int lvl = 1;
        while (coin(gen) >= p && lvl < MAX_LVL) ++lvl;
        return lvl;
    }

public:
    struct node {
        int key;
        node **next;

        node(int k, int lvl) : key(k) {
            next = new node*[lvl];
            for (int i = 0; i < lvl; ++i) next[i] = nullptr;
        }
    };
    
    node *header;

    skip_list() {
        header = new node(INT_MIN, MAX_LVL);

        random_device rd;
        gen = mt19937(rd());
    }

    void insert(int key) {
        node *current = header;

        node *update[MAX_LVL];
        for (int i = 0; i < MAX_LVL; ++i) update[i] = nullptr;

        for (int i = MAX_LVL - 1; i >= 0; --i) {
            while (current->next[i] != nullptr &&
                current->next[i]->key < key) current = current->next[i];
            
            update[i] = current;
        }

        current = current->next[0];

        int rlvl = rand_lvl();
        node *n = new node(key, rlvl);

        for (int i = 0; i < rlvl; ++i) {
            n->next[i] = update[i]->next[i];
            update[i]->next[i] = n;
        }
    }
};

void skip_list_sort(vector<int>& a) {
    skip_list sl;
    for (auto& x : a) sl.insert(x);

    auto current = sl.header;
    for (size_t i = 0; i < a.size(); ++i) {
        current = current->next[0];
        a[i] = current->key;
    }
}