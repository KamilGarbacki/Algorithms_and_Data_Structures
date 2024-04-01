#include<iostream>

using namespace std;

class Hero {
public:
    string name;
    int level;
    string skill;
};

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(): next(nullptr), prev(nullptr){}
};

template<typename T>
class List {
protected:
    Node<T>* tail = nullptr;
    Node<T>* head = nullptr;

    int size = 0;

    Node<T>* get_node(int index){
        Node<T>* temp = tail;
        for (int i = 0; i != index; i++){
            temp = temp->prev;
        }
        return temp;
    }

    void remove(int index){
        Node<T>* temp = get_node(index);

        if (temp == tail && temp == head){
            delete(temp);
            head = nullptr;
            tail = nullptr;
        }
        else if(temp == tail){
            tail = temp->prev;
            tail->next = nullptr;
            delete(temp);
        }
        else if (temp == head)
        {
            head = temp->next;
            head->prev = nullptr;
            delete(temp);
        }
        else{
            Node<T>* p_temp = temp->prev;
            Node<T>* n_temp = temp->next;

            p_temp->next = n_temp;
            n_temp->prev = p_temp;
        }
        size--;
    }
public:
    void insert(T x){
        Node<T> *temp = new Node<T>;
        temp->data = x;

        if (tail == nullptr){
            tail = temp;
            head = temp;
        }
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        size++;
    }

    void remove_val(T val){
        if (size == 0){
            return;
        }

        for (int i = 0; i < size; i++){
            if (get_node(i)->data == val)
                remove(i);
        }
    }

    int get_size(){
        return size;
    }

    bool is_empty(){
        if (size == 0)
            return true;
        else
            return false;
    }
};

class Hero_List : public List<Hero>{
public:
    void display(string name){
        for (int i = 0; i < size; i++){
            if (get_node(i)->data.name == name){
                cout << "Bohater: " << get_node(i)->data.name << " Poziom: " << get_node(i)->data.level << " Umiejetnosc: " << get_node(i)->data.skill << endl;
            }
        }
    }
};

int main(){
    return 0;
}

