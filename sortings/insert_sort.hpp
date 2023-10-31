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