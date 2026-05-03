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

tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->color = RED;  // Новый узел всегда красный
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void rotate_left(tree*& root, tree* x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(tree*& root, tree* x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fix_insert(tree*& root, tree* z) {
    while (z != root && z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            tree* y = z->parent->parent->right; // дядя

            if (y != NULL && y->color == RED) {
                // случай 1: дядя красный
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                // случай 2: дядя черный
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(root, z);
                }
                // случай 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_right(root, z->parent->parent);
            }
        }
        else {
            // симметричный случай для правого родителя
            tree* y = z->parent->parent->left;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotate_left(root, z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) {
        tr = n;
        tr->color = BLACK; // корень всегда черный
        return;
    }
    // обычная вставка в бинарное дерево поиска
    tree* y = NULL;
    tree* current = tr;
    while (current != NULL) {
        y = current;
        if (n->inf < current->inf)
            current = current->left;
        else if (n->inf > current->inf)
            current = current->right;
        else {
            delete n;
            return;
        }
    }
    n->parent = y;
    if (n->inf < y->inf)
        y->left = n;
    else
        y->right = n;

    // восстанавливаем свойства красно-черного дерева
    fix_insert(tr, n);
}

tree* find_min(tree* tr) {
    while (tr->left != NULL)
        tr = tr->left;
    return tr;
}

tree* find_max(tree* tr) {
    while (tr->right != NULL)
        tr = tr->right;
    return tr;
}

// замена одного узла другим
void transplant(tree*& root, tree* u, tree* v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

// восстановление свойств после удаления
void fix_delete(tree*& root, tree* x) {
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            tree* w = x->parent->right; // брат

            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_left(root, x->parent);
                w = x->parent->right;
            }

            if ((w == NULL || w->left == NULL || w->left->color == BLACK) &&
                (w == NULL || w->right == NULL || w->right->color == BLACK)) {
                if (w != NULL) w->color = RED;
                x = x->parent;
            }
            else {
                if (w != NULL && (w->right == NULL || w->right->color == BLACK)) {
                    if (w->left != NULL) w->left->color = BLACK;
                    if (w != NULL) w->color = RED;
                    rotate_right(root, w);
                    w = x->parent->right;
                }

                if (w != NULL) {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != NULL) w->right->color = BLACK;
                    rotate_left(root, x->parent);
                }
                x = root;
            }
        }
        else {
            tree* w = x->parent->left;   // симметричный случай

            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_right(root, x->parent);
                w = x->parent->left;
            }

            if ((w == NULL || w->right == NULL || w->right->color == BLACK) &&
                (w == NULL || w->left == NULL || w->left->color == BLACK)) {
                if (w != NULL) w->color = RED;
                x = x->parent;
            }
            else {
                if (w != NULL && (w->left == NULL || w->left->color == BLACK)) {
                    if (w->right != NULL) w->right->color = BLACK;
                    if (w != NULL) w->color = RED;
                    rotate_left(root, w);
                    w = x->parent->left;
                }

                if (w != NULL) {
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != NULL) w->left->color = BLACK;
                    rotate_right(root, x->parent);
                }
                x = root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

void delete_node(tree*& root, int value) {
    tree* z = root;
    while (z != NULL && z->inf != value) {
        if (value < z->inf)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NULL) {
        cout << "Элемент не найден!" << endl;
        return;
    }
    tree* y = z;
    tree* x = NULL;
    Color y_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        transplant(root, z, z->left);
    }
    else {
        y = find_min(z->right);
        y_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        }
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            if (y->right != NULL) y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        if (y->left != NULL) y->left->parent = y;
        y->color = z->color;
    }
    delete z;

    if (y_color == BLACK) {
        fix_delete(root, x);
    }
}

void print_leaves(tree* tr) {
    if (!tr) return;
    if (!tr->left && !tr->right) {
        cout << tr->inf << " ";
        return;
    }
    print_leaves(tr->left);
    print_leaves(tr->right);
}

// симметричный обход
void inorder(tree* tr) {
    if (!tr) return;
    inorder(tr->left);
    cout << tr->inf << " ";
    inorder(tr->right);
}

// очистка дерева
void clear_tree(tree*& tr) {
    if (!tr) return;
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
    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        insert(tr, val);
    }
    cout << "Симметричный обход: ";
    inorder(tr);
    cout << "\nЛистья дерева: ";
    print_leaves(tr);
    return 0;
}