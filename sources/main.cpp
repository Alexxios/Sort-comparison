#include<iostream>
#include<vector>
#include<fstream>
#include<random>
#include<chrono>

#include "../sortings/insert_sort.hpp"
#include "../sortings/merge_sort.hpp"

using namespace std;
using namespace std::chrono;


template<typename Func>
struct func_array {
    static Func *const data[];
};

template<typename Func>
Func *const func_array<Func>::data[] = { insert_sort, merge_sort };


int main() {
    size_t testn[] = {5, 10, 15, 20, 30, 45, 60, 80, 100, 200, 300, 500, 1000, 2000, 5000, 7000, 10000, 15000};
    vector<int> a;
    mt19937 gen(time(nullptr));
    high_resolution_clock hrc;

    ofstream fout;
    fout.open("main_part.txt");
    fout << "N;Insert Sort;Merge Sort" << endl;

    // T - number of runs for each array length
    #define T 50

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