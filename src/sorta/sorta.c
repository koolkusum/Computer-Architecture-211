#include <stdio.h>
#include <string.h>


int main (int argc, char *argv[])
{
int i;
int j;
 
    //will act as a placeholder when performing the swap
    char *ptr;
    //a for loop to go through all arguments in the command panel
    for (i= 1; i<argc;i++)
    {
        for(j =i+1; j<argc; j++)
        {
            //string 1 is greater than string 2
            if (strcmp(argv[i], argv[j]) > 0) 
            {
                ptr=argv[i];
                argv[i]=argv[j];
                argv[j]=ptr;

            }
        
        }
    }
    for (i = 1; i<argc;i++)
    {
    printf("%s\n", argv[i]);
    }
    return 0;
}