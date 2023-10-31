#include<iostream>
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
    size_t testn[] = {5, 10, 15, 20, 30, 45, 60, 100, 500, 1000, 2000, 5000, 15000, 25000};
    vector<int> a;
    mt19937 gen(time(nullptr));
    high_resolution_clock hrc;

    ofstream fout;
    fout.open("output.txt");

    // T - number of runs for each array length
    #define T 20

    for (auto& N : testn) {
        a.resize(N);

        double duration_sum[] = {0, 0};
        for (size_t run = 0; run != T; ++run) {
            for (auto& x : a) x = gen();

            size_t i = 0;
            for (auto f : func_array<void(vector<int>&)>::data) {
                auto start = hrc.now();
                f(a);
                auto stop = hrc.now();

                duration_sum[i++] += duration<double, milli>(stop - start).count();
            }
        }
        fout << N;
        for (double d : duration_sum) fout << ',' << fixed << d / N;
        fout << endl;
    }
    #undef T
    
    fout.close();
    return 0;
}