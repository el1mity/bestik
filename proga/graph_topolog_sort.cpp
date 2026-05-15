#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<bool> used;
vector<int> order;
vector<vector<int>> gr;

// обход в глубину 
void dfs(int x) {
    used[x] = true;
    for (int i = 0; i < gr[x].size(); i++) {
        if (!used[gr[x][i]]) {
            dfs(gr[x][i]);
        }
    }
    order.push_back(x);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m;
    cout << "Введите количество вершин: "; cin >> n;
    cout << "Введите количество дуг: "; cin >> m;
    gr.resize(n);

    cout << "Введите дуги:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x >= n || y >= n) continue;
        gr[x].push_back(y);
    }

    // Обход для всех непосещённых вершин 
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());

    // Дополнительная проверка на наличие цикла 
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[order[i]] = i;
    }
    bool hasCycle = false;
    for (int u = 0; u < n; u++) {
        for (int v : gr[u]) {
            if (pos[u] > pos[v]) {
                hasCycle = true;
                break;
            }
        }
        if (hasCycle) break;
    }

    if (hasCycle) {
        cout << "Граф содержит цикл! Топологическая сортировка невозможна." << endl;
    }
    else {
        cout << "\nТопологический порядок вершин: ";
        for (int i = 0; i < n; i++) {
            cout << order[i] << " ";
        }
    }
    return 0;
}