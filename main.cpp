#include<iostream>
#include<fstream>
#include<random>
#include<chrono>
#include<cstdlib>

using namespace std;

int main() {
    ofstream fout;
    ofstream fin;

    size_t testn[] = {3, 4, 5};
    mt19937 gen(time(nullptr));

    fin.open("output.txt");
    fin.close();

    for (auto& N : testn) {
        fout.open("input.txt");
        fout << N << endl;
        
        for (size_t i = 0; i != N; ++i) {
            int x = gen();
            fout << x << ' ';
        }
        fout << endl;
        
        system("./heap_sort");
        fout.close();
    }
    return 0;
}