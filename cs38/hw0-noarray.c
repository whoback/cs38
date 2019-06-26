//hw0
//take in pos ints until -1 entered then exit
//print smallest and largest nums entered
//implement using an array
//implement not using an array
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for min/max


static int user_input; 
static int num_of_ints; 
static int smallest_int;
static int largest_int; 
static int i = 1;

int main()
{
    
    //prompt user for positve int
    while(i == 1)
    {
        
        printf("Enter a positive integer: ");
        int prompt = scanf("%i", &user_input);
        if(prompt != 1)
        {
            
            printf("Error! Please enter only positive integers.\n");
            i = 0;
        }
        else if(user_input == -1)
        {
            i = 0;
        }
        else
        {
            largest_int = fmax(user_input, largest_int);
            // set smallest to first entered number otherwise it will
            // always be 0
            if(num_of_ints == 0)
            {
                smallest_int = user_input;
            }
            smallest_int = fmin(user_input, smallest_int);
            num_of_ints++;
        }
    }
    
    printf("Largest: %i \nSmallest: %i \nTotal: %i\n", largest_int, smallest_int, num_of_ints);
    
    return 0;
}
