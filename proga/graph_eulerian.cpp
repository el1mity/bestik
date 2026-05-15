#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m;
    cout << "Введите количество вершин: "; cin >> n;
    cout << "Введите количество рёбер: "; cin >> m;
    vector<vector<int>> gr(n);
    vector<int> step(n, 0);

    cout << "Введите рёбра:" << endl;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
        step[x]++;
        step[y]++;
    }

    // Определяем степени всех вершин
    int v1 = -1, v2 = -1;
    for (int i = 0; i < n; i++) {
        if (step[i] % 2 == 1) {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else {
                cout << "Эйлерова пути/цикла нет" << endl;
                return 0;
            }
        }
    }

    // Если есть вершины с нечётными степенями, добавляем фиктивное ребро
    bool hasFakeEdge = (v1 != -1);
    if (hasFakeEdge) {
        gr[v1].push_back(v2);
        gr[v2].push_back(v1);
        step[v1]++;
        step[v2]++;
    }

    stack<int> st;
    vector<int> result;

    // Стартовая вершина: если есть нечетные, начинаем с первой нечетной
    int start = 0;
    if (v1 != -1) start = v1;
    st.push(start);

    while (!st.empty()) {
        int cur = st.top();

        if (!gr[cur].empty()) {
            int neighbor = gr[cur][0];

            // Удаляем ребро cur-neighbor
            gr[cur].erase(remove(gr[cur].begin(), gr[cur].end(), neighbor), gr[cur].end());
            gr[neighbor].erase(remove(gr[neighbor].begin(), gr[neighbor].end(), cur), gr[neighbor].end());

            st.push(neighbor);
        }
        else {
            result.push_back(cur);
            st.pop();
        }
    }

    // Если есть фиктивное ребро — корректируем путь
    if (hasFakeEdge) {
        // Ищем разрез в нужном месте
        for (size_t i = 0; i + 1 < result.size(); i++) {
            if ((result[i] == v1 && result[i + 1] == v2) ||
                (result[i] == v2 && result[i + 1] == v1)) {
                // Сдвигаем результат
                vector<int> new_result;
                for (size_t j = i + 1; j < result.size(); j++)
                    new_result.push_back(result[j]);
                for (size_t j = 0; j <= i; j++)
                    new_result.push_back(result[j]);
                result = new_result;
                break;
            }
        }
        // Убираем фиктивное ребро 
        result.pop_back();
    }

    // Проверка остатков рёбер
    bool hasEdges = false;
    for (int i = 0; i < n; i++) {
        if (!gr[i].empty()) {
            hasEdges = true;
            break;
        }
    }

    if (hasEdges) {
        cout << "Граф несвязный, Эйлерова цикла нет." << endl;
    }
    else {
        cout << "\nЭйлеров ";
        if (v1 == -1) cout << "цикл: ";
        else cout << "путь: ";

        for (int i = result.size() - 1; i >= 0; i--) {
            cout << result[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}