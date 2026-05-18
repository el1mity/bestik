#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

// Пузырьковая сортировка (bubble_sort)
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Быстрая сортировка (quick_sort) — вспомогательная функция
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_rec(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_rec(arr, low, pi - 1);
        quick_sort_rec(arr, pi + 1, high);
    }
}

void quick_sort(vector<int>& arr) {
    quick_sort_rec(arr, 0, arr.size() - 1);
}

// Сортировка слиянием (merge_sort)
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort_rec(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_rec(arr, left, mid);
        merge_sort_rec(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort(vector<int>& arr) {
    merge_sort_rec(arr, 0, arr.size() - 1);
}

// Замер времени
template<typename Func>
double measure_time(Func sort_func, vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    sort_func(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    return duration.count();
}

int main() {
    vector<int> sizes = {1000, 5000, 10000, 50000};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);
    
    cout << "Сравнение алгоритмов сортировки на C++" << endl;
    cout << "============================================================" << endl;
    cout << "   Размер   | Quick (мс) | Merge (мс) | Bubble (мс)" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    for (int size : sizes) {
        vector<int> data(size);
        for (int i = 0; i < size; ++i) data[i] = dist(gen);
        
        double t_quick = measure_time(quick_sort, data);
        double t_merge = measure_time(merge_sort, data);
        
        if (size <= 5000) {
            double t_bubble = measure_time(bubble_sort, data);
            printf("%8d | %10.2f | %10.2f | %10.2f\n", size, t_quick, t_merge, t_bubble);
        } else {
            printf("%8d | %10.2f | %10.2f | %10s\n", size, t_quick, t_merge, "N/A");
        }
    }
    
    return 0;
}