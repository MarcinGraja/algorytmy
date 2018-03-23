#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
void quicksort(int *tab,int n)
{
    if (n==1)
    {
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
        return;
    }
    if (n<=0)
    {
        return;
    }
    int i=0,j=n-1;
    int pivot=0;
    int temp;
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
    } while (i+2!=j);
    if(pivot)quicksort(tab,pivot);
    if(n-pivot)quicksort(tab+pivot+1,n-pivot-1);
}
int main()
{
    srand(time(NULL));
    int n=100;
    for (long int i=2; i<n; i++)
    {
        int *tab= new int[i];
        int *tab2=new int[i];

        for (int k=0; k<i; k++)
        {
            tab[k]=rand()%89+10;
            tab2[k]=tab[k];
        }
        quicksort(tab,i);
        sort(tab2,tab2+i);
        for (int j=0;j<i;j++)
        {
            if (tab[j]!=tab2[j])
            {
                for (int j=0; j<i; j++)
                {
                    cout<<tab[j]<<'\t';
                }
                cout<<"\n\n";
                break;
            }
            if (j==n-1) cout<<i<<" ok\n";
        }
        delete[] tab;
        delete[] tab2;
        //for (int j=0; j<100; j+=10)
        //if (n/i==j&&n%i==0) cout <<j<<"%\n";
    }
}
