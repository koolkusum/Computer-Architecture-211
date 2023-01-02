
#include <ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main (int argc, char **argv)
{   //Notes for self
    //using ASCII values to calculate the values
    //dont change symcbols
    //65 to 90 uppercase
    //97 to 122 lowercase
    if ((argc - 1) != 1) 
    {
		  return 0;
	  } 
    char *input =argv[1];
    char final[1024];
    
    for(int i=0; i<1024;i++)
    {
      char c =input[i];
      if (c >= 65 && c < (65 + 26)) 
      {
      c = 65 + ((c - 65 + 13) % 26);
      }
      if (c >= 97 && c < (97 + 26)) 
      {
      c = 97 + ((c - 97 + 13) % 26);
      }

    final[i]=c;
    }
           final[strlen(input)] = '\0';

	printf("%s\n", final);

	return 0;

}