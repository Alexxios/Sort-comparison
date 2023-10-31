#include<fstream>
#include<vector>
#include<functional>
#include<chrono>
#include<iostream>
using namespace std;


template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort(vector<_Tp>& a, size_t lb, size_t rb) {
    if (lb + 1 >= rb) return;

    _Compare cmp;
    _Tp x = a[(lb + rb) >> 1];

    size_t i = lb;
    size_t j = rb - 1;
    while (i <= j) {
        while (cmp(a[i], x)) ++i;
        while (cmp(x, a[j])) --j;
        if (i >= j) break;
        swap(a[i++], a[j--]);
    } 

    quick_sort(a, lb, j);
    quick_sort(a, j, rb);
}



template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort(vector<_Tp>& a) {
    quick_sort(a, 0, a.size());
}

int main() {
    ifstream fin;
    ofstream fout;
    chrono::high_resolution_clock hrc;

    fin.open("input.txt");
    
    size_t N;
    fin >> N;
    
    vector<int> a(N);
    for (int& x: a) fin >> x;
    
    fin.close();
    
    auto start = hrc.now();
    // sort values
    quick_sort(a);
    for (int i = 1; i < N; ++i) cout << boolalpha << (a[i] > a[i - 1]) << ' ';
    cout << endl;
    auto end = hrc.now();

    fout.open("output.txt", ios::app);

    fout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    fout.close();

    return 0;
}