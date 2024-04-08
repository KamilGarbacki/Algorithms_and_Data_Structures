#include<iostream>

using namespace std;

class Student {
public:
    int id;

    int pow;
    int intel;
    int det;

    int sum;
    string student_faculty;

	Student() : id(0), pow(0), intel(0), det(0){}
	Student(int id) : id(id), pow(rand() % 100), intel(rand() % 100), det(rand() % 100), sum(pow + intel + det), student_faculty("___") {}

	bool operator == (Student& obj){
			return (id == obj.id && pow == obj.pow && intel == obj.intel && det == obj.det);
	}
};

class Node{
public:
	Student data;
	Node* next;
	Node* prev;

	Node() : next(nullptr), prev(nullptr){}
};


class List {
	Node* tail = nullptr;
	Node* head = nullptr;
	int size = 0;
public:
	List(){}
	List(List &l){
		Student temp;
		for (int i = 0; i < l.get_size(); i++){
			temp = l.get_node(i)->data;
            insert(temp);
		}
	}

	void insert(Student &x){
		Node* temp = new Node;
		temp->data = x;

		if (tail == nullptr)
		{
			tail = temp;
			head = temp;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

	Node* get_node(int index){
		Node* temp = head;
		for (int i = 0; i != index; i++){
			temp = temp->next;
		}
		return temp;
	}

	void remove_student(Student x){
		if (size == 0){
			cout << "Lista jest pusta" << endl;
			return;
		}

		for (int i = 0; i < size; i++){
			if (get_node(i)->data == x)
			{
				remove(i);
			}
		}
	}

	Student remove(int index){
		Node* temp = get_node(index);
		Student ret = temp->data;
		if (temp == tail && temp == head)
		{
			head = nullptr;
			tail = nullptr;
		}
		else if (temp == tail)
		{
			tail = temp->prev;
			tail->next = nullptr;
		}
		else if (temp == head)
		{
			head = temp->next;
			head->prev = nullptr;
		}
		else
		{
			Node* p_temp = temp->prev;
			Node* n_temp = temp->next;

			p_temp->next = n_temp;
			n_temp->prev = p_temp;
		}
		delete(temp);
		size--;
		return ret;
	}

	int get_size(){return size;}

	void write_list(){
		for (int i = 0; i < size; i++){
			Student temp = get_node(i)->data;
			cout << "Student id: " << temp.id << " | moc: " << temp.pow << " | intel: " << temp.intel;
			cout << " | det: " << temp.det << " | suma: " << temp.sum << " | wydzial: " << temp.student_faculty << endl;
		}
	}

	void swap_wimip(int index){
		Node* curr = get_node(index);
		Node* next = get_node(index + 1);

		Student temp = curr->data;

		if(curr->data.pow  < next->data.pow){

			curr->data = next->data;
			next->data = temp;

		}
		else if (curr->data.pow == next->data.pow){
			if (curr->data.intel < next->data.intel){
				curr->data = next->data;
				next->data = temp;
			}
			else if (curr->data.intel == next->data.intel){
				if (curr->data.det < next->data.det){
					curr->data = next->data;
					next->data = temp;
				}
			}
		}
	}

	void swap_wimir(int index){
		Node* curr = get_node(index);
		Node* next = get_node(index + 1);

		Student temp = curr->data;

		if (curr->data.det < next->data.det){
			curr->data = next->data;
			next->data = temp;

		}
		else if (curr->data.det == next->data.det){
			if (curr->data.pow < next->data.pow){
				curr->data = next->data;
				next->data = temp;
			}
			else if (curr->data.pow == next->data.pow){
				if (curr->data.intel < next->data.intel){
					curr->data = next->data;
					next->data = temp;
				}
			}
		}
	}

	void swap_wiet(int index){
		Node* curr = get_node(index);
		Node* next = get_node(index + 1);

		Student temp = curr->data;

		if (curr->data.intel < next->data.intel){
			curr->data = next->data;
			next->data = temp;

		}
		else if (curr->data.intel == next->data.intel){
			if (curr->data.det < next->data.det){
				curr->data = next->data;
				next->data = temp;
			}
			else if (curr->data.det == next->data.det){
				if (curr->data.pow < next->data.pow){
					curr->data = next->data;
					next->data = temp;
				}
			}
		}
	}

	void swap_sum(int index){
		Node* curr = get_node(index);
		Node* next = get_node(index + 1);

		Student temp = curr->data;

		if (curr->data.sum < next->data.sum){
			curr->data = next->data;
			next->data = temp;
		}
	}

	void sort_list(int mode){
		for (int i = 0; i < 29; i++){
			for (int j = 0; j < 29 - i; j++){
				switch(mode) {
				case 0: swap_sum(j); break;
				case 1: swap_wimip(j); break;
				case 2: swap_wimir(j); break;
				case 3: swap_wiet(j); break;
				default: break;
				}
			}
		}
	}
};

class University {
	List wimip; //pow > int > det
	List wimir; //det > pow >int
	List wiet; //int > det > pow
	List sum_list; //sum

	List t_wimip;
	List t_wimir;
	List t_wiet;

public:
University(List l): t_wiet(l), t_wimip(l), t_wimir(l){}

	void sort_lists(){
		t_wimip.sort_list(1);
		t_wimir.sort_list(2);
		t_wiet.sort_list(3);
	}

	void sort_final(){
		sum_list.sort_list(0);
	}

	void write_final(){
		sum_list.write_list();
	}

	void recruitment(){
		while (t_wimip.get_size() != 0){
			Student temp;
			temp = t_wimip.remove(0);
			temp.student_faculty = "wimip";
			t_wimir.remove_student(temp);
			t_wiet.remove_student(temp);

            wimip.insert(temp);
            sum_list.insert(temp);

			temp = t_wimir.remove(0);
			temp.student_faculty = "wimir";
			t_wiet.remove_student(temp);
			t_wimip.remove_student(temp);

            wimir.insert(temp);
            sum_list.insert(temp);

			temp = t_wiet.remove(0);
			temp.student_faculty = "wiet";
			t_wimir.remove_student(temp);
			t_wimip.remove_student(temp);

            wiet.insert(temp);
            sum_list.insert(temp);
		}
	}
	void write_faculty(){
		cout << "Studenci wimip:" << endl;
		wimip.write_list();

		cout << "Studenci wimir:" << endl;
		wimir.write_list();

		cout << "Studenci wiet:" << endl;
		wiet.write_list();
	}

	List get_wimip() { return wimip; }
	List get_wimir() { return wimir; }
	List get_wiet() { return wiet; }
};

List list_for_exercise(University u, int additional_students){
	List temp;
	temp = u.get_wimir();

	List new_list(temp);

	temp = u.get_wimip();

	for (int i = 0; i < additional_students; i++)
        new_list.insert(temp.get_node(i)->data);

	return new_list;
}


int main()
{
	List s_list;

	for (int i = 0; i < 30; i++){
		Student s(i);
        s_list.insert(s);
	}

	University agh(s_list);
	agh.sort_lists();
	agh.recruitment();
	agh.write_faculty();

	cout << "zad 3" << endl;
	agh.sort_final();
	agh.write_final();
	cout << "zad 2" << endl;

	List list_for_professor;
	list_for_professor = list_for_exercise(agh, 4);
	list_for_professor.write_list();

	return 0;
}
