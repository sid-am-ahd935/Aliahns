#include<iostream>
using namespace std;
//COMPLETE***********************************************
int main(){
	int n;
	
	cout<<"Put the value:";
	cin>>n;


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
