#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;
struct node
{
	float value;
	node* next = NULL;
	node* prev = NULL;
};
void show(node* head)
{

	while (head != NULL)
	{
		cout << head->value << '\t';
		head = head->next;
	}
	cout << endl;
}
void add(node*& head, float value, int position)//adds element at position. If position<=0 element goes at the start; if position>=number of elements, it goes at the end
{
	node* temp = head;
	if (position <= 0 || head == 0)
	{
		temp = new node;
		temp->value = value;
		temp->next = head;
		if (head) head->prev = temp;
		head = temp;
		return;
	}
	int i = 1;
	node* Node = new node;
	Node->value = value;
	while (1)
	{
		if (temp->next != NULL&&i<position) temp = temp->next;
		else if (temp->next == NULL)
		{
			if (temp->next == 0)//adding at the last place in the list
			{
				Node->next = 0;
				Node->prev = temp;
				temp->next = Node;
				return;
			}
			Node->next = temp;
			Node->prev = temp->prev;
			temp->prev = Node;
			if (Node->prev) Node->prev->next = Node;
			return;
		}
		else
		{
			Node->next = temp->next;
			Node->prev = temp;
			temp->next = Node;
			Node->next->prev = Node;
			return;
		}
		i++;
	}

}
void add(node*& head, float value)
{
	add(head, value, 0);
}
void swap(node *&head, node *&t1, node *&t2)
{
	node *t1Prev = t1->prev, *t1Next = t1->next;
	if (t1->next == t2 || t2->next == t1)
	{
		if (t1->next == t2)
		{
			t2->prev = t1->prev;
			t1->next = t2->next;
			t2->next = t1;
			t1->prev = t2;
		}
		else
		{
			t2->next = t1->next;
			t1->prev = t2->prev;
			t1->next = t2;
			t2->prev = t1;
		}
	}
	else
	{
		t1->next = t2->next;
		t1->prev = t2->prev;
		t2->next = t1Next;
		t2->prev = t1Prev;
	}
	if (t1->prev == 0) head = t1;
	if (t2->prev == 0) head = t2;
	if (t1->prev) t1->prev->next = t1;
	if (t1->next) t1->next->prev = t1;
	if (t2->prev) t2->prev->next = t2;
	if (t2->next) t2->next->prev = t2;
}
void swap(node*&head, int pos1, int pos2)
{
	node *t1 = NULL, *t2 = NULL, *t3 = head;
	if (!t3)
	{
		cout << "list is empty\n";
		return;
	}
	for (int i = 0; i <= pos1 || i <= pos2; i++)
	{
		if (i == pos1) t1 = t3;
		if (i == pos2) t2 = t3;
		if (t3->next) t3 = t3->next;
		else break;
	}
	if (!(t1&&t2))
	{
		cout << "out of range\nt1:" << t1 << "t2:" << t2 << endl;
		return;
	}
	node *t1Prev = t1->prev, *t1Next = t1->next;
	if (t1->next == t2 || t2->next == t1)
	{
		if (t1->next == t2)
		{
			t2->prev = t1->prev;
			t1->next = t2->next;
			t2->next = t1;
			t1->prev = t2;
		}
		else
		{
			t2->next = t1->next;
			t1->prev = t2->prev;
			t1->next = t2;
			t2->prev = t1;
		}
	}
	else
	{
		t1->next = t2->next;
		t1->prev = t2->prev;
		t2->next = t1Next;
		t2->prev = t1Prev;
	}
	if (t1->prev == 0) head = t1;
	if (t2->prev == 0) head = t2;
	if (t1->prev) t1->prev->next = t1;
	if (t1->next) t1->next->prev = t1;
	if (t2->prev) t2->prev->next = t2;
	if (t2->next) t2->next->prev = t2;
}
void readFromFile(node*& head, char* filename)
{
	float a;
	ifstream F;
	F.open(filename);
	if (F.good())
	{
		while (!F.eof())
		{
			a = 0;
			F >> a;
			add(head, a, 100);
		}
	}
}
void remove(node*& head, int a)
{
	node *temp = head;
	while (temp != NULL)
	{
		//cout << "in remove \n value \t next \t\t prev \t\t adress \n" << temp->value << '\t' << temp->next << '\t' << temp->prev << '\t' << temp << endl;
		if (temp->value == a)
		{
			if (temp->prev != NULL)
			{
				temp->prev->next = temp->next;
			}
			else head = temp->next;
			if (temp->next) temp->next->prev = temp->prev;
			delete temp;
			break;
		}
		temp = temp->next;
	}
}
int set(node *&head, int pos, float value)
{
	node *temp = head;
	for (int i = 0; i<pos; i++)
	{
		if (temp->next) temp = temp->next;
		else
		{
			cout << "function set: Invalid index" << endl;
			return -1;
		}
	}
	temp->value = value;
	return 0;
}
float get(node *&head, int pos)
{
	node *temp = head;
	for (int i = 0; i<pos; i++)
	{
		if (temp) temp = temp->next;
		else
		{
			cout << "function set: Invalid index" << endl;
			return nan("");
		}
	}
	return temp->value;
}
void split(node *&head, node *&head2, int pos)
{
	if (pos < 1) return;
	node *temp = head;
	for (int i = 0; i < pos; i++)
	{
		if (temp) temp = temp->next;
		else return;
	}
	temp->prev->next = NULL;
	temp->prev = NULL;
	head2 = temp;
	return;
}
void bubblesort(node *&head)
{
	node last =NULL;
	do
	{
		node *temp = head;
		node *lastCandidate;
		while (temp->next!=last)
		{
			if (temp->value > temp->next->value)
			{
				swap(head, i,i+1);
				lastCandidate = temp->next;
			}
			if (temp->next) temp = temp->next;
			i++;
		}
		last=lastCandidate;
	} while (count);
}
int main()
{
	node *head = NULL, *head2=NULL;
	show(head);
	int i = 100;
	while (1)
	{
		cout << "0: fill randomly; 1:add at given pos; 2:delete of given value; 3:read from file; 4:swap, 5:split, 6:get, 7:set, 8:bubblesort" << endl;
		int n;
		cin >> n;
		cout << endl;
		switch (n)
		{
		case 0:
			cin >> n;
			srand(time(NULL));
			for (int i = 0; i < n; i++)
			{
				add(head, rand() % 900 + 100);
			}
			break;
		case 1:
			cin >> n;
			cout << endl;
			add(head, i, n);
			i++;
			break;
		case 2:
			cin >> n;
			cout << endl;
			remove(head, n);
			break;

		case 3:
			readFromFile(head, "liczby.txt");
			break;

		case 4:
			int pos1, pos2;
			cin >> pos1 >> pos2;
			cout << endl;
			swap(head, pos1, pos2);
			break;
		case 5:
			cin >> n;
			split(head, head, n);
		case 6:
			int pos;
			cin >> pos;
			cout<<get(head, pos)<<endl;
			break;
		case 7:
			float value;
			cin >> pos>>value;
			set(head, pos, value);
			break;
		case 8:
			bubblesort(head);
			break;
		}
		show(head);
	}
	cout << endl;
}
