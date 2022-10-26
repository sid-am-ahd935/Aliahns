

import java.util.*;

class Calculator{
            
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
         
        System.out.println("Simple calculator.");
        System.out.println("\t 1. Press 1 for Addition.");
        System.out.println("\t 2. Press 2 for Subtraction.");
        System.out.println("\t 3. Press 3 for Multiplication.");
        System.out.println("\t 4. Press 4 for Division."); 
        System.out.println("\t 5. Press 5 for Remainder."); 
        System.out.println("Enter your choice: ");
        int choice = sc.nextInt();
       
        int a=0,b=0,r=0;
        if(choice <6 && choice >0){
        System.out.println("Enter 1st no. A:");
        a=sc.nextInt();
        System.out.println("Enter 2nd no. B:");
        b=sc.nextInt();
        }
        
            if(choice==1) //For Addition
             {
              r=a+b;
              System.out.println("Addition Result : "+r);
             }
             else if(choice==2) //For Subtraction
             {
              r=a-b;
              System.out.println("Subtraction Result : "+r);
             }
             else if(choice==3) // For Multiplication
             {
              r=a*b;
              System.out.println("Multiplication Result : "+r);
             }
             else if(choice==4) // For Division
             {
              if(b==0){
                        
              if(a==0){

              System.out.println("invalid");

             }
             else{

              System.out.println("infinite");
             }
             }
             else 
             {
              r=a/b;
              System.out.println("Division Result : "+r);
             }
             }
             else if(choice==5) // For Rmainder
             {
              if(b==0){
                        
              if(a==0){
    
              System.out.println("invalid");
    
             }
             else{
    
              System.out.println("infinite");
             }
             }
             else 
             {
              r=a%b;
              System.out.println("Remainder: "+r);
             }
             
             }
             else{
              System.out.println("invalid choice");
             } 
    }

}