//Notes to self:
// double array two stars!!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
        
        //TRANSPOSE//
//method to transpose a matrix
//returns the tranposed matrix
//inputs: matrix (double array), num of rows, num of columns
double** transpose(double** res, double** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col+1; j++){
            res[j][i] = matrix[i][j];
        }
    }
    return res;
}

        //MULTIPLY//
//this method multiplies two matrices neither of which are vectors
//this will also return a matrix (two stars indicating a double array)
//consider the two matrices (matrix1 with rows1 x columns1) (matrix2 with rows2 x columns2)
//the resulting matrix will be in the dimensions of the resulting matrix: rows1 x columns2
double **multiply (double** outputmatrix, double **matrix1, double **matrix2, int rows1, int columns1, int rows2, int columns2)
{
   
    //with the size of rows1 x columns2
    //printf("in multiply");

    double inputval=0;//product to be inputted
    //like mexp we need a triple nested for loop to multiply
    for (int i = 0; i<rows1; i++)
    {
        for(int j =0; j<columns2; j++)
        {
            inputval=0;
            for (int k =0; k<rows2; k++)
            {
                inputval+=matrix1[i][k]*matrix2[k][j];
            }
            outputmatrix[i][j]=inputval;
            //reset value after inserting to be ready for next input
            
        }
    }


return outputmatrix;

}

        //VECTOR MULTIPLY//
//this method will multiply a vector and a matrix
//the reason we did not include this in multiply is to simplify the pointer situation
//a vector will always have a column of 1 and a variable row
//for this reason the resulting matrix will be rows1 x 1
double *vectorMultiply(double **matrix1, double *matrix2, int rows1, int columns1, int rows2)
{
    //gonna create a temp matrix to return result
    //we need to allocate memory for temp
    double *temp = malloc (rows1*sizeof(double));

    //like we did for multiply we have to initialize all elments in temp to 0
    for (int i =0; i<rows1; i++)
    {
        //making vector
        for (int j=0; j<1; j++)
        {
            temp[i]=0;
        }
    }

    //since there is only one column in vector we only need a double nested for loop
    double inputval=0;
    for(int i=0; i<rows1; i++)
    {
        for(int j=0; j<columns1; j++)
        {
            inputval+=matrix1[i][j]*matrix2[j];
        }
        temp[i]=inputval;
    }
    return temp;
}

        //FREE MATRIX//
//this frees every element of the matrix(double array)
//reversing the way we allocated memory basically
//taken from my mexp code from prev assignment
void freeMatrix(double**matrix, int len){
    for(int i =0 ;i <len; i++)
    {
        free(matrix[i]);
    }
    free (matrix);
}

        //INVERSE MATRIX//
//when multiplying the matrices it will automatically become a square matrix
double **inverse(double** outputmatrix, double **matrix, int len){
    
    //printf("in inverse");

    //the inverse matrix will start off as an identity matrix
    //
    for (int i =0; i<len; i++)
    {
        for(int j=0; j<len; j++)
        {
            if(i==j)
            {
                outputmatrix[i][j]=1;
            }
            else
            {
                outputmatrix[i][j]=0;
            }
        }
    }

 
    /* algo 1 
for 0 to n-1
    f= Mnn
    divide matrix/f
    divide inverse/f
    for n+1 to n-1
        subtract matrix*f  from matrixn
        subtract inverse*f  from inversen
    end for
end for
look at pa 2 for rest im lazy
*/
    double f;
    for(int p =0;p<len;p++)
    {
        f = matrix[p][p];
    //division part
        for (int j= 0; j<len;j++)
        {
            matrix[p][j]=matrix[p][j]/f;
            outputmatrix[p][j]=outputmatrix[p][j]/f;
        }


    //subtraction and multiplication part
        for(int i = p+1;i<len;i++)
        {
            
            f=matrix[i][p];

            for(int j=0;j<len;j++)
            {
                matrix[i][j]=matrix[i][j]-(f*matrix[p][j]);
                outputmatrix[i][j]=outputmatrix[i][j]-(f*outputmatrix[p][j]);
            }
        }
    }
    //subtraction
    for(int p = len-1; p>=0; p--)
    {
        for(int i=p-1; i>=0; i--)
        {
            double f = matrix[i][p];
            
            for(int j=0; j<len; j++)
            {
                matrix[i][j]=matrix[i][j]-(f*matrix[p][j]);
                outputmatrix[i][j]=outputmatrix[i][j]-(f*outputmatrix[p][j]);
            }
        }


    }
   
    return outputmatrix;
}



        //MAIN METHOD//
int main (int argc, char **argv)
{
       // printf("Success");
        
    //check if we are taking two inputs
    //the inputs we should be taking is the train file
    //and the data file
    //if(argc<3)
    //{
    //    return 0;
    //}
    //take in the second and third line
    //the second line being the number of attributes
    //third line being the number of houses
    
    int numofattributes, numofhouses;
    //opening file and reading lines from training files
    FILE *trainingfile, *datafile;
    //taking in file name so we can read int
    trainingfile = fopen(argv[1],"r");
    datafile = fopen(argv[2],"r");
    
    fscanf(trainingfile, "%*s");
    fscanf(trainingfile,"%d\n%d", &numofattributes,&numofhouses);

    ////we have to allocate memory for the number of houses in matrix and vector
    double **matrix= (double**)malloc(numofhouses*sizeof(double*));
    double **vector=(double**)malloc(numofhouses*sizeof(double*));

    for(int i =0; i<numofhouses; i++)
    {
        matrix[i]=malloc((numofattributes+1)*sizeof(double));
        vector[i]=malloc(sizeof(double));
    }
    
    //setting values in matrix and vector from trainingfile
    //we need to add a column of 1s in the front
    for(int i =0; i<numofhouses; i++)
    {
        for(int j =0; j<numofattributes+2; j++)
        {
            if (j==0)
            {
                matrix[i][j]=1;
            }
            else{
                double inputnumber=0;
                fscanf(trainingfile, "%lf,", &inputnumber);
                if(j==numofattributes+1)
                {
                    vector[i][0]=inputnumber;
                    //printf("vector: %lf\n ", vector[i][0]);
                }
                else{
                    matrix[i][j]=inputnumber;
                    //printf("matrix: %lf\n", matrix[i][j]);
                }
            }
        }
    }

        
    //fclose(trainingfile);
    //trainingfile=NULL;
    //printf("went through");
    //allocating memory for all these arrays
    double **transposedmatrix= (double**)malloc(sizeof(double*)*(numofattributes+1));
    double **multipliedtranspose= (double**)malloc(sizeof(double*)*(numofattributes+1));
    double **inversed= (double**)malloc(sizeof(double*)*(numofattributes+1));
    double **multiplyinvtra= (double**)malloc(sizeof(double*)*(numofattributes+1));
    double **multipliedwvector= (double**)malloc(sizeof(double*)*(numofattributes+1));
    for(int i=0; i<numofattributes+1; i++)
    {
        //with size of number of houses
        transposedmatrix[i]= malloc(sizeof(double)*numofhouses);
        multiplyinvtra[i]= malloc(sizeof(double)*numofhouses);
        multipliedwvector[i]= malloc(sizeof(double)*numofhouses);

        //with size of attritibutes
        multipliedtranspose[i]= malloc(sizeof(double)*(numofattributes+1));
        inversed[i]= malloc(sizeof(double)*(numofattributes+1));
    }
    //printf("went through");
    //the equation method perform here
    //sending its own equation back
    
    transposedmatrix=transpose(transposedmatrix,matrix,numofhouses, (numofattributes));
    
    //printf("went through");
    multipliedtranspose=multiply(multipliedtranspose, transposedmatrix, matrix, (numofattributes+1),numofhouses,numofhouses, (numofattributes+1));

    inversed = inverse(inversed,multipliedtranspose,(numofattributes+1));
  
    
    multiplyinvtra =multiply(multiplyinvtra, inversed, transposedmatrix, (numofattributes+1), (numofattributes+1),(numofattributes+1),numofhouses);

    multipliedwvector= multiply(multipliedwvector, multiplyinvtra, vector, (numofattributes+1), numofhouses,numofhouses,1);

    //predicting pricing
    int datainput, row;
    fscanf(datafile, "%*s");
    fscanf(datafile, "%d\n%d", &datainput,&row);
    double finalprice=0;
    for (int i= 0;i<row;i++ )
    {
        finalprice= multipliedwvector[0][0];
        for (int j=0; j<datainput; j++)
        {
            double numb= 0;
            fscanf(datafile, "%lf,", &numb);
            //printf("numb: %lf\n",numb);
            //printf("matrix inputs %f\n",multipliedwvector[j+1][0]);
            finalprice += (multipliedwvector[j + 1][0] * numb);
            //printf("final price :%f", finalprice);
        }
             printf("%0.0lf\n", finalprice);
    }
    

     //fclose(datafile);
     //datafile=NULL;

     freeMatrix(vector,numofhouses);
     freeMatrix(matrix, numofhouses);
     freeMatrix(transposedmatrix,(numofattributes+1)); 
     freeMatrix(multipliedtranspose, (numofattributes+1));
     freeMatrix(inversed,(numofattributes+1));
     freeMatrix(multiplyinvtra,(numofattributes+1));
     freeMatrix(multipliedwvector,(numofattributes+1));
    return 0;
    
}