#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct tree {
    int inf;
    Color color;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(tree* p, int X) {
    tree* n = new tree;
    n->inf = X;
    n->color = RED;
    n->left = n->right = NULL;
    n->parent = p;
    return n;
}

tree* root(int X) {
    tree* n = new tree;
    n->inf = X;
    n->color = BLACK;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

tree* grandparent(tree* X) {
    if (X != NULL && X->parent != NULL)
        return X->parent->parent;
    return NULL;
}

tree* uncle(tree* X) {
    tree* g = grandparent(X);
    if (g == NULL) return NULL;
    if (X->parent == g->left) return g->right;
    else return g->left;
}

tree* sibling(tree* X) {
    if (X != NULL && X->parent != NULL) {
        if (X == X->parent->left) return X->parent->right;
        else return X->parent->left;
    }
    return NULL;
}

void rotate_left(tree*& tr, tree* X) {
    tree* Y = X->right;
    X->right = Y->left;
    if (Y->left != NULL) Y->left->parent = X;
    Y->parent = X->parent;
    if (X->parent == NULL) tr = Y;
    else if (X == X->parent->left) X->parent->left = Y;
    else X->parent->right = Y;
    Y->left = X;
    X->parent = Y;
}

void rotate_right(tree*& tr, tree* X) {
    tree* Y = X->left;
    X->left = Y->right;
    if (Y->right != NULL) Y->right->parent = X;
    Y->parent = X->parent;
    if (X->parent == NULL) tr = Y;
    else if (X == X->parent->right) X->parent->right = Y;
    else X->parent->left = Y;
    Y->right = X;
    X->parent = Y;
}

void insert_case1(tree*& tr, tree* X);
void insert_case2(tree*& tr, tree* X);
void insert_case3(tree*& tr, tree* X);
void insert_case4(tree*& tr, tree* X);
void insert_case5(tree*& tr, tree* X);

void insert_case1(tree*& tr, tree* X) {
    if (X->parent == NULL) X->color = BLACK;
    else insert_case2(tr, X);
}

void insert_case2(tree*& tr, tree* X) {
    if (X->parent->color == RED) insert_case3(tr, X);
}

void insert_case3(tree*& tr, tree* X) {
    tree* U = uncle(X);
    tree* G = grandparent(X);

    if (U != NULL && U->color == RED && X->parent->color == RED) {
        X->parent->color = BLACK;
        U->color = BLACK;
        G->color = RED;
        insert_case1(tr, G);
    }
    else {
        insert_case4(tr, X);
    }
}

void insert_case4(tree*& tr, tree* X) {
    tree* G = grandparent(X);

    if (X == X->parent->right && X->parent == G->left) {
        rotate_left(tr, X);
        X = X->left;
    }
    else if (X == X->parent->left && X->parent == G->right) {
        rotate_right(tr, X);
        X = X->right;
    }
    insert_case5(tr, X);
}

void insert_case5(tree*& tr, tree* X) {
    tree* G = grandparent(X);
    X->parent->color = BLACK;
    G->color = RED;
    if (X == X->parent->left && X->parent == G->left) rotate_right(tr, G);
    else rotate_left(tr, G);
}

void insert(tree*& tr, tree* Prev, int X) {
    if (X < Prev->inf && Prev->left == NULL) {
        Prev->left = node(Prev, X);
        insert_case1(tr, Prev->left);
    }
    else if (X > Prev->inf && Prev->right == NULL) {
        Prev->right = node(Prev, X);
        insert_case1(tr, Prev->right);
    }
    else if (X < Prev->inf && Prev->left != NULL) {
        insert(tr, Prev->left, X);
    }
    else if (X > Prev->inf && Prev->right != NULL) {
        insert(tr, Prev->right, X);
    }
}

void delete_case1(tree*& tr, tree* X);
void delete_case2(tree*& tr, tree* X);
void delete_case3(tree*& tr, tree* X);
void delete_case4(tree*& tr, tree* X);
void delete_case5(tree*& tr, tree* X);
void delete_case6(tree*& tr, tree* X);

void replace(tree*& tr, tree* X) {
    tree* ch = NULL;
    if (X->left != NULL) {
        ch = X->left;
        ch->parent = X->parent;
        if (X->parent != NULL) {
            if (X == X->parent->left) X->parent->left = ch;
            else X->parent->right = ch;
        }
        else tr = ch;
    }
    else if (X->right != NULL) {
        ch = X->right;
        ch->parent = X->parent;
        if (X->parent != NULL) {
            if (X == X->parent->left) X->parent->left = ch;
            else X->parent->right = ch;
        }
        else tr = ch;
    }
}

void delete_case1(tree*& tr, tree* X) {
    if (X->parent == NULL) {
        if (X->left != NULL) tr = X->left;
        else tr = X->right;
    }
    else delete_case2(tr, X);
}

void delete_case2(tree*& tr, tree* X) {
    tree* S = sibling(X);
    if (S != NULL && S->color == RED) {
        X->parent->color = RED;
        S->color = BLACK;
        if (X == X->parent->left) rotate_left(tr, X->parent);
        else rotate_right(tr, X->parent);
    }
    delete_case3(tr, X);
}

void delete_case3(tree*& tr, tree* X) {
    tree* S = sibling(X);
    if (X->parent->color == BLACK && S != NULL && S->color == BLACK &&
        (S->left == NULL || S->left->color == BLACK) &&
        (S->right == NULL || S->right->color == BLACK)) {
        S->color = RED;
        delete_case1(tr, X->parent);
    }
    else delete_case4(tr, X);
}

void delete_case4(tree*& tr, tree* X) {
    tree* S = sibling(X);
    if (X->parent->color == RED && S != NULL && S->color == BLACK &&
        (S->left == NULL || S->left->color == BLACK) &&
        (S->right == NULL || S->right->color == BLACK)) {
        S->color = RED;
        X->parent->color = BLACK;
    }
    else delete_case5(tr, X);
}

void delete_case5(tree*& tr, tree* X) {
    tree* S = sibling(X);
    if (S->color == BLACK) {
        if (X == X->parent->left && S->left != NULL && S->left->color == RED &&
            (S->right == NULL || S->right->color == BLACK)) {
            S->color = RED;
            S->left->color = BLACK;
            rotate_right(tr, S);
        }
        else if (X == X->parent->right && S->right != NULL && S->right->color == RED &&
            (S->left == NULL || S->left->color == BLACK)) {
            S->color = RED;
            S->right->color = BLACK;
            rotate_left(tr, S);
        }
    }
    delete_case6(tr, X);
}

void delete_case6(tree*& tr, tree* X) {
    tree* S = sibling(X);
    S->color = X->parent->color;
    X->parent->color = BLACK;
    if (X == X->parent->left) {
        if (S->right != NULL) S->right->color = BLACK;
        rotate_left(tr, X->parent);
    }
    else {
        if (S->left != NULL) S->left->color = BLACK;
        rotate_right(tr, X->parent);
    }
}

tree* find_node(tree* tr, int value) {
    while (tr != NULL && tr->inf != value) {
        if (value < tr->inf) tr = tr->left;
        else tr = tr->right;
    }
    return tr;
}

void delete_one(tree*& tr, tree* X) {
    if (X->left != NULL && X->right != NULL) {
        tree* buf = X->right;
        while (buf->left != NULL) buf = buf->left;
        X->inf = buf->inf;
        X = buf;
    }

    if (X->left != NULL || X->right != NULL) {
        tree* ch = (X->left != NULL) ? X->left : X->right;
        replace(tr, X);
        if (X->color == BLACK) {
            if (ch->color == RED) ch->color = BLACK;
            else delete_case1(tr, ch);
        }
    }
    else {
        if (X->color == BLACK) delete_case1(tr, X);
        if (X->parent != NULL) {
            if (X == X->parent->left) X->parent->left = NULL;
            else X->parent->right = NULL;
        }
    }
    delete X;
}

void delete_value(tree*& tr, int value) {
    tree* X = find_node(tr, value);
    if (X == NULL) {
        cout << "Элемент " << value << " не найден!" << endl;
        return;
    }
    delete_one(tr, X);
}

// Симметричный обход
void inorder(tree* tr) {
    if (tr == NULL) return;
    inorder(tr->left);
    cout << tr->inf << " ";
    inorder(tr->right);
}

// Вывод всех листьев
void print_leaves(tree* tr) {
    if (tr == NULL) return;
    if (tr->left == NULL && tr->right == NULL) {
        cout << tr->inf << " ";
        return;
    }
    print_leaves(tr->left);
    print_leaves(tr->right);
}

// Очистка дерева
void clear_tree(tree*& tr) {
    if (tr == NULL) return;
    clear_tree(tr->left);
    clear_tree(tr->right);
    delete tr;
    tr = NULL;
}

int main() {
    setlocale(LC_ALL, "RUS");
    tree* tr = NULL;
    int n, val;
    cout << "Введите количество элементов: "; cin >> n;

    if (n > 0) {
        cout << "Введите " << n << " элементов: ";
        for (int i = 0; i < n; ++i) {
            cin >> val;
            if (i == 0) tr = root(val);
            else {
                insert(tr, tr, val);
            }
        }
    }
    else {
        cout << "Дерево пустое!";
        return 0;
    }

    cout << "\nСимметричный обход: ";
    inorder(tr);

    cout << "\nЛистья дерева: ";
    print_leaves(tr);

    clear_tree(tr);
    return 0;
}