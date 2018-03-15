#include <iostream>
#include <fstream>
using namespace std;
struct node
{
	int value;
	node* next=NULL;
	node* prev=NULL;
};
void show(node* head)
{
	while (head != NULL)
	{
		cout << head->value << '\t';
		head = head->next;
	}
	cout<<endl;
}
void add(node*& head, int value, int position)//adds element at position. If position<=0 element goes at the start; if position>=number of elements, it goes at the end
{
	node* temp=head;
	if (position<=0||head==0)
    {
        temp=new node;
        temp->value=value;
        temp->next=head;
        if (head) head->prev=temp;
        head=temp;
        return;
    }
    int i=1;
    node* Node = new node;
    Node->value = value;
	while(1)
	{
		if (temp->next!=NULL&&i<position) temp=temp->next;
		else if (temp->next==NULL)
        {
            if (temp->next==0)//adding at the last place in the list
            {
                Node->next=0;
                Node->prev=temp;
                temp->next=Node;
                return;
            }
            Node->next = temp;
            Node->prev=temp->prev;
            temp->prev=Node;
            if (Node->prev) Node->prev->next=Node;
            return;
		}
		else
        {
            Node->next=temp->next;
            Node->prev=temp;
            temp->next=Node;
            Node->next->prev=Node;
            return;
        }
		i++;
	}

}
void add(node*& head, int value)
{
	add(head,value,0);
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
		    a=0;
			F >> a;
			if (F.tellg()!=-1)add(head, a,100);
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
			if (temp->prev!=NULL)
            {
                temp->prev->next = temp->next;

            }
			else head = temp->next;
		}
		temp = temp->next;
	}
}
int main()
{
	node *head=NULL;
    show(head);
    int i=100;
	while (1)
    {
        //cout<<"1:add at given pos; 2:delete at given pos; 3:read from file"<<endl;
        int n=1;
        //cin>>n;
        cout<<endl;
        switch(n)
        {
            case 1:
                cin>>n;
                cout<<endl;
                add(head,i,n);
                show(head);
                i++;
                break;
            case 2:
                cin>>n;
                cout<<endl;
                remove(head, 5);
            case 3:
                readFromFile(head, "liczby.txt");
        }
    }
	cout << endl;
}
