#include<vector>
#include<functional>
#include<random>
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

    quick_sort(a, lb, i);
    quick_sort(a, i, rb);
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort(vector<_Tp>& a) {
    quick_sort(a, 0, a.size());
}

template<typename _Tp, typename _Compare = less<_Tp> >
void sort5(vector<_Tp>& a, size_t pos) {
    _Compare cmp;
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort_mod(vector<_Tp>& a, vector<_Tp>& tmp, size_t lb, size_t rb) {
    

}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort_mod(vector<_Tp>& a) {
    vector<_Tp> b(a);
    quick_sort_mod(a, b, 0, a.size());
}

