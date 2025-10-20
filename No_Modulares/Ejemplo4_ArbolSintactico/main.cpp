#include <bits/stdc++.h>
using namespace std;

struct Node {
    string val;
    Node* left;
    Node* right;
    Node(string v, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r) {}
};

// --- Prototipos ---
Node* expr();
Node* term();
Node* factor();
int eval(Node* n);
void printTree(Node* n, int indent = 0);

// --- Variables globales para el parser ---
string input;
int pos = 0;

// --- Funciones auxiliares ---
char peek() {
    if (pos < (int)input.size())
        return input[pos];
    return '\0';
}

char get() {
    if (pos < (int)input.size())
        return input[pos++];
    return '\0';
}

void skipSpaces() {
    while (isspace(peek()))
        get();
}

// --- Gramática ---
Node* factor() {
    skipSpaces();
    if (isdigit(peek())) {
        string num;
        while (isdigit(peek()))
            num += get();
        return new Node(num);
    }
    else if (peek() == '(') {
        get(); // consume '('
        Node* inside = expr();
        skipSpaces();
        if (peek() == ')') get();
        else cout << "Error: falta ')' \n";
        return inside;
    }
    else {
        cout << "Error: token inesperado '" << peek() << "'\n";
        get();
        return new Node("?");
    }
}

Node* term() {
    Node* left = factor();
    skipSpaces();
    while (peek() == '*' || peek() == '/') {
        char op = get();
        Node* right = factor();
        left = new Node(string(1, op), left, right);
        skipSpaces();
    }
    return left;
}

Node* expr() {
    Node* left = term();
    skipSpaces();
    while (peek() == '+' || peek() == '-') {
        char op = get();
        Node* right = term();
        left = new Node(string(1, op), left, right);
        skipSpaces();
    }
    return left;
}

// --- Evaluación del árbol ---
int eval(Node* n) {
    if (!n) return 0;
    if (!n->left && !n->right)
        return stoi(n->val);
    int l = eval(n->left);
    int r = eval(n->right);
    if (n->val == "+") return l + r;
    if (n->val == "-") return l - r;
    if (n->val == "*") return l * r;
    if (n->val == "/") return (r != 0 ? l / r : 0);
    return 0;
}

// --- Impresión del árbol ---
void printTree(Node* n, int indent) {
    if (!n) return;
    for (int i = 0; i < indent; i++) cout << "  ";
    cout << n->val << "\n";
    printTree(n->left, indent + 1);
    printTree(n->right, indent + 1);
}

int main() {
    cout << "Ingrese una expresion, por ejemplo: 3 + 5 * (2 - 1): ";
    getline(cin, input);

    Node* root = expr();

    cout << "\n--- Arbol sintactico ---\n";
    printTree(root);

    cout << "\nResultado: " << eval(root) << "\n";
    return 0;
}
