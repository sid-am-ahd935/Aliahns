#include<iostream>
using namespace std;

int main(){
	int n;

	cout<<"Put the value:";
	cin>>n;

	for (int i=1;i<=n;i++){
			//int count=n;
		for(int j=1;j<=n;j++){
		 char ans = 'A'+i-1;
		cout<<ans<<" ";
	//	ans++;
		}
		cout<<endl;
		}
	
	return 0;
}
