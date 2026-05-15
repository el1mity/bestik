#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, v;
    cout << "Введите количество вершин: "; cin >> n;
    vector<vector<int>> Gr(n);
    cout << "Введите количество рёбер: "; cin >> m;
    cout << "Введите рёбра: ";
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x >= n || y >= n) continue;
        Gr[x].push_back(y);
        Gr[y].push_back(x);
    }
    for (int i = 0; i < n; i++) {
        sort(Gr[i].begin(), Gr[i].end());           // сначала сортируем
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());  // затем удаляем дубликаты
    }
    cout << "Список смежности: " << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < Gr[i].size(); j++) cout << Gr[i][j] << " ";
        cout << endl;
    }
    cout << "Введите номер вершины: "; cin >> v;
    cout << "Количество вершин, смежных с вершиной " << v << ": " << Gr[v].size();
    return 0;
}