import java.util.*;

class Swap {

        public static void main(String args[]) {
                Scanner sc = new Scanner (System.in);

                System.out.println("Select the method of swapping two numbers.");
                System.out.println("\t 1. Press 1 for + & - method.");
                System.out.println("\t 2. Press 2 for * & / method.");
                System.out.println("\t 3. Press 3 for XOR method.");
                System.out.println("\t 4. Press 4 for single statement method.");
                System.out.println("Enter your choice: ");
                int choice = sc.nextInt();
                
                int a,b;
                System.out.println("Enter 1st no. A:");
                a = sc.nextInt();
                System.out.println("Enter 2nd no. B:");
                b = sc.nextInt();

                switch(choice) {
                        // + & - method
                        case 1: a=a+b;
                                b=a-b;
                                a=a-b;
                                System.out.println("result: "+a+"  "+b);
                                break;
                        // * & / method
                        case 2: a=a*b;
                                b=a/b;
                                a=a/b;
                                System.out.println("result: "+a+"  "+b);
                                break;             
                        // XOR method               
                        case 3: a=a^b;
                                b=a^b;
                                a=a^b;
                                System.out.println("result: "+a+"  "+b);
                                break;        

                        // single statement method          
                        case 4: b=a+b-(a=b);
                                System.out.println("result: "+a+"  "+b);
                                break;

                        default:System.out.println("Invalid choice");             
                                break;

               }

        }


}
