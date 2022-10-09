import random
from pyfiglet import figlet_format

# 1 means ROCK
# 2 means PAPER
# 3 means SCISSOR

dict_c = {1:'ROCK', 2:'PAPER', 3:'SCISSOR'}
#dict_c = dictionary for convention

dict_r = {'12':2, '21':2,
        '13':1, '31':1,
        '23':3, '32':3}
#dict_r = dictionary that determines result

#__main__
while(1):
    print("Press :- ",
          "\n\t1 for ROCK",
          "\n\t2 for PAPER",
          "\n\t3 for SCISSOR",
          "\n\tany other to exit.")
    a=int(input("Enter your choice = "))

    if(a<4):
        b=random.randint(1,3)
        if(str(a)==str(b)):
            print("Draw happened.")
        else:
            print("Computer choose = ", dict_c[b])
            final = dict_r[str(a)+str(b)]
            if(final==a):
                print("You win...","\U0001F973")
            else:
                print("Oops!!..Computer won, better luck next time.")
                
        choice = input("Want to play more ? (y/n) = ")
        if(choice.lower()=='y'):
            continue
        else:
            print()
            print(figlet_format("Come Back Again Chief", font="digital") )
            break
        
    else:
        print()
        print(figlet_format("Come Back Again Chief", font="digital") )
        break
