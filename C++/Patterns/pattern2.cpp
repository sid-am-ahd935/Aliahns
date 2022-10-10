#include<iostream>
using namespace std;

int main(){
	int n;
//pattern 2 by number
	cout<<"Put the value:";
	cin>>n;

	for (int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			
			cout<<i<<" ";	
			
		}
		cout<<endl;
		}
	
	return 0;
}
