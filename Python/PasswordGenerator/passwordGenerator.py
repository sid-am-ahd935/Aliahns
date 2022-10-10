from tkinter import messagebox
import tkinter as tk
from tkinter import simpledialog
import random

def main():
    # used to display a message box on the screen
    messagebox.showinfo("Information","Welcome to Your Password Generator")
    
    #Create an instance of tkinter frame or window
    application_window = tk.Tk()
    
    # A string of all of the characters that can be used for a single password
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+0123456789'

    # using simpledialog to ask for an integer number from the user
    number = simpledialog.askinteger("Input", "Amount of Passwords to Generate: ",
                                    parent=application_window,                                 
                                    minvalue=0, maxvalue=100)
    
    # converting to int type
    number = int(number)

    # using a simpledialog to ask for an integer number from the user
    length = simpledialog.askinteger("Input", "Input your password length: ",
                                    parent=application_window,
                                    minvalue=0, maxvalue=100)
    
    #converting to int type
    length = int(length)

    # another dialog to show a piece of text
    messagebox.showinfo("Information","\nHere are your passwords:")

    # main logic
    for pwd in range(number):
        password = ''
        for c in range(length):
            password += random.choice(chars)
        messagebox.showinfo("Information",password)

    # close the window when everything is done
    application_window.withdraw()


if __name__ == "__main__":
    main()
