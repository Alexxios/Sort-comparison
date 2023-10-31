#include<iostream>
#include<fstream>
#include<random>
#include<chrono>

#include "sortings/merge_sort.hpp"

using namespace std;
using namespace std::chrono;


template<typename Func>
struct func_array {
  static Func *const data[];
};


template<typename Func>
Func *const func_array<Func>::data[] = { merge_sort };

int main() {
    //ofstream fout;

    size_t testn[] = {4, 5, 15, 100, 4000, 50000};
    vector<int> a;
    mt19937 gen(time(nullptr));
    high_resolution_clock hrc;


    //fout.open("output.txt");

    for (auto& N : testn) {
        a.resize(N);
        for (auto& x : a) x = gen();

        auto start = hrc.now();
        func_array<void(std::vector<int>&)>::data[0](a);
        auto stop = hrc.now();

        bool ok = true;
        for (int i = 1; i < N; ++i) ok &= (a[i - 1] <= a[i]);
        cout << boolalpha << ok << ' ';

        cout << duration_cast<microseconds>(stop - start).count() << endl;
      
    }
    //fout.close();
    return 0;
}