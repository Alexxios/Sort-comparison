#include<fstream>
#include<vector>
#include<functional>
#include<chrono>
using namespace std;

template<typename _Tp, typename _Compare = less<_Tp> >
void sift_up(vector<_Tp>& heap, size_t i) {
    _Compare cmp;
    if (i > 1 && cmp(heap[i], heap[i >> 1])) {
        swap(heap[i >> 1], heap[i]);
        sift_up<_Tp, _Compare>(heap, i >> 1);
    }
}


template<typename _Tp, typename _Compare = less<_Tp> >
void sift_down(vector<_Tp>& heap, size_t i) {
    if (i + i >= heap.size()) return;
    _Compare cmp;
    if (i + i + 1 >= heap.size()) {
        if (cmp(heap[i + i], heap[i])) swap(heap[i], heap[i + i]);
        return;
    }
    size_t l = i + i, r = l ^ 1;
    if (cmp(heap[l],heap[r])) {
        if (cmp(heap[l], heap[i])) {
            swap(heap[l], heap[i]);
            sift_down<_Tp, _Compare>(heap, l);
        }
    } else {
        if (cmp(heap[r], heap[i])) {
            swap(heap[r], heap[i]);
            sift_down<_Tp, _Compare>(heap, r);
        }
    }
}

template<typename _Tp, typename _Compare = less<_Tp>>
void add(vector<_Tp>& heap, _Tp x) {
    if (heap.empty()) heap.push_back(x);
    heap.push_back(x);
    sift_up<_Tp, _Compare>(heap, heap.size() - 1);
}

template<typename _Tp, typename _Compare = less<_Tp>>
void pop(vector<_Tp>& heap) {
    if (heap.size() < 2) return;
    swap(heap[1], heap.back());
    heap.pop_back();
    sift_down<_Tp, _Compare>(heap, 1);
}

template<typename _Tp, typename _Compare = less<_Tp>>
void heap_sort(vector<_Tp>& a) {
    vector<_Tp> heap;
    heap.reserve(a.size() + 1);
    for (_Tp& x : a) add<_Tp, _Compare>(heap, x);
    for (_Tp& x : a) x = heap[1], pop<_Tp, _Compare>(heap);
}