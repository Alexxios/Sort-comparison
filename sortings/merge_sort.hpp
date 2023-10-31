#include<functional>
#include<vector>

using namespace std;

template<typename _Tp, typename _Compare = less<_Tp> >
void merge_sort(vector<_Tp>& a, vector<_Tp>& tmp, size_t lb, size_t rb) {
    if (lb + 1 >= rb) {
        return;
    }

    size_t mid = (lb + rb) >> 1;
    merge_sort(a, tmp, lb, mid);
    merge_sort(a, tmp, mid, rb);

    _Compare cmp;
    size_t i = lb, j = mid, k = 0;
    
    while (i < mid && j < rb) {
        if (cmp(a[i], a[j])) {
            tmp[k++] = a[i];
            ++i;
        } else {
            tmp[k++] = a[j];
            ++j;
        }
    } 
    while (i < mid) {
        tmp[k++] = a[i];
        ++i;
    }
    while (j < rb) {
        tmp[k++] = a[j];
        ++j;
    }

    for (i = 0; i < k; ++i) {
        a[lb + i] = tmp[i];
    }
}

template<typename _Tp, typename _Compare = less<_Tp> >
void merge_sort(vector<_Tp>& a) {
    vector<_Tp> reserve(a.size());
    merge_sort(a, reserve, 0, a.size());
}