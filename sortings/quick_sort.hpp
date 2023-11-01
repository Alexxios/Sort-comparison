#include<vector>
#include<functional>
#include<random>
#include<iostream>

using namespace std;

template<typename _Tp, typename _Compare = less<_Tp> >
size_t partition(vector<_Tp>& a, size_t lb, size_t rb, _Tp x) {
    _Compare cmp;

    size_t i = lb;
    size_t j = rb - 1;
    while (i <= j) {
        while (cmp(a[i], x)) ++i;
        while (cmp(x, a[j])) --j;
        if (i >= j) break;
        swap(a[i++], a[j--]);
    }
    return i;
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort(vector<_Tp>& a, size_t lb, size_t rb) {
    if (lb + 1 >= rb) return;

    _Tp x = a[(lb + rb) >> 1];

    size_t p = partition<_Tp, _Compare>(a, lb, rb, x);

    quick_sort(a, lb, p);
    quick_sort(a, p, rb);
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort(vector<_Tp>& a) {
    quick_sort<_Tp, _Compare>(a, 0, a.size());
}

template<typename _Tp, typename _Compare = less<_Tp> >
_Tp median5(_Tp& A, _Tp& B, _Tp& C, _Tp& D, _Tp& E) {
    _Compare cmp;
    
    if (!cmp(A, B)) swap(A, B);
    // now A <= B

    if (!cmp(C, D)) swap(C, D);
    // now A <= B && C <= D

    if (!cmp(A, C)) {
        swap(B, D);
        swap(A, C);
    }
    // now A <= C <= D && A <= B

    if (cmp(C, E)) {
        if (!cmp(D, E)) swap(D, E);
    } else {
        swap(C, E);
        swap(D, E);
        if (!cmp(A, C)) swap(A, C);
    }
    // now A <= C <= D <= E && A <= B

    if (cmp(B, D)) {
        if (!cmp(B, C)) swap(B, C);
    } else {
        swap(B, D);
        swap(B, C);
        if (!cmp(D, E)) swap(D, E);
    }
    // now A <= B <= C <= D <= E
    return C;
}


template<typename _Tp, typename _Compare = less<_Tp> >
_Tp order_stat(vector<_Tp>& a, size_t lb, size_t rb, size_t k) {
    size_t n = rb - lb;
    size_t i = 0;
    vector<_Tp> median((n + 4) / 5);

    for (; 5 * i != n - n % 5; ++i) {
            median[i] = median5<_Tp, _Compare>(
                a[lb + 5 * i],
                a[lb + 5 * i + 1],
                a[lb + 5 * i + 2],
                a[lb + 5 * i + 3],
                a[lb + 5 * i + 4]);
    }
    if (n % 5) {
        sort(a.begin() + lb + 5 * i, a.begin() + rb);
        median[n / 5] = a[lb + 5 * i + (n % 5 / 2)];
        ++i;
    } 

    _Tp x = (i == 1) ? median[i - 1] : order_stat<_Tp, _Compare>(median, 0, i, i / 2);

    size_t p = partition<_Tp, _Compare>(a, lb, rb, x);

    if (p == lb + k) return a[p];
    if (p > lb + k) return order_stat<_Tp, _Compare>(a, lb, p, k);
    else return order_stat<_Tp, _Compare>(a, p + 1, rb, lb + k - p - 1);
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort_mod(vector<_Tp>& a, size_t lb, size_t rb) {
    if (lb + 1 >= rb) return;

    _Tp x = order_stat<_Tp, _Compare>(a, lb, rb, (rb - lb) >> 1);
    size_t p = partition<_Tp, _Compare>(a, lb, rb, x);

    quick_sort_mod<_Tp, _Compare>(a, lb, p);
    quick_sort_mod<_Tp, _Compare>(a, p, rb);
}

template<typename _Tp, typename _Compare = less<_Tp> >
void quick_sort_mod(vector<_Tp>& a) {
    quick_sort_mod<_Tp, _Compare>(a, 0, a.size());
}