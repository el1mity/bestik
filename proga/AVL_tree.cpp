#include <iostream>
using namespace std;


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

int height(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

void updateHeight(Node* node) {
    if (node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }
}

int getBalance(Node* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

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
    int b = getBalance(node);

    // Левый перекос
    if (b > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    // Правый перекос
    if (b < -1) {
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
    if (!node) return -1;
    int degree = 0;
    if (node->left) degree++;
    if (node->right) degree++;
    return degree;
}

// Симметричный обход 
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
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
    cout << "Введите количество элементов: "; cin >> n;

    if (n <= 0) {
        cout << "Некорректное количество элементов!\n";
        return 1;
    }

    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nСимметричный обход: ";
    inorder(root);
    cout << endl;

    cout << "\nВведите значение узла X для определения его степени: "; cin >> x;

    Node* nodeX = search(root, x);

    if (nodeX) {
        int degree = getNodeDegree(nodeX);
        cout << "Степень узла " << x << " = " << degree << endl;
    }
    else {
        cout << "\nУзел " << x << " не найден в дереве!" << endl;
    }

    clearTree(root);
    return 0;
}