#ifndef PROJ2_NODE_H
#define PROJ2_NODE_H
#include <string>

class Node {
private:
    int value;
    bool has_value; // true, если узел получил значение из файла
    Node *left;
    Node *right;

public:
    // Конструктор для узла-заглушки (без значения)
    Node() : value(0), has_value(false), left(nullptr), right(nullptr) {
    }

    // Конструктор для узла с заданным значением
    Node(int val) : value(val), has_value(true), left(nullptr), right(nullptr) {
    }

    ~Node() {
        delete left;
        delete right;
    }

    /*
     * Добавление новой вершины по указанному пути.
     * Предполагается, что в пути только символы '0' и '1'
     */
    void InsertByPath(const std::string &path, int val) {
        Node *current = this;

        for (char direction: path) {
            if (direction == '0') {
                if (!current->left)
                    current->left = new Node(); // узел заглушка
                current = current->left;
            } else if (direction == '1') {
                if (!current->right)
                    current->right = new Node(); // узел заглушка
                current = current->right;
            }
        }

        // Устанавка значения в конечном узле
        current->value = val;
        current->has_value = true;
    }

    bool IsValidTree() const {
        return IsValidRec(this);
    }

    void Print() {
        PrintRec(this, 0);
    }

private:
    static bool IsValidRec(const Node *node) {
        if (!node)
            return true;

        // Если узел не имеет значения, но у него есть хотя бы один потомок, то дерево некорректно
        if (!node->has_value && (node->left || node->right))
            return false;

        return IsValidRec(node->left) && IsValidRec(node->right);
    }

    static void PrintRec(const Node* tree, int h) {
        using namespace std;

        if (!tree)
            return;

        PrintRec(tree->right, h + 1);

        cout << string(h * 4, ' ') << tree->value << endl;

        PrintRec(tree->left, h + 1);
    }
};

#endif //PROJ2_NODE_H
