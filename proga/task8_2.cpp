#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, A, B;
    cout << "Введите количество вершин: "; cin >> n;
    vector<vector<int>> Gr(n);
    cout << "Введите количество рёбер: "; cin >> m;
    cout << "Введите существующие рёбра: ";
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x >= n || y >= n) continue;
        Gr[x].push_back(y);
        Gr[y].push_back(x);
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

    cout << "\nВведите A и B: ";
    cin >> A >> B;
    // проверяем, существует ли уже такое ребро
    if (find(Gr[A].begin(), Gr[A].end(), B) != Gr[A].end()) {
        cout << "Ребро " << A << " - " << B << " уже существует!";
    }
    else {
        Gr[A].push_back(B);
        Gr[B].push_back(A);
        cout << "Ребро " << A << " - " << B << " успешно добавлено!";
    }
    return 0;
}