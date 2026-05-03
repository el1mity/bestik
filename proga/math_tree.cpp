#include <iostream>
#include <string>
#include <stack>
#include <vector>
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

// проверка является ли символ оператором
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// проверка приоритета операторов
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// преобразование в постфиксную запись
string to_postfix(string expr) {
    string result;
    stack<char> ops;

    for (char c : expr) {
        if (isdigit(c)) {
            result += c; // числа сразу добавляем
        }
        else if (c == '(') {
            ops.push(c);
        }
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                result += ops.top();
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // удаляем (
        }
        else if (is_operator(c)) {
            while (!ops.empty() && priority(ops.top()) >= priority(c)) {
                result += ops.top();
                ops.pop();
            }
            ops.push(c);
        }
    }
    while (!ops.empty()) {
        result += ops.top();
        ops.pop();
    }
    return result;
}

// создание дерева выражений из постфиксной записи
tree* tree_from_postfix(string postfix) {
    stack<tree*> st;
    for (char c : postfix) {
        tree* n = node(c);

        if (isdigit(c)) {
            st.push(n); // если число то просто кладем в стек
        }
        else if (is_operator(c)) {
            // если оператор то берем два последних узла
            tree* right = st.top(); st.pop();
            tree* left = st.top(); st.pop();

            n->left = left;
            n->right = right;
            left->parent = n;
            right->parent = n;
            st.push(n);
        }
    }
    return st.top();
}

// прямой обход (префиксный)
void preorder(tree* tr) {
    if (tr) {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

// обратный обход (постфиксный)
void postorder(tree* tr) {
    if (tr) {
        postorder(tr->left);
        postorder(tr->right);
        cout << tr->inf << " ";
    }
}

// вычисление значения выражения
int eval(tree* tr) {
    if (!tr) return 0;
    if (isdigit(tr->inf)) {
        return tr->inf - '0';
    }
    int leftVal = eval(tr->left);
    int rightVal = eval(tr->right);

    switch (tr->inf) {
    case '+': return leftVal + rightVal;
    case '-': return leftVal - rightVal;
    case '*': return leftVal * rightVal;
    case '/': return leftVal / rightVal;
    default: return 0;
    }
}

// вывод дерева в виде структуры
void printTree(tree* tr, int level = 0) {
    if (!tr) return;
    printTree(tr->right, level + 1);

    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << tr->inf << endl;
    printTree(tr->left, level + 1);
}

int main() {
    setlocale(LC_ALL, "RUS");
    string tmp;
    cout << "Введите математическое выражение: ";
    getline(cin, tmp);
    string clean_tmp;
    for (char c : tmp) {
        if (c != ' ') {
            clean_tmp += c;
        }
    }
    try {
        string postfix = to_postfix(clean_tmp);
        tree* root = tree_from_postfix(postfix);

        cout << "Префиксная форма (прямой обход): ";
        preorder(root);
        cout << endl;

        cout << "Постфиксная форма (обратный обход): ";
        postorder(root);
        cout << endl;

        int result = eval(root);
        cout << "\nРезультат вычисления: " << result << endl;

    }
    catch (exception& e) {
        cout << "Ошибка при обработке выражения!" << endl;
    }
    return 0;
}