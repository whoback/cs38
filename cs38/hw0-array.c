#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int arr[100];
    enum dir {SMALL, LARGE, COUNT};
    char line[256];
    int i;
    while(true)
    {
        printf("Please enter a positive integer: ");
        if (fgets(line, sizeof(line), stdin)) {
            if (1 == sscanf(line, "%d", &i)) {
                
                // -1 entered should just print out results
                if(i == -1)
                {
                    break;
                }
                if(i < -1)
                {
                    printf("Only positive integers please!\n");
                    break;
                }
                
                // set SMALL to the very first value otherwise it will be 0
                if(arr[COUNT] == 0)
                {
                    arr[SMALL] = i;
                    arr[COUNT] += 1;
                }
                if(i > arr[LARGE])
                {
                    arr[LARGE] = i;
                    arr[COUNT] += 1;
                }
                if(i < arr[SMALL])
                {
                    arr[SMALL] = i;
                    arr[COUNT] += 1;
                }
            }
        }
    }
    printf("Largest: %i\n Smallest: %i\n Count: %i\n", arr[LARGE], arr[SMALL], arr[COUNT]);
    return 0;
}
