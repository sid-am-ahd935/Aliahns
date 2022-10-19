/* 
* This program generates a password of specified length
*/

import java.util.Random;
class App {

    // All the capital letters
    static final char ALPHA_CAPS[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
            'W', 'X', 'Y', 'Z'
    };
    
    // All the small letters
    static final char ALPHA_LOWER[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
            'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z'
    };

    //All the numeric characters
    static final char NUMERIC[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    //All the special characters
    static final char SPECIAL[] = { '!', '@', '#', '$', '%', '^', '&', '*', '|', ';', ':' };

    // All characters
    static final char ALL_CHARS[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
            'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
            'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            '!', '@', '#', '$', '%', '^', '&', '*', '|', ';', ':'
    };

    public static void main(String[] args) {
        System.out.println("Random password generator in Java");
        System.out.println(generatePassword(8));
        System.out.println(generatePassword(14));
        System.out.println(generatePassword(3));
        System.out.println(generatePassword(10));
        System.out.println(generatePassword(9));

    }

    /* 
     * Password generating function
     * Input: Password length
     * Output: Password string
     */

    private static String generatePassword(int length) {
        // Assert that given length is that greater than 3
        if (length < 4) {
            System.out.print("Length of Password to generate must be greater than 3");
            return "";
        }

        char password[] = new char[length];
        
        // Random number generator
        Random random = new Random();

        // Generate at least one character of each type
        password[0] = ALPHA_CAPS[random.nextInt(ALPHA_CAPS.length)];
        password[1] = ALPHA_LOWER[random.nextInt(ALPHA_LOWER.length)];
        password[2] = NUMERIC[random.nextInt(NUMERIC.length)];
        password[3] = SPECIAL[random.nextInt(SPECIAL.length)];

        // Generate remaining number of characters
        for (int i = 4; i < length; i++) {
            password[i] = ALL_CHARS[random.nextInt(ALL_CHARS.length)];
        }

        // Shuffling all the characters
        for (int i = 0; i < password.length; i++) {
            int r = random.nextInt(password.length);
            char temp = password[r];
            password[r] = password[i];
            password[i] = temp;
        }

        // Create the string from password arr
        return new String(password);

    }
}