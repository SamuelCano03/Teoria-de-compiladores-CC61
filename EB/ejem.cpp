#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Nodo del AST
struct TreeNode {
    char op;
    int value;
    vector<TreeNode*> children;
};

// Analizador léxico
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Analizador sintáctico y construcción del AST
TreeNode* parseExpression(vector<string>& tokens, size_t& index) {
    if (index >= tokens.size()) {
        return nullptr;
    }

    TreeNode* node = new TreeNode;
    if (isdigit(tokens[index][0]) || (tokens[index][0] == '-' && isdigit(tokens[index][1]))) {
        node->value = stoi(tokens[index]);
    } else {
        node->op = tokens[index][0];
        index++;
        while (index < tokens.size()) {
            TreeNode* child = parseExpression(tokens, index);
            if (child) {
                node->children.push_back(child);
            } else {
                break;
            }
        }
    }
    return node;
}

// Función para evaluar el AST
int evaluate(TreeNode* node) {
    if (node->children.empty()) {
        return node->value;
    } else {
        int result = (node->op == '+' ? 0 : 1);  // Inicializar el resultado según la operación
        for (TreeNode* child : node->children) {
            result = (node->op == '+' ? result + evaluate(child) : result * evaluate(child));
        }
        return result;
    }
}

int main() {
    string input = "- * 4 3 2";
    vector<string> tokens = tokenize(input);
    
    size_t index = 0;
    TreeNode* root = parseExpression(tokens, index);

    if (root) {
        cout << "Resultado: " << evaluate(root) << endl;
    } else {
        cout << "Error de sintaxis" << endl;
    }

   

    return 0;
}
