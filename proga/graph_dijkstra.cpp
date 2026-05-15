#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, start;
    cout << "Введите количество вершин: "; cin >> n;
    cout << "Введите количество рёбер: "; cin >> m;
    // gr[i] хранит пары (сосед, вес)
    vector<vector<pair<int, int>>> gr(n);

    cout << "Введите рёбра и вес: ";
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        if (x >= n || y >= n) continue;
        gr[x].push_back({ y, w });
        gr[y].push_back({ x, w });
    }
    cout << "Введите стартовую вершину: "; cin >> start;

    // Алгоритм Дейкстры
    vector<int> dist(n, INT_MAX);   // кратчайшие расстояния
    vector<int> parent(n, -1);      // для восстановления пути
    vector<bool> visited(n, false); // посещённые вершины
    dist[start] = 0;

    for (int iter = 0; iter < n; iter++) {
        int x = -1;
        int minDist = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                x = i;
            }
        }
        if (x == -1) break;
        visited[x] = true;

        for (auto edge : gr[x]) {
            int y = edge.first;
            int weight = edge.second;

            if (!visited[y] && dist[x] + weight < dist[y]) {
                dist[y] = dist[x] + weight;
                parent[y] = x;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == start) continue;
        cout << "\nВершина " << i << ": ";
        if (dist[i] == INT_MAX) {
            cout << "недостижима" << endl;
            continue;
        }
        cout << "расстояние = " << dist[i] << endl;

        vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        cout << "Путь: ";
        for (int j = path.size() - 1; j >= 0; j--) {
            cout << path[j];
            if (j > 0) cout << " -> ";
        }
    }
    return 0;
}