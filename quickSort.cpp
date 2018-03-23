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
//    if (verbose)
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,15);
//        cout<<"\n*******new iteration;n="<<n<<"*******\n";
//        printOnce();
//    }
    if (n==2)
    {
        if (tab[0]>tab[1])
        {
            int temp=tab[0];
            tab[0]=tab[1];
            tab[1]=temp;
        }
//        if (verbose) prettyPrint(tab,n);
        return;
    }
    int i=0,j=n-1;
    int pivot=tab[rand()%n];
    int temp;
//    if (verbose) prettyPrint(tab,n,pivot,i,j);
    while (i<=j)
    {
        while (tab[j]>=pivot&&j>1) j--;
        while (tab[i]<=pivot&&i<n-1) i++;

        if (i<=j)
        {
            temp=tab[i];
            tab[i]=tab[j];
            tab[j]=temp;
        }
//        if (verbose) prettyPrint(tab,n,pivot,i,j);
    }
    //if (verbose) prettyPrint(tab,n,pivot,i,j);
    if (pivot>1) quicksort(tab,pivot);
    if (n-pivot-1>1) quicksort(tab+pivot+1,n-pivot-1);
}
int main()
{
    srand(time(NULL));
    int x=15;
    int okCount=0;
    int *tab= new int[x];
    int *tab2=new int[x];//copy of tab; to be used when debugging

    for (int i=0; i<x; i++)
    {
        tab[i]=rand()%89+10;
        tab2[i]=tab[i];
    }

    cout<<"arrays created"<<endl;
    time_t t1Start,t1End,t2Start,t2End;

    t2Start=time(NULL);
    sort(tab,tab+x);
    t2End=time(NULL);
    time_t t2=t2End-t2Start;
    cout<<"czas funkcji sort:"<<t2<<endl;

    t1Start=time(NULL);
    quicksort(tab,x);
    t1End=time(NULL);

    time_t t1=t1End-t1Start;
    cout<<"czas mojej funkcji:"<<t1<<endl;
    if (t2) cout<<"t1/t2="<<t1/t2<<endl;
    for (int i=0;i<x-1;i++)
    {
        if (tab[i]>tab[i+1])
        {
            break;
        }
        if (i==x-2) okCount++;
    }
    delete[] tab;
    delete[] tab2;
    cout<<endl<<"ok? "<<okCount<<endl;
}
