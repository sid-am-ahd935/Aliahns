if __name__ == '__main__':
    h = int(input("Enter height of pyramid :"))
    print("The hollow pyramid is given below:-\n")
    for i in range(1,h+1):
        for j in range(h-i):
            print(" ",end="")
        for j in range(1,2*i-1+1):
            if(i==h):
                print("*",end="")
            else:
                if(j==1 or j==2*i-1):
                    print("*",end="")
                else:
                    print(" ",end="")
        print()

