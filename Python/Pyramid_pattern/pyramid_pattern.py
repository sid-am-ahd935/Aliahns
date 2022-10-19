'''
The below code id used to create a pyramid pattern. i.e. either a hollow or
filled sort of equilateral triangle with symbol as the user enters🔺.

Code has been kept simple yet rich in features , quite customizable.

'''

def Hollow(h,ele):
    print("The hollow pyramid is given below:-\n")
    ln = len(ele)
    for i in range(1,h+1):
        for j in range(h-i):
            print(" "*ln,end="")
        for j in range(1,2*i-1+1):
            if(i==h):
                print(ele,end="")
            else:
                if(j==1 or j==2*i-1):
                    print(ele,end="")
                else:
                    print(" "*ln,end="")
        print()


def Filled(h,ele):
    print("The Filled pyramid is given below:-\n")
    ln = len(ele)
    for i in range(1,h+1):
        for j in range(h-i):
            print(" "*ln,end="")
        for j in range(1,2*i-1+1):
                print(ele,end="")
        print()




if __name__ == '__main__':
    while(1):
        #enter height of pyramid
        h = int(input("\n\n\nEnter height of pyramid(Enter 0 or less to break the loop) :"))
        if(h <= 0):
            break;
        #choose either to print hollow or filled pyramid
        ch = ''
        while(ch not in ['1','2']):
            ch = input("Press\n1. Hollow Pyramid\n2. Filled Pyramid\nEnter your choice : ")
            if(ch not in ['1','2'] ):
                print("\nWrong choice!!!\n")
    
        #enter desired character to print
        ele = input("Enter the character(s) you want you pattern to be made of : ")
    
        if(ch=='1'):
            Hollow(h,ele)
        else:
            Filled(h,ele)

    
