#include<iostream>
using namespace std;

int main(){
	int n;
	
	cout<<"Put the value:";
	cin>>n;
	//FIRST TRIANGLE 
	for(int i=0;i<n;i++){
		
		int count1=1;
		
		for(int j=0;j<n-i;j++){
			
			cout<<count1++<<" ";
			
	    }
		//STAR TRIANGLE
		int k=2*i;
		while(k>0){
		cout<<" *";	
		k--;		
		}
	
		//LAST TRIANGLE
		int count2=n;
		
		for(int j=0;j<n-i;j++){
			
			cout<<count2--<<" ";	
		}
			cout<<endl;		
		}
		//LOWER FIRST TRIANGLE 
		for(int i=0;i<n;i++){
		
		int count3=1;
		
		for(int j=0;j<=i;j++){
			
			cout<<count3++<<" ";
			
	    }
	    

		//LOWER STAR TRIANGLE
		int k=8-i-i;
		while(k>0){
		cout<<" *";	
		k--;		
		}

		//LOWER LAST TRIANGLE
		int count4=1;
		
		for(int j=0;j<=i;j++){
			
			cout<<count4++<<" ";
	
		}
	    cout<<endl;	
	
		}
	}
	
