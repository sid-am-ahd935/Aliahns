#creating the secret word that player wants to guess
# secretWord = "dictionary"
import random 
import json

with open('dictionary.txt', 'r') as f:
    word_list = json.loads(f.read())

secretWord = random.choice(word_list)
lettersGuessed = ""

# The number of turns before the player loses
# we can ask users whether they play in easy or medium or hard mode and
# set this count accordingly
print('Choose your playing Mode:')
mode = int(input("1. Easy   2. Medium    3. Hard\n"))
if(mode==1):
    failureCount = 10
elif mode==2:
    failureCount = 6
elif mode==3:
    failureCount = 3    
else:
    failureCount = 5
    print('Default selected.')    

# loop until failureCount decreases to zero
while failureCount > 0:
    #take letters input
    guess = input("\t| Enter a letter: ")  

    if guess in secretWord:
        print(f"Correct! There is one or more {guess} present in Secret Word\n")
    else:
        failureCount -= 1
        print(f"Incorrect! There are no {guess} present in the Secret Word.\n {failureCount} turn(s) left.\n")

    # storing already guessed letters
    lettersGuessed = lettersGuessed + guess

    wrongLetterCount = 0
    for letter in secretWord:
        if letter in lettersGuessed:
            print(f"{letter}",end="")
        else:
            print("_",end="") 
            wrongLetterCount += 1  

    # if there is no wrong letters
    if wrongLetterCount == 0:
        print(f"\tYou cracked it! Congratulations..") 
        break #to end while

else:
    print(f"\tThe Secret Word was {secretWord}. ")