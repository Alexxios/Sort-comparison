#include<functional>
#include<vector>
using namespace std;

template<typename _Tp, typename _Compare = less<_Tp>>
void insert_sort(vector<_Tp>& a){
    _Compare cmp;
    for (size_t i = 1; i < a.size(); ++i) {
        _Tp x = a[i];
        size_t j = i;

        for (; j > 0 && cmp(x, a[j - 1]); --j) {
            a[j] = a[j - 1];
        }
        a[j] = x; 
    }
}

template<typename _Tp, typename _Compare = less<_Tp>>
void insert_sort_bs(vector<_Tp>& a){
    _Compare cmp;
    for (size_t i = 1; i < a.size(); ++i) {
        _Tp x = a[i];
        size_t l = 0, r = i + 1;

        while (l + 1 < r) {
            size_t m = (l + r) >> 1;
            if (cmp(x, a[m])) r = m;
            else l = m;
        }
        if (!cmp(x, a[l])) ++l;

        for (r = i; r > l; --r) {
            a[r] = a[r - 1];
        }
        a[r] = x;
    }
}