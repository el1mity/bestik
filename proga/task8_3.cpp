#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m;
    cout << "Введите количество вершин: "; cin >> n;
    vector<vector<int>> Gr(n);
    cout << "Введите количество дуг: "; cin >> m;
    cout << "Введите существующие дуги: ";
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x >= n || y >= n) continue;
        Gr[x].push_back(y);
    }
    // удаляем дубликаты
    for (int i = 0; i < n; i++) {
        sort(Gr[i].begin(), Gr[i].end());
        Gr[i].erase(unique(Gr[i].begin(), Gr[i].end()), Gr[i].end());
    }
    cout << "Список смежности: " << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < Gr[i].size(); j++) cout << Gr[i][j] << " ";
        cout << endl;
    }
    cout << "\nРезультат: " << endl;
    for (int i = 0; i < n; i++)
        cout << "Полустепень исхода (количество исходящих дуг) вершины " << i << " = " << Gr[i].size() << endl;
    return 0;
}