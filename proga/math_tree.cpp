#include <iostream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

struct tree { // узел
    char inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(char x) { // создание узла
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

tree* create_tree(string str) {
    tree* tr = NULL;
    for (unsigned int i = 0; i < str.length(); i++) {
        tree* n = node(str[i]);

        if (str[i] == '-' || str[i] == '+') { // становится корнем
            if (tr != NULL) tr->parent = n;
            n->left = tr;
            tr = n;
        }
        else if (str[i] == '/' || str[i] == '*') {
            if (tr != NULL && isdigit(tr->inf)) { // первый знак операции - корень
                if (tr != NULL) tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else { // добавляем справа от корня
                if (tr != NULL) {
                    n->parent = tr;
                    n->left = tr->right;
                    if (tr->right != NULL) tr->right->parent = n;
                    tr->right = n;
                }
            }
        }
        else { // цифра
            if (!tr) tr = n; // первая в выражении - корень
            else {
                if (!tr->right) { // у корня нет правого сына
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                }
                else { // ищем операнд без правого сына
                    tree* x = tr->right;
                    while (x->right) x = x->right;
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
}

// прямой обход (префиксная форма)
void preorder(tree* tr) {
    if (tr) {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

// обратный обход (постфиксная форма) 
void postorder(tree* tr) {
    if (tr) {
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->inf << " ";
    }
}

// Вычисление значения выражения
int evaluate(tree* tr) {
    if (!tr) return 0;
    if (isdigit(tr->inf)) {
        return tr->inf - '0';
    }
    int leftVal = evaluate(tr->left);
    int rightVal = evaluate(tr->right);

    switch (tr->inf) {
    case '+': return leftVal + rightVal;
    case '-': return leftVal - rightVal;
    case '*': return leftVal * rightVal;
    case '/': return leftVal / rightVal;
    default: return 0;
    }
}

void clearTree(tree*& tr) {
    if (!tr) return;
    clearTree(tr->left);
    clearTree(tr->right);
    delete tr;
    tr = NULL;
}

int main() {
    setlocale(LC_ALL, "RUS");
    string str;
    cout << "Введите математическое выражение: ";
    getline(cin, str);

    string clean_str; // удалим пробелы
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            clean_str += str[i];
        }
    }

    // Проверка на допустимые символы
    string znak = "+-/*0123456789";
    bool flag = true;
    for (unsigned int i = 0; i < clean_str.length(); i++) {
        if (znak.find_first_of(clean_str[i]) == string::npos) {
            flag = false;
            break;
        }
    }

    if (!flag) {
        cout << "Ошибка! Недопустимые символы в выражении!" << endl;
        return 1;
    }

    else {
        tree* tr = create_tree(clean_str);
        if (tr == NULL) {
            cout << "Ошибка при создании дерева!" << endl;
            return 1;
        }
        cout << "\nИсходное выражение: " << clean_str << endl;

        cout << "Префиксная форма (прямой обход): ";
        preorder(tr);
        cout << endl;

        cout << "Постфиксная форма (обратный обход): ";
        postorder(tr);
        cout << endl;

        cout << "\nРезультат вычисления: " << evaluate(tr) << endl;

        clearTree(tr);
    }

    return 0;
}