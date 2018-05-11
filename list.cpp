#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#define debug 1
using namespace std;
struct node
{
	float value;
	node* next = NULL;
	node* prev = NULL;
};
void show(node* head, string indent="")
{
	int i = 0;
	cout << indent;
	while (head != NULL&&i<20)
	{
		cout << head->value << '\t';
		head = head->next;
		i++;
	}
	cout << endl;
	return;
}
void unlink(node *&Node)
{
	if (Node->prev) Node->prev->next = Node->next;
	if (Node->next) Node->next->prev = Node->prev;
	Node->prev = NULL;
	Node->next = NULL;
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
void swap(node *&head, node *t1, node *t2)
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
float get(node *Node)
{
	return Node->value;
}
node *split(node *&head, int pos)
{
	if (pos < 0) return NULL;
	node *temp = head;
	for (int i = 0; i < pos; i++)
	{
		if (temp->next) temp = temp->next;
		else return NULL;
	}
	node *head2 = temp->next;
	if (head2) head2->prev = NULL;
	temp->next = NULL;
	return head2;
}
void bubblesort(node *&head)
{
	node *last = NULL;
	do
	{
		node *temp = head;
		node *lastCandidate = head;
		while (temp->next != last)
		{
			if (temp->value > temp->next->value)
			{
				swap(head, temp, temp->next);
				lastCandidate = temp;
			}
			else if (temp->next) temp = temp->next;
		}
		last = lastCandidate;
	} while (last != head);
}
node *mergesort(node *head1, int n, int iteration)
{
	if (n == 1) return head1;
	node *head2 = split(head1, n / 2 - 1);
	if (head1->next) head1 = mergesort(head1, n / 2, iteration + 1);
	if (head2->next) head2 = mergesort(head2, n / 2 + n % 2, iteration + 1);
	node *sorted = NULL;
	node *tail = NULL;
	while (head1&&head2)
	{
		node *temp = NULL;
		if (head1->value<head2->value)
		{
			temp = head1;
			head1 = head1->next;
			if (head1)head1->prev = NULL;

		}
		else
		{
			temp = head2;
			head2 = head2->next;
			if (head2)head2->prev = NULL;
		}
		if (sorted == NULL)
		{
			temp->next = temp->prev = NULL;
			sorted = temp;
			tail = sorted;
		}
		else
		{
			temp->prev = tail;
			tail = tail->next = temp;
		}
	}
	if (head1)
	{
		head1->prev = tail;
		tail->next = head1;
	}
	else if (head2)
	{
		head2->prev = tail;
		tail->next = head2;
	}
	return sorted;
}
void mergesort(node *&head)
{
	if (head == NULL)
	{
		cout << "mergesort: list empty\n";
		return;
	}
	int n = 1;
	node *temp = head;
	while ((temp = temp->next))  n++;
	head = mergesort(head, n, 1);
}
void insertsort(node *&head)
{
	node *newHead = NULL;
	while (head)
	{
		node *temp = head;
		head = head->next;
		unlink(temp);
		if (newHead == NULL)
		{
			newHead = temp;
		}
		else
		{
			node *temp2 = newHead;
			if (newHead->value > temp->value)
			{
				temp->next = newHead;
				newHead->prev = temp;
				newHead = temp;
				continue;
			}
			else while (temp2->next
				&&temp->value > temp2->next->value)
			{
				temp2 = temp2->next;
			}
			temp->next = temp2->next;
			temp->prev = temp2;
			temp2->next = temp;
		}
	}
	head = newHead;
}
void selectionsort(node *&head)
{
	node *max = NULL;
	node *head2 = NULL;
	while (head)
	{
		float maxValue = head->value;
		node *temp = head;
		while (temp)
		{
			if (temp->value >= maxValue)
			{
				max = temp;
				maxValue = temp->value;
			}
			temp = temp->next;
		}
		if (max == head) head = head->next;
		if (max) unlink(max);
		max->next = head2;
		if (head2) head2->prev = max;
		head2 = max;

	}
	head = head2;
}
void qsadd(node *&head, node *element)
{
	if (!head) head = element;
	else
	{
		element->prev = head;
		element->next = head->next;
		if (head->next) head->next->prev = element;
		head->next = element;
	}
}
node *quicksort(node *head, int iteration)
{
	string indent;
	for (int i = 0; i < iteration; i++) indent += "";
	if (debug)
	{
		cout << indent << "\niteration:" << iteration << ";head:\n";
		show(head, indent);
	}
	if (head->next == NULL)
	{
		if (debug)
		{
			cout << indent << "one element element iteration " << iteration<<endl;
			show(head, indent);
		}
		return head;
	}
	if (head->next->next == NULL)
	{

		if (head->value > head->next->value) swap(head, head, head->next);
		if (debug)
		{
			cout << indent << "two element iteration " << iteration<<endl;
			show(head, indent);
		}
		return head->next;
	}
	node *low = NULL, *mid = NULL, *top = NULL;
	float pivot = head->value;
	node *temp = head;
	node *last = NULL;
	node *lastMid = NULL;
	while (temp)
	{
		node *next = temp->next;
		unlink(temp);
		if (temp->value < pivot) qsadd(low, temp);
		if (temp->value == pivot)
		{
			qsadd(mid, temp);
			if (!mid || mid && !mid->next) lastMid = temp;
			if (!top && !mid->next /*|| mid->next && !mid->next->next*/) last = temp;
		}
		if (temp->value > pivot)
		{
			qsadd(top, temp);
			if (!top || (top && !top->next)) last = temp;
		}
		temp = next;
		/*cout << "\n*****in while*****\nlow:\n";
		show(low, indent);
		cout << "\nmid:\n";
		show(mid, indent);
		cout << "\nhigh:\n";
		show(top, indent);*/
	}
	if (debug)
	{
		cout << indent << "\nlow:\n";
		show(low, indent);
		cout << indent << "\nmid:\n";
		show(mid, indent);
		cout << indent << "\nhigh:\n";
		show(top, indent);
	}
	node *lastLow = NULL;
	if (low)
	{
		lastLow = quicksort(low, iteration + 1);
		lastLow->next = mid;
		mid->prev = lastLow;
	}
	if (top)
	{
		last = quicksort(top,  iteration + 1);
		lastMid->next = top;
		top->prev = lastMid;
	}
	if (debug)
	{
		cout << "\ncombined:\n";
		show(low, indent);
		cout << "end"<<endl;
		return last;
	}
}
void quicksort(node *&head)
{
	head=quicksort(head, 1);
	while (head->prev)	head = head->prev;
	return;
}
int main()
{
	node *head = NULL, *head2 = NULL;
	show(head);
	int i = 100;
	while (1)
	{
		cout << "0: fill randomly; 1:add at given pos; 2:delete of given value; 3:read from file; 4:swap, 5:split, 6:get, 7:set, 8:bubblesort, 9:quicksort, 10:insertsort, 11: selectionsort, 12:mergesort" << endl;
		long int n;
		cin >> n;
		cout << endl;
		switch (n)
		{
		case 0:     //fill random
			cout << "How many numbers:";
			cin >> n;
			srand(time(NULL));
			long int j;
			try
			{
				for (j = 0; j < n; j++)
				{
					add(head, rand() % 900 + 100);
				}
			}
			catch (const std::bad_alloc& e) {
				std::cout << "Allocation failed: " << e.what() << '\n' << "j:" << j << "\n";
			}
			break;
		case 1:     //add at pos
			cout << "Position:";
			cin >> n;
			cout << endl;
			add(head, i, n);
			i++;
			break;
		case 2:     //delete value
			cout << "Value:";
			cin >> n;
			cout << endl;
			remove(head, n);
			break;

		case 3:     //read from file
			readFromFile(head, "liczby.txt");
			break;

		case 4:     //swap
			cout << "Positions:\n";
			int pos1, pos2;
			cin >> pos1 >> pos2;
			cout << endl;
			swap(head, pos1, pos2);
			break;
		case 5:     //split
			cout << "Index of last element in first list:";
			cin >> n;
			head2 = split(head, n);
			break;
		case 6:     //get
			int pos;
			cin >> pos;
			cout << get(head, pos) << endl;
			break;
		case 7:     //set
			float value;
			cin >> pos >> value;
			set(head, pos, value);
			break;
		case 8:     //bubblesort
			bubblesort(head);
			break;
		case 9:
			quicksort(head);
			break;
		case 10:
			insertsort(head);
			break;
		case 11:
			selectionsort(head);
			break;
		case 12:
			mergesort(head);
			break;
		}
		cout << "main loop; heads\n";
		show(head);
		show(head2);
	}
	cout << endl;
}
