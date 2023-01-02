#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Strat
//make a double array of the matrix once open file
//this should make matrix multiplication ALOT easier
//this doesn't seem very efficient however
//possible other method(?)

void freeMEXP(int **matrix, int len)
{
    for(int i =0; i<len;i++)
    {
        free(matrix[i]);
    }
    free (matrix);
}

int main (int argc, char **argv)
{
    //
    FILE *fp;
    int len,r,i;
    //len is the first input indicating lenxlen matrix
    //no file is inputted
    if (argc -1 !=1)
    {
        return 0;
    }
    //opening input file from terminal
    fp = fopen(argv[1],"r");
    if (!fp) exit(EXIT_FAILURE);
    //len will help us allocate space for the code
    r =fscanf(fp, "%d",&len );
    if (r!=1)exit (EXIT_FAILURE); //if theres no number

    //allocating space for a double array
    //and allocationg another array space to hold athe results
    //temp array to hold on to values while we perform the multiplication
    int **inputarray= malloc (len *sizeof(int*));
    int **resultingarray= malloc (len*sizeof(int*));
    int **temparray= malloc (len*sizeof(int*));

    for (i=0;i<len;i++)
    {
        inputarray[i]=malloc(len*sizeof(int));
        resultingarray[i]=malloc(len*sizeof(int));
        temparray[i]=malloc(len*sizeof(int));
    }

    //making double array
    //input array currently contains the matrix elements read from file
    //NOTE:result array is empty at this point!!!
    int rows;
    int columns;
    for(rows =0; rows<len; rows++)
    {
        for(columns=0; columns<len; columns++)
        {
            fscanf(fp, "%d",&(inputarray[rows][columns]));
            resultingarray[rows][columns]= inputarray[rows][columns];
        }
    }
   
   
    int exponent;
    fscanf(fp, "%d", &exponent);
    //lets start off with the cases if exponent=0 
    //then move onto the multiplication
    
    //when exponent=0 it creates an identity matrix
    if (exponent==0)
    {
        for (i=0;i<len;i++)
        {
            for(int j=0;j<len;j++)
            {
                if(i==j)
                {
                    resultingarray[i][j]=1;
                }
                else
                {
                    resultingarray[i][j]=0;
                }
            }
        }
    }

    //we will now perform the matrix multiplication
    else
    {
    for( int i = 1;i<exponent;i++)
    {
        int inputval=0;
        //these varaibels will help us traverse through the matrices
        
        for(int x=0; x<len; x++)
        {
            for(int y=0; y<len; y++)
            {
                for(int z=0; z<len; z++)
                {
                    //performing the matrix
                    inputval+=inputarray[x][z]*resultingarray[z][y];
                }
                temparray[x][y] =inputval;
                inputval=0;
            }
        }
        //transferring temp elements into result array
        for (int x=0; x<len; x++)
        {
            for(int y=0; y<len; y++)
            {
                resultingarray[x][y]=temparray[x][y];
            }
        }
    
    }
    
   // freeMEXP(temparray,len);
    //freeMEXP(inputarray,len);
    }

      //print the resulting array
    for(int k=0; k<len; k++)
    {
        for(int l=0; l<len; l++)
        {
           printf("%d", resultingarray[k][l]);
           if (l<(len-1))
           {
            printf(" ");
           }
        }
        printf("\n");
    }
    freeMEXP(resultingarray,len);
    freeMEXP(temparray,len);
    freeMEXP(inputarray,len);
    fclose(fp);
    return 0;

}