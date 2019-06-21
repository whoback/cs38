//hw0
//take in pos ints until -1 entered then exit
//print smallest and largest nums entered
//implement using an array
//implement not using an array
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> //for assert
#include <ctype.h> //for isdigit
#include <math.h> // for min/max
int main()
{
   static int user_input;
   static int num_of_ints;
   static int smallest_int;
   static int largest_int;

        //prompt user for positve int
    while((user_input = getchar()) != -1)
    {
            largest_int = fmax(user_input, largest_int);
            smallest_int = fmin(user_input, smallest_int);
            num_of_ints++;

            printf("Largest: %i \n Smallest: %i \n Total: %i\n", largest_int, smallest_int, num_of_ints);
    }
     
    printf("QED.\n");

    return 0;
}
