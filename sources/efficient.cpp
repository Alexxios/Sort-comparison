#include<iostream>
#include<vector>
#include<fstream>
#include<random>
#include<chrono>

#include "../sortings/merge_sort.hpp"
#include "../sortings/quick_sort.hpp"
#include "../sortings/heap_sort.hpp"
#include "../sortings/skip_list_sort.hpp"

using namespace std;
using namespace std::chrono;


template<typename Func>
struct func_array {
    static Func *const data[];
};

template<typename Func>
Func *const func_array<Func>::data[] = { merge_sort, quick_sort, heap_sort, quick_sort_mod, skip_list_sort };


int main() {
    size_t testn[] = {60, 80, 100, 200, 300, 500, 1000, 2000, 5000, 15000, 30000, 100000, 250000, 500000, 750000, 1000000};
    vector<int> a;
    mt19937 gen(time(nullptr));
    high_resolution_clock hrc;

    ofstream fout;
    fout.open("efficient_comparison.txt");
    fout << "N;Merge Sort;Quick Sort;Heap Sort;Quick Sort Modification;Sort with Skip List" << endl;

    // T - number of runs for each array length
    #define T 10

    for (auto& N : testn) {
        a.resize(N);

        for (size_t run = 0; run != T; ++run) {
            for (auto& x : a) x = gen();

            fout << N;
            for (auto f : func_array<void(vector<int>&)>::data) {
                auto b(a);
                auto start = hrc.now();
                f(b);
                auto stop = hrc.now();

                fout << ';' << fixed << duration<double, milli>(stop - start).count();
            }
            fout << endl;
        }
    }
    #undef T
    
    fout.close();
    return 0;
}