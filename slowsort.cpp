#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <windows.h>
using namespace std;
bool verbose = 0;
int *tabGlobal=NULL;
int sizeGlobal=0;
void printOnce()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 264);
    for (int t=0; t<sizeGlobal; t++)
    {
        cout<<tabGlobal[t]<<'\t';
    }
    cout<<endl;
}
void printOnce(int *tab, int x)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 264);
    for (int t=0; t<x; t++)
    {
        cout<<tab[t]<<'\t';
    }
    cout<<endl;
}
void prettyPrint(int *tab, int n)
{
    int *temp=tabGlobal;
    while (temp<tab)
    {
        cout<<'\t';
        temp++;
    }
    for (int t=0; t<n; t++)
    {
        cout<<tab[t]<<'\t';
    }
    cout<<endl;
}

void prettyPrint(int *tab, int n, int pivot, int i, int j)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int *temp=tabGlobal;
    while (temp<tab)
    {
        cout<<'\t';
        temp++;
    }
    for (int t=0; t<n; t++)
    {
        if (t<i) SetConsoleTextAttribute(hConsole, 10);//colour green; should be less than tab[pivot]
        else if(t>j) SetConsoleTextAttribute(hConsole, 9);//colour blue; should be more than tab[pivot]
        else if (t==pivot)SetConsoleTextAttribute(hConsole, 12);//colour red; tab[pivot]
        else SetConsoleTextAttribute(hConsole,15);//colour white; no info yet
        cout<<tab[t]<<'\t';
    }
    SetConsoleTextAttribute(hConsole,15);
    cout<<endl;
}

void quicksort(int *tab,int n)
{
    if (verbose)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,15);
        cout<<"\n*******new iteration;n="<<n<<"*******\n";
        printOnce();
    }
    if (n==1)
    {
        if (verbose) prettyPrint(tab,n);
        return;
    }
    if (n==2)
    {
        if (tab[0]>tab[1])
        {
            int temp=tab[0];
            tab[0]=tab[1];
            tab[1]=temp;
        }
        if (verbose) prettyPrint(tab,n);
        return;
    }
    if (n<=0)
    {
        if (verbose) cout<<"\ndun fked up\n";
        return;
    }
    int i=0,j=n-1;
    int pivot=0;
    int temp;
    if (verbose) prettyPrint(tab,n,pivot,i,j);
    do
    {
        while (tab[j]>=tab[pivot])
        {
            if (j>pivot) j--;
            else break;
        }
        temp=tab[j];
        tab[j]=tab[pivot];
        tab[pivot]=temp;
        pivot=j;
        if (i<pivot) i++;
        if (verbose) prettyPrint(tab,n,pivot,i,j);
        if (i==j) break;
        while (tab[i]<=tab[pivot])
        {
            if (i<pivot)i++;
            else break;
        }
        temp=tab[i];
        tab[i]=tab[pivot];
        tab[pivot]=temp;
        pivot=i;
        if (j>pivot) j--;
        if (verbose) prettyPrint(tab,n,pivot,i,j);
    } while (i!=j);
    if (verbose) prettyPrint(tab,n,pivot,i,j);
    if(pivot) quicksort(tab,pivot);
    if (n-pivot-1) quicksort(tab+pivot+1,n-pivot-1);
}
int main()
{
    srand(time(NULL));
    int n=1000000;
    int x=15;
    int okCount=0;
    for (long int i=0; i<n; i++)
    {
        int *tab= new int[x];
        int *tab2=new int[x];//copy of tab; to be used when debugging

        for (int i=0; i<x; i++)
        {
            tab[i]=rand()%89+10;
            tab2[i]=tab[i];
        }
        quicksort(tab,x);
        for (int i=0;i<x-1;i++)
        {
            if (tab[i]>tab[i+1])
            {
                tabGlobal=tab2;
                sizeGlobal=x;
                verbose=1;
                cout<<"Failed; tab:\n";
                printOnce(tab,x);
                cout<<"\nunsorted:\n";
                printOnce(tab2,x);
                quicksort(tab2,x);
                verbose=0;
                cout<<"\n\n enter anything to continue;start with 0 to end\n";
                string n;
                cin>>n;
                if (n[0]=='0') return 0;
                cin.ignore();
                break;
            }
            if (i==x-2) okCount++;
        }
        delete[] tab;
        delete[] tab2;
    }
    cout<<endl<<okCount<<endl;
}
