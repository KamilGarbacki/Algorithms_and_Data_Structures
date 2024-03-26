#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
};

template <typename T>
class Stack {
	Node<T>* head = nullptr;
	int size = 0;
public:
	void push(T i){
		Node<T>* x = new Node<T>({ i, nullptr });
		x->next = head;
		head = x;
		size++;
	}
	T pop(){
		if (head != nullptr){
			Node<T>* temp = head;
			head = head->next;

			size--;

			return temp->data;
		}
		else
			throw invalid_argument("Stack is empty");
	}
	bool is_empty(){
		if (head == nullptr)
			return true;
		else
			return false;
	}
	int get_size(){
		return size;
	}
};

template <typename T>
class Queue {
    Node<T>* tail = nullptr;
    Node<T>* head = nullptr;
    int size = 0;
public:
    void enqueue(T i){
        size++;

        Node<T>* x = new Node<T>({ i, nullptr });

        if (tail == nullptr) {
            tail = x;
            head = x;
        }
        else {
            tail->next = x;
            tail = x;
        }
    }
    T dequeue(){
        if (head != nullptr){
            size--;

            Node<T>* temp = head;
            head = head->next;

            return(temp->data);
        }
        else
            throw invalid_argument("Stack is empty");
    }
    bool is_empty(){
        if (head == nullptr)
            return true;
        else
            return false;
    }
    int get_size(){
        return size;
    }
};

vector<string> event_type{ "Monster", "Urgent" };
vector<string> location_name{ "wschodzie", "zachodzie", "polnocy", "polodniu"};
vector<string> monster_name{ "Leszy", "Ghoul", "Golem"};
vector<string> village_event_name{ "pozar", "zaginone dziecko", "Plotka utknela na dachu stodoly"};

class Event {
public:
    const string type;
    const string name;
    const string location;
    Event(string type, string name, string location) : type(std::move(type)), name(std::move(name)), location(std::move(location)){}
};

class Wicher {
    int killed_monsters = 0;
    Stack<Event> monster_stack;
    Stack<Event> event_stack;
    Queue<Event> monster_queue;
public:
    void new_event() {
        string x_type = event_type[rand() % event_type.size()];
        string x_location = location_name[rand() % location_name.size()];
        string x_name;

        if (x_type == "Monster"){
            x_name = monster_name[rand() % monster_name.size()];
            Event e(x_type, x_name, x_location);
            monster_stack.push(e);

            cout << "Na " << x_location << " wioski, pojawil sie: " << x_name << "!" << endl;
        }
        else if (x_type == "Urgent"){
            x_name = village_event_name[rand() % village_event_name.size()];
            Event e(x_type, x_name, x_location);
            event_stack.push(e);

            cout << "Na " << x_location << " wioski, pojawilo sie zadanie: " << x_name << "!" << endl;
        }
        else{
            x_name = "Unknown";
        }
    }

    void take_action() {

        if (event_stack.is_empty()){
            if (monster_stack.is_empty())
                cout << "Nie ma aktualnie zadnych zadan" << endl;
            else{
                Event temp = monster_stack.pop();
                cout << temp.name << " znajdujacy sie na " << temp.location << " wioski, zostal pokonany przez wiedzmina!" << endl;

                killed_monsters++;

                monster_queue.enqueue(temp);

                if (killed_monsters == 10){
                    killed_monsters = 0;
                    cout << "Geralt udaje sie do soltysa by uzyskac nagrode za zabicie 10 potworow. Byly to: " << endl;

                    for (int i = 0; i < 10; i++){
                        Event t = monster_queue.dequeue();
                        cout << t.name << " ";
                    }
                    cout << endl;
                }
            }
        }
        else{
            Event temp = event_stack.pop();
            cout << "Wiedzmin zajal sie problemem na " << temp.location << " wioski, problemem bylo: '" << temp.name << "'" << endl;
        }
    }
};



int main() {
    srand((unsigned) time(nullptr));

    Wicher Geralt;
    int i = 0;

    while (i != 1) {
        cout << "Co robisz? (1-czekaj na wyadrzenie, 2-Podejmij akcje, 3-zakoncz program)" << endl;

        int wybor;
        cin >> wybor;
        if (wybor == 1){
            Geralt.new_event();
            Geralt.new_event();
            Geralt.new_event();
            cout << endl;
        }
        else if(wybor == 2){
            Geralt.take_action();
            cout << endl;
        }
        else if(wybor == 3){
            return 0;
        }
    }
    return 0;
}
