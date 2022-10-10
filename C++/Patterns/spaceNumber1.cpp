#include<iostream>
using namespace std;

int main(){

	int n;
	cout<<"Put the value:";
	cin>>n;


for (int i=1;i<=n;i++)
{
//PRINT SPACES
	for(int j=n-i;j>=1;j--)	
	{
		cout<<" ";	
	}
//PRINT 1ST TRIANGLE
		int ans = 1;
		for(int k=1;k<=i;k++)
		{
			cout<<ans++;

		}
//PRINT 2ND TRIANGLE
      
		for(int l=i-1;1<=l;l--){
			
//	cout<<l;
//	int start=i-1;
//	while(start){
			
			cout<<l;
//	start=start-1;
		}
		cout<<endl;	
		}

		}
		

		
		
