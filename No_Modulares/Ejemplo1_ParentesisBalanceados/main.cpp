/* ... (same content as earlier; omitted here for brevity) */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    cout << "Ejemplo 1 - Parentesis Balanceados (ingrese una expresion y presione Enter)\n";
    cout << "Ejemplo: (a+b)*(c-d)  ---  Escribir 'exit' para salir\n\n";
    string line;
    while (true) {
        cout << "Entrada> ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;
        stack<pair<char, int> > st;
        bool error = false;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '(' || c == '[' || c == '{') {
                st.push({c, (int) i});
                cout << "Pos " << i << ": push '" << c << "'. Pila size=" << st.size() << "\n";
            } else if (c == ')' || c == ']' || c == '}') {
                cout << "Pos " << i << ": encontrar cierre '" << c << "'. ";
                if (st.empty()) {
                    cout << "ERROR -> no hay apertura correspondiente\n";
                    error = true;
                    break;
                } else {
                    char open = st.top().first;
                    int posOpen = st.top().second;
                    st.pop();
                    bool match = (open == '(' && c == ')') || (open == '[' && c == ']') || (open == '{' && c == '}');
                    if (match) {
                        cout << "coincide con apertura '" << open << "' en pos " << posOpen << ". Pila size=" << st.
                                size() << "\n";
                    } else {
                        cout << "NO coincide con apertura '" << open << "' en pos " << posOpen << " -> ERROR\n";
                        error = true;
                        break;
                    }
                }
            } else {
                cout << "Pos " << i << ": caracter '" << c << "' (ignorado para el balanceo)\n";
            }
        }
        if (!error) {
            if (st.empty()) {
                cout << "Resultado: Paréntesis balanceados ✅\n";
            } else {
                cout << "Resultado: Faltan aperturas. Pila size=" << st.size() << "\n";
                while (!st.empty()) {
                    cout << " - Apertura '" << st.top().first << "' en pos " << st.top().second << "\n";
                    st.pop();
                }
            }
        }
        cout << "----------------------------------------\n";
    }
    return 0;
}
