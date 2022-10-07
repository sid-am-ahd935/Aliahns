import random

print('Welcome to Your Password Generator')

chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()_+0123456789'

number = input('Amount of Passwords to Generate: ')
number = int(number)

length = input('Input your password length: ')
length = int(length)

print('\nHere are your passwords:')

for pwd in range(number):
    password = ''
    for c in range(length):
        password += random.choice(chars)
    print(password)