#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, A, B;
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
    cout << "\nВведите начальную вершину A: "; cin >> A;
    cout << "Введите конечную вершину B: "; cin >> B;
    if (A >= n || B >= n) {
        cout << "Ошибка: вершины должны быть от 0 до " << n - 1 << endl;
        return 1;
    }
    // BFS для поиска кратчайшего пути
    vector<bool> visited(n, false);      
    vector<int> parent(n, -1);        // для восстановления пути
    queue<int> q;                      // очередь BFS

    visited[A] = true;
    q.push(A);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == B) {
            break;
        }

        for (int neighbor : Gr[cur]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = cur;  // запоминаем, откуда пришли
                q.push(neighbor);
            }
        }
    }
    if (!visited[B]) {
        cout << "Пути из вершины " << A << " в вершину " << B << " не существует!" << endl;
    }
    else {
        vector<int> path;
        int current = B;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());
        cout << "Кратчайший путь: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
    }
    return 0;
}