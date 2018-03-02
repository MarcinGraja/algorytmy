#include <iostream>
#include <fstream>
using namespace std;
struct node
{
	int value;
	node* next=NULL;
	node* prev=NULL;
};
void add(node*& head, int value)
{
	node* Node=new node;
	Node->value = value;
	Node->next = head;
	if (Node->next != NULL)
	{
		Node->next->prev = Node;
	}
	head = Node;
	//cout << "In add \n value \t next \t\t prev \t\t adress \n" << Node->value << '\t' << Node->next << '\t' << Node->prev <<'\t'<< Node<<endl;

}
void add(node*& head, int value, int position)
{
	node* temp=head;
	for (int i = 0; i < position; i++)
	{
		if (temp->next!=NULL) temp=temp->next;
	}
	node* Node = new node;
	Node->value = value;
	//cout<<head->next<<endl;
	Node->next = temp;
	Node->prev=temp->prev;
	if (Node->next != NULL)
	{
		Node->next->prev = Node;
	}
}
void readFromFile(node*& head, char* filename)
{
	int a;
	ifstream F;
	F.open(filename);
	if (F.good())
	{
		while (!F.eof())
		{
		    a=NULL;
			F >> a;
			if (F.tellg()!=-1)add(head, a);
			//cout << a << endl;
		}
	}
}
void remove(node*& head, int a)
{
	node *temp=head;
	while (temp->next!=NULL)
	{
		//cout << "in remove \n value \t next \t\t prev \t\t adress \n" << temp->value << '\t' << temp->next << '\t' << temp->prev << '\t' << temp << endl;
		if (temp->value == a)
		{
			if (temp->prev!=NULL) temp->prev->next = temp->next;
			else head = temp->next;
		}
		temp = temp->next;
	}
}
void show(node* head)
{
	while (head != NULL)
	{
		cout << head->value << endl;
		head = head->next;
	}
}
int main()
{
	node *head=NULL;
	//readFromFile(head, "liczby.txt");
	add(head,5);
	for (int i=0; i<20; i++) add(head,i,i);
	show(head);
	cout << endl;
	//remove(head, 5);
	show(head);
}
