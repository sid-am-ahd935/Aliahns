import java.util.*;

class Swap {
        /**
         * @param args
         */
        public static void main(String args[]) {

                Scanner aliul12 = new Scanner (System.in);
                
                                System.out.println("select the method of swapping two numbers");
                                System.out.println("press 1 for + & - method");
                                System.out.println("press 2 for * & / method");
                                System.out.println("press 3 for XOR method");
                                System.out.println("press 4 for single statement method");
                                System.out.println("Enter your choice: ");
                
                     int choice = aliul12.nextInt();
                int a,b;
                System.out.println("Enter 1st no. A:");
               a = aliul12.nextInt();
               System.out.println("Enter 2nd no. B:");
               b = aliul12.nextInt();

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
