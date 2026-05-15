#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

void dfs(int v, vector<vector<int>>& Gr, vector<bool>& visited) {
    visited[v] = true;
    for (int neighbor : Gr[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, Gr, visited);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, x;
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
    // запускаем DFS из вершины 0
    vector<bool> visited(n, false);
    dfs(0, Gr, visited);
    bool connected = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            connected = false;
            break;
        }
    }
    if (connected)
        cout << "\nГраф связный";
    else
        cout << "\nГраф несвязный";
    return 0;
}