#include<iostream>
#include <utility>

using namespace std;

class Hero {
    string name;
    int level;
    string skill;
public:
    Hero()=default;
    Hero(string n, int l, string s): name(std::move(n)), level(l), skill(std::move(s)){}

    bool operator ==(const Hero &h){
        return(name == h.name && level == h.level && skill == h.skill);
    }

    string get_name(){return name;}
    int get_level(){return level;}
    string get_skill(){return skill;}
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
    void display(Node<Hero>* temp){
        cout<<"Bohater: "<< temp->data.get_name()<<" Poziom: "<<temp->data.get_level()<<" Umiejetnosc: "<< temp->data.get_skill() << endl;
    }
public:
    void display_hero(string name){
        cout << "--------------------------------" << endl;
        for (int i = 0; i < size; i++){
            if (get_node(i)->data.get_name() == name){
                display(get_node(i));
            }
        }
    }
    void display_all(){
        cout << "--------------------------------" << endl;
        Node<Hero>* temp = tail;
        for (int i = 0; i < size; i++){
            display(temp);
            temp = temp->prev;
        }
    }
};

int main(){
    Hero_List h_list;

    h_list.insert(Hero("Kelsier", 29, "skradanie"));
    h_list.insert(Hero("Hoid", 99, "teleportacja"));
    h_list.insert(Hero("Kaladin", 25, "latanie"));
    h_list.display_all();
    h_list.display_hero("Hoid");
    h_list.remove_val(Hero("Kelsier", 29, "skradanie"));
    h_list.display_all();
    return 0;
}
