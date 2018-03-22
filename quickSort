#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void quicksort(int *tab,int n)
{
    if (n==1)
    {
        cout<<"<quicksort>:last element:"<<tab[0]<<"\n"<<tab<<endl;
        return;
    }
    if (n<=0)
    {
        cout<<"zjebalem\n";
        return;
    }
    int i=0,j=n-1;
    int pivot=0;
    int temp=-1;
    while (i!=j)
    {
        if (j<=pivot&&i>=pivot)
        {
            temp=j;
            j=i;
            i=temp;
        }
        while (tab[j]>=tab[pivot]&&j>=pivot)
        {
            if (j>0) j--;
        }
        temp=tab[j];
        tab[j]=tab[pivot];
        tab[pivot]=temp;
        pivot=j;
        if (i==j) break;
        while (tab[i]<=tab[pivot]&&i<=pivot)
        {
            if (i<n-1)i++;
        }
        temp=tab[i];
        tab[i]=tab[pivot];
        tab[pivot]=temp;
        pivot=i;
    }
    cout<<"<quicksort>:tab["<<n<<"]\t"<<tab<<"\n";
    for (int k=0; k<n; k++)
    {
        cout<<tab[k]<<'\t';
    }
    cout<<"\n\nend of writing\n\n";
    if(pivot)quicksort(tab,pivot);
    if(n-pivot)quicksort(tab+pivot+1,n-pivot);
}
int main()
{
    int n=1;
    while(n)
    {
        cout<<"give n:"<<endl;
        cin>>n;
        if (!n) break;
        int *tab= new int[n];
        srand(time(NULL));
        for (int i=0; i<n; i++)
        {
            tab[i]=rand()%89+10;
            cout<<tab[i]<<'\t';
        }
        cout<<"\n\nend of writing\n\n";
        quicksort(tab,n);
        cout<<"sorted:\n";
        for (int i=0; i<n; i++)
        {
            cout<<tab[i]<<'\t';
        }
        cout<<endl;
        delete tab;
    }
}
