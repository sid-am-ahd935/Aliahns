/*
A new way to play the same old game. Hand cricket is a game played by many school kids for fun. It uses the concepts of cricket and played with hands. 
Hand Cricket is a game in which two players show scores on their respective fingers. If the scores are equal, the batsman is declared out. 
Else, the score of the batsman is added to the total runs of the batting team.
*/

#include<bits/stdc++.h>

using namespace std;
int match(int pre_run = INT_MAX);
bool toss(int val);
int main(){
    int bat=0,ball=0;
    cout<<"\n1.Head \n2.Tail\nEnter your choise : ";
    int choise;
    cin>>choise;
    bool win=toss(choise-1);
    if(win==true){
        cout<<"\nYou win the toss.";
        cout<<"\n1.Batting \n2.Balling\nEnter your choise : ";
        cin>>choise;
    }
    else{
        cout<<"\nYou loss the toss.";
        choise=toss(win)+1;
    }
    if(choise==1){
        cout<<"\nIt's your batting first"<<endl;
        bat=match();
        cout<<"\nIt's your balling first"<<endl;
        ball=match(bat);
    }
    else if(choise==2){
        cout<<"\nIt's your balling first"<<endl;
        ball=match();
        cout<<"\nIt's your batting first"<<endl;
        bat=match(ball);
    }
    else{
        cout<<"\nWrong input";
        exit(0);
    }
    if(bat>ball){
        cout<<"\nYou Win! by runs "<<bat-ball;
    }
    else if(bat<ball){
        cout<<"\nYou Loss! by runs "<<ball-bat;
    }
    else{
        cout<<"\nDraw";
    }
}
int match(int pre_run){
    bool flag=true;
    int input,totalRun=0;
    srand(unsigned(time(0)));
    while(flag){
        if(totalRun>pre_run)
            return totalRun;
        else{
            int run=(rand()%6)+1;
            cout<<"\nEnter a number within 6 : ";
            cin>>input;
            try{
                if(input>6 or input<0)
                    throw "\ninvalid input\n";
                else{
                    if(input==run){
                        flag=false;
                        cout<<"\nOut!";
                    }
                    else{
                        totalRun+=input;
                    }
                }
            }
            catch(...){
                cout<<"\nYou are cheating.";
                return totalRun=-1;
            }
        }
    }
    return totalRun;
}
bool toss(int val){
    srand(time(0));
    return rand()%2==val;
}
