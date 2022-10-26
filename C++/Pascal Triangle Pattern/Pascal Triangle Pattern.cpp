#include <iostream>

using namespace std;

int main()
{
     int n;
     cout<<"Enter the no. of Rows: ";
     cin>>n;
     for(int i=0;i<n;i++)
        {
         int num=1;
         for(int j=0;j<n-i;j++)
         {
         cout<<" ";
         }
         for(int k=0;k<=i;k++)
         {
            cout<<num<<" ";
            num=num*(i-k)/(k+1);
         }
         cout<<endl;
        }
       return 0;
}