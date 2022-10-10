#include<iostream>
using namespace std;

int main(){
	int n;

	cout<<"Put the value:";
	cin>>n;

	for (int i=1;i<=n;i++){
		
	int count=1;

	for(int j=1;j<=i;j++){
			
	cout<<count++<<" ";
		}
		cout<<endl;
		}
	
	return 0;
}
