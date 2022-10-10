#include<iostream>
using namespace std;



int main(){
	int n;

	cout<<"Put the value:";
	cin>>n;

	for (int i=1;i<=n;i++){
	
		for(int j=1;j<=i;j++){
			
		char count = 'A'+i-1;
		
		cout<<count<<" ";
		 
		//count++;
		}
		cout<<endl;
		}
	
	return 0;
}
