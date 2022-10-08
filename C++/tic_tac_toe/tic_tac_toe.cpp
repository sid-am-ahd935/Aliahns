#include <iostream>
#include <stdio.h>
using namespace std;

char tic_tac_toe[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
int row, column, choice;
bool draw = false;
int chance_count = 1;

void display_board(){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++)
      cout << tic_tac_toe[i][j]<<"\t";
    cout<<"\n";
  }
  cout << "\n\n";
}

bool valid_chance(int choice){
  if (choice >=1 && choice <= 9)
    return true;
  return false;
}

bool check_win(){
  for(int i = 0; i < 3; i++){
    if ((tic_tac_toe[i][0] == tic_tac_toe[i][1] && tic_tac_toe[i][0] == tic_tac_toe[i][2]) || \
        (tic_tac_toe[0][i] == tic_tac_toe[1][i] && tic_tac_toe[0][i] == tic_tac_toe[2][i]))
      return true;
    else if ((tic_tac_toe[0][2] == tic_tac_toe[1][1] && tic_tac_toe[0][2] == tic_tac_toe[2][0]) || \
            (tic_tac_toe[0][0] == tic_tac_toe[1][1] && tic_tac_toe[0][0] == tic_tac_toe[2][2]))
      return true;
  }
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(tic_tac_toe[i][j] != 'X' && tic_tac_toe[i][j] != 'O')
        return false;
  draw = true;
  return false;
}

void set_choice(int row, int column){
  if (chance_count%2 == 1)
    tic_tac_toe[row][column] = 'X';
  else
    tic_tac_toe[row][column] = 'O';
}

void player_chance(){
  start:
  if (chance_count%2 == 1)
    cout << "Player 1 [X]\n" << "Choose number: ";
  else
    cout << "Player 2 [O]\n" << "Choose number: ";
  cin >> choice;
  cout << "\n";
  row = (choice - 1)/3;
  column = (choice - 1)%3;
  if (valid_chance(choice) && tic_tac_toe[row][column] != 'X' && tic_tac_toe[row][column] != 'O')
    set_choice(row, column);
  else{
    cout << "Enter a valid choice!\n\n";
    goto start;
  }
}

void game(){
  cout << "------------TIC-TAC-TOE-------------\n\n\n";
  while(true){
    display_board();
    player_chance();
    if (check_win() && chance_count%2 == 1 && draw == false){
      display_board();
      cout << "Player 1 wins!\n";
      break;
    }
    else if (check_win() && chance_count%2 == 0 && draw == false){
      display_board();
      cout << "Player 2 wins!\n";
      break;
    }
    if (draw){
      cout << "It's a draw!\n";
      break;
    }
    chance_count++;
  }
}

int main(){
  game();
  return 0;
}