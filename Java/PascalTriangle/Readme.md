Pascal’s triangle is a pattern of the triangle which is based on nCr.below is the pictorial representation of Pascal’s triangle.

Example:

Input : N = 5
Output:
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
Approach #1:

nCr formula:

n ! / ( n – r ) ! r !

After using nCr formula, the pictorial representation becomes:

           0C0
        1C0   1C1
     2C0   2C1   2C2

3C0 3C1 3C2 3C3
Algorithm:

Take a number of rows to be printed, assume it to be n
Make outer iteration i from 0 to n times to print the rows.
Make inner iteration for j from 0 to (N – 1).
Print single blank space ” “
Close inner loop (j loop) //it’s needed for left spacing
Make inner iteration for j from 0 to i.
Print nCr of i and j.
Close inner loop.
Print newline character (\n) after each inner iteration.
Below is the implementation of the above approach:
