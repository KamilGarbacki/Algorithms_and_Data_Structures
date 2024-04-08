#include <iostream>
#include <functional>

using namespace std;

class Person{
public:
    string name;
    string surname;

    Person(string name, string surname): name(name), surname(surname){}
    Person()= default;

    friend ostream& operator<<(ostream& os, const Person& per)
    {
        os << per.name << " | " << per.surname;
        return os;
    }
};



template <typename T>
class Node {
public:
    T data;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(T val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}

    Node() = default;
};

template <typename T>
class BST {
    Node<T>* root;
public:
    BST() : root(nullptr) {}

    void insert(string name, string surname) {
        T per(name, surname);
        Node<T>* temp = new Node(per);
        Node<T>** look;
        Node<T>* parent = nullptr;

        look = &root;

        while ((*look) != nullptr) {
            int res_name = (*look)->data.name.compare(per.name);
            int res_sur = (*look)->data.surname.compare(per.surname);
            if (res_name > 0 || (res_name == 0 && res_sur > 0)) {
                parent = (*look);
                look = &((*look)->left);
            } else {
                parent = (*look);
                look = &((*look)->right);
            }
        }
        temp->parent = parent;
        (*look) = temp;
    }

    Node<T>* search(string name, string surname) {
        T per(name, surname);
        if (root == nullptr) {
            cout << "Drzewo jest puste" << endl;
            return nullptr;
        } else {
            Node<T>* look = root;
            while (look != nullptr) {
                int res_name = look->data.name.compare(per.name);
                int res_sur = look->data.surname.compare(per.surname);

                if (res_name > 0 || (res_name == 0 && res_sur > 0))
                    look = look->left;
                else if (res_name < 0 || (res_name == 0 && res_sur < 0))
                    look = look->right;
                else
                    return look;
            }
            return nullptr;
        }
    }

    void remove(string name, string surname) {
        Node<T>* n = search(name, surname);

        if (n->left == nullptr && n->right == nullptr) {
            Node<T>* tmp = n->parent;

            if (tmp == nullptr)
                delete n;
            else if (tmp->left == n) {
                tmp->left = nullptr;

                delete n;
            } else {
                tmp->right = nullptr;

                delete n;
            }

        } else if (n->left == nullptr) {
            Node<T>* tmp = n->right;
            n->data = n->right->data;
            n->left = n->right->left;
            n->right = n->right->right;

            delete tmp;

            n->right = nullptr;
        } else if (n->right == nullptr) {
            Node<T>* tmp = n->left;
            n->data = n->left->data;
            n->right = n->left->right;
            n->left = n->left->left;

            delete tmp;

            n->left = nullptr;
        }
        else {
            Node<T>* to_swap = n->right;

            while (to_swap->left != nullptr)
                to_swap = to_swap->left;

            if (to_swap->parent != n)
                to_swap->parent->left = to_swap->right;
            else
                to_swap->parent->right = to_swap->right;

            n->data = to_swap->data;

            delete to_swap;
        }
    }

    Node<T>* get_root() { return root; }

    int height(Node<T>* temp) {
        if (temp == nullptr)
            return 0;
        else {
            int left_height = height(temp->left);
            int right_height = height(temp->right);
            if (left_height > right_height)
                return left_height + 1;
            else
                return right_height + 1;
        }
    }

    vector<T> inOrder() {
        std::vector<T> res;

        function<void(Node<T> *)> rec = [&](Node<T> *n) {
            if (n == nullptr) return;

            rec(n->left);

            res.push_back(n->data);

            rec(n->right);
        };

        rec(root);

        return res;
    }

    void check_current_level(Node<T>* root, int level, string t_name, string t_surname)
    {
        if(root == nullptr)
            cout << "Tej osoby nie ma w notatniku" << endl;
        else if(level == 1 && root->data.name == t_name && root->data.surname == t_surname)
            cout << "Podana osoba znajduje sie w notatniku" << endl;
        else if(level > 1){
            check_current_level(root->left, level-1, t_name, t_surname);
            check_current_level(root->right, level-1, t_name, t_surname);
        }
    }

    void BFS_check(Node<T>* root , string name, string surname)
    {
        int h = height(root);
        for (int i = 1; i <= h; i++) {
            check_current_level(root, i, name, surname);
        }
    }

    bool check_preorder(Node<T>* n, string name, string surname)
    {
        bool check = false;

        function<void(Node<T> *)> rec = [&](Node<T> *n) {
            if (n == nullptr) return;
            else if (n->data.name == name && n->data.surname == surname)
            {
                check = true;
                return;
            }
            rec(n->left);
            rec(n->right);
        };

        rec(n);

        return check;
    }

    void check_modes(int mode, string name, string surname)
    {
        if(mode == 1)
        {
            if(check_preorder(root, name, surname))
                cout << "Ta osoba jest w notatniku" << endl;
            else
                cout << "Tej osoby nie ma w notatniku" << endl;
        }
        else if(mode == 2)
            BFS_check(root, name, surname);
    }

};

int main() {
    BST<Person> notebook;
    notebook.insert("david", "my_roommate");
    notebook.insert("kamil", "garbacki");
    notebook.insert("danek", "my_friend");

    vector<Person> dn = notebook.inOrder();

    for (const auto & i : dn) {
        cout << i << endl;
    }

    notebook.check_modes(1, "kamil", "garbacki");
    notebook.check_modes(2, "kamil", "garbacki");
}
