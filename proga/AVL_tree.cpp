#include <iostream>
using namespace std;

// Структура узла AVL-дерева
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

// Получение высоты
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Обновление высоты
void updateHeight(Node* node) {
    if (node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

// Получение баланса
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Правый поворот
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Левый поворот
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Балансировка
Node* balance(Node* node) {
    if (!node) return nullptr;

    updateHeight(node);
    int balanceFactor = getBalance(node);

    // Левый перекос
    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Правый перекос
    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Вставка узла
Node* insert(Node* root, int value) {
    if (!root) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else {
        return root;
    }

    return balance(root);
}

// Поиск узла по значению
Node* search(Node* root, int value) {
    if (!root || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

// Определение степени узла (количество потомков)
int getNodeDegree(Node* node) {
    if (!node) return -1; // Узел не найден

    int degree = 0;
    if (node->left) degree++;
    if (node->right) degree++;

    return degree;
}

// Симметричный обход для вывода дерева
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Вывод дерева в структурированном виде
void printTree(Node* root, int level = 0) {
    if (!root) return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << root->data << endl;

    printTree(root->left, level + 1);
}

// Очистка дерева
void clearTree(Node*& root) {
    if (!root) return;
    clearTree(root->left);
    clearTree(root->right);
    delete root;
    root = nullptr;
}

int main() {
    setlocale(LC_ALL, "RUS");

    Node* root = nullptr;
    int n, value, x;

    // Ввод исходных данных
    cout << "=== Определение степени узла в AVL-дереве ===\n\n";
    cout << "Введите количество элементов: ";
    cin >> n;

    if (n <= 0) {
        cout << "Некорректное количество элементов!\n";
        return 1;
    }

    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    // Вывод дерева
    cout << "\nСтруктура AVL-дерева:\n";
    printTree(root);

    cout << "\nСимметричный обход (отсортированные элементы): ";
    inorder(root);
    cout << endl;

    // Ввод узла X
    cout << "\nВведите значение узла X для определения его степени: ";
    cin >> x;

    // Поиск узла и определение степени
    Node* nodeX = search(root, x);

    if (nodeX) {
        int degree = getNodeDegree(nodeX);
        cout << "\nУзел " << x << " найден!\n";
        cout << "Степень узла " << x << " = " << degree << endl;

        // Дополнительная информация
        cout << "\nДети узла:\n";
        if (nodeX->left) {
            cout << "  - Левый потомок: " << nodeX->left->data << endl;
        }
        if (nodeX->right) {
            cout << "  - Правый потомок: " << nodeX->right->data << endl;
        }
        if (!nodeX->left && !nodeX->right) {
            cout << "  - Узел является листом (нет детей)\n";
        }
    }
    else {
        cout << "\nУзел " << x << " не найден в дереве!\n";
    }

    // Очистка памяти
    clearTree(root);

    return 0;
}