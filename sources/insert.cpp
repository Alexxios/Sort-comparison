#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<random>
#include<chrono>

#include "../sortings/insert_sort.hpp"

using namespace std;
using namespace std::chrono;


template<typename Func>
struct func_array {
    static Func *const data[];
};

template<typename Func>
Func *const func_array<Func>::data[] = { insert_sort, insert_sort_bs };

string gen_string(size_t M, mt19937& gen) {
    string s;
    s.reserve(M);
    for (size_t i = 0; i != M; ++i) s.push_back('a' + gen() % 26);
    return s;
}

int main() {
    size_t testn[] = {3, 4, 5};
    size_t testm[] = {1, 2, 3};
    vector<string> a;
    mt19937 gen(time(nullptr));
    high_resolution_clock hrc;

    ofstream fout;
    fout.open("insert_comparison.txt");
    fout << "N;M;Insert Sort;Insert Sort with Binary Search" << endl;

    // T - number of runs for each array length
    #define T 1

    for (auto& N : testn) {
        a.resize(N);
        for (auto& M : testm) {

            for (size_t run = 0; run != T; ++run) {
                for (auto& s : a) s = gen_string(M, gen);

                fout << N;
                for (auto f : func_array<void(vector<string>&)>::data) {
                    auto b(a);
                    auto start = hrc.now();
                    f(b);
                    auto stop = hrc.now();
                    
                    for (auto& s : b) cout << s << ' ';
                    cout << endl;

                    fout << ';' << fixed << duration<double, milli>(stop - start).count();
                }
                fout << endl;
            }
        }
    }
    #undef T
    
    fout.close();
    return 0;
}