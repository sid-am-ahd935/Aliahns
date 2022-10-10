#include<iostream>
using namespace std;

int main(){
	int n;
	
	cout<<"Put the value:";
	cin>>n;


for (int i=1;i<=n;i++)
{
	for(int j=n-i;j>=1;j--)	
	{
		cout<<" ";	
	}
	
		for(int k=1;k<=i;k++)
		{
			cout<<" *";
		}
			cout<<endl;
		}
	
		
for (int i=n;1<=i;i--)
{
	for(int j=1;n-i>=j;j++)	
	{
		cout<<" ";	
	}
	
		for(int k=i;k>=1;k--)
		{
			cout<<" *";
		}
			cout<<endl;
		}
		}
		
	
