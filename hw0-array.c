#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int arr[3];
int input;
enum dir {SMALL, LARGE, COUNT};

int main()
{
        while((input = fgetc(stdin)) != '\r' && input != '\n' && input != EOF)
        {
                printf("Please enter a positive integer: ");
                // -1 entered should just print out results
                if(input == -1)
                {
                        break;
                }
                if(input < -1)
                {
                        printf("Only positive integers please!\n");
                        break;
                }

                // set SMALL to the very first value otherwise it will be 0
                if(arr[COUNT] == 0)
                {
                        arr[SMALL] = input;
                        arr[COUNT] += 1;
                }
                if(input > arr[LARGE])
                {
                        arr[LARGE] = input;
                        arr[COUNT] += 1;
                }
                if(input < arr[SMALL])
                {
                        arr[SMALL] = input;
                        arr[COUNT] += 1;
                }
        }
        printf("Largest: %i\n Smallest: %i\n Count: %i\n", arr[LARGE], arr[SMALL], arr[COUNT]);
        return 0;
}
