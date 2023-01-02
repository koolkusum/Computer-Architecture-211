/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct gate {
    int *inputptr; 
    int totalnuminputs;
    int *outputptr;
    int totalnumout;  
    int*tofillindex;
    char circuitnode[17];
};


void circuitcntr(int number)
{
    int cntrnum=0;
    for(int i=0; i<number; i++)
    {
        if(i%2==0)
        {
            cntrnum++;
        }
    }
}

void DECODER(int *data, int exp, int *inparray, int *outparray) {
    int count = 0;
    for (int i = 0; i < pow(2, exp); i++) 
    {
        data[outparray[i]] = 0;
    }

    for (int i = 0; i < exp; i++) 
    {
        count = count + data[inparray[i]] * pow(2, exp - i - 1);
    }
    
    data[outparray[count]] = 1;
}


void NOR(int *data, int indexf, int indexs, int indexa){
    data[indexa] = !(data[indexf] || data[indexs]);
}

void AND(int *data, int indexf, int indexs, int indexa){
    data[indexa] = data[indexf] && data[indexs];
}
void MULTIPLEXER(int *data, int exp, int *inparray, int *outparray, int outindex) {
    int counter = 0;
    for (int i = 0; i < exp; i++) {
        counter = counter + data[outparray[i]] * pow(2, exp - i - 1);
    }
    data[outindex] = data[inparray[counter]];
}

void XOR(int *data, int indexf, int indexs, int indexa){
    data[indexa] = data[indexf] ^ data[indexs];
}




int newvalueforarray(int numbs, char **data, char *inputch){
    for(int i = 0; i < numbs; i++){
        if(strcmp(data[i], inputch) == 0){
            return i;
        }
    }
    return -1;
}

int counting(int *data, int numbs){
    for(int i = numbs + 1; i >= 2; i--){
        data[i] = !data[i];
        if(data[i] == 1){
            return 1;
        }
    }
    return 0;
}



int main(int argc, char ** argv){
    
    //not enough inputptr so it returns
    if(argc-1 != 1)
    {
        return 0;
    }

    int originalsize=2;
    //keeps of input count
    int countin = 0; 
    //keeps track of output count
    int countout = 0; 
    //numbers in ecloop gate
    int numinlist = 0; 
    int numty = 0;
    //
    char *inputstrings = (char*)malloc(17 * sizeof(char)); 
    circuitcntr(200*originalsize);
    


    //reading file
    FILE *inputfile;
    inputfile = fopen(argv[1], "r");
    
    //if there was no file
    if(!inputfile)
    {
        return 0;
    }
    //keeps track of size
    int size = 2;
    
    //reading inopt strings
    fscanf(inputfile, "%16s", inputstrings);
    //reading number
    fscanf(inputfile, " %d", &countin);

    //input count plus the size is the new size
    //min is 2 then there can be more if added
    size = size + countin;
    char **truthtable;
    //allocating for truth table data
    truthtable = (char**)malloc(size * sizeof(char*));
    
    //allocationg space fot character for each element of the data
    for(int i = 0; i < size; i++)
    {
        truthtable[i] = (char*) malloc(17 * sizeof(char));
    }

    //first element in truth table is 0
    strcpy(truthtable[0], "0\0");
    //second element in truth table is 1
    strcpy(truthtable[1], "1\0");

    //copy the string from input file into truth table
    for(int i = 0; i < countin; i++)
    {
        fscanf(inputfile, "%16s", inputstrings);
        //inputtng the truth table
        strcpy(truthtable[i + originalsize], inputstrings);
    }
    //second line of input file being read
    //FYI ORDER MATTERS :(
    fscanf(inputfile, "%16s", inputstrings);
    fscanf(inputfile, "%d", &countout);
    
    //new size is is the size +input count+ output count
    size = size + countout;

    //allocationg more space in truth table to hold new variables
    truthtable = realloc(truthtable, size * sizeof(char*));
    
    //allocating for truth table
    for(int i = 0; i < countout; i++)
    {
        truthtable[i + originalsize + countin] = (char*)malloc(17 * sizeof(char));
    }

    //copying the strings into the truth table
    for(int i = 0; i < countout; i++)
    {
        fscanf(inputfile, "%16s", inputstrings);
        strcpy(truthtable[originalsize + countin + i], inputstrings);
    }

    //create struct to hold values of the circuit
    struct gate* gates;
    gates = NULL;
    //until the end of file
    while(!feof(inputfile))
    {
        int countout = 1;
        int inputcount = 2;
        struct gate gate;
        
        gate.totalnuminputs = 0;
        gate.totalnumout = 0; 
        
        numinlist = numinlist + 1;

        fscanf(inputfile, " %s", inputstrings);
        strcpy(gate.circuitnode, inputstrings);

        if(strcmp(inputstrings, "NOT") == 0)
        {
            inputcount = 1;
        }
        else if(strcmp(inputstrings, "DECODER") == 0)
        {
            fscanf(inputfile, "%d" , &inputcount);
            gate.totalnuminputs = inputcount;
            countout = pow(2, inputcount);
        }
        else if(strcmp(inputstrings, "MULTIPLEXER") == 0)
        {
            fscanf(inputfile, "%d", &inputcount);
            gate.totalnumout = inputcount;
            inputcount = pow(2, inputcount);
        }
        else if (strcmp(inputstrings, "PASS") == 0)
        {
            inputcount = 1;
        }        

        gate.inputptr = (int *)malloc(inputcount * sizeof(int));
        gate.tofillindex = (int *)malloc(gate.totalnumout * sizeof(int));
        gate.outputptr = (int *)malloc(countout * sizeof(int));
        
        for(int i = 0; i < inputcount; i++)
        {
            fscanf(inputfile, "%16s", inputstrings);
            gate.inputptr[i] = newvalueforarray(size, truthtable, inputstrings);
        }

        for(int i = 0; i < gate.totalnumout; i++)
        {
            fscanf(inputfile, "%16s", inputstrings);
            gate.tofillindex[i] = newvalueforarray(size, truthtable, inputstrings);
        }

        for(int i = 0; i < countout; i++)
        {
            fscanf(inputfile, "%16s", inputstrings);
            int check = newvalueforarray(size, truthtable, inputstrings);
            if(check != -1)
            {
                gate.outputptr[i] = check;
            }
            else if(check == -1)
            {
                size = size + 1;
                numty = numty + 1;
                truthtable = realloc(truthtable, size * sizeof(char*));
                truthtable[size - 1] = (char*)malloc(17 * sizeof(char));
                strcpy(truthtable[size - 1], inputstrings);
                gate.outputptr[i] = size - 1;
            }
        }

        if(gates)
        {
            
            gates = realloc(gates, numinlist * sizeof(struct gate));
        }
        else 
        {
            gates = (struct gate*)malloc(sizeof(struct gate));
        }
        gates[numinlist - 1] = gate;
        
    }

    int *data;
    data = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        data[i] = 0;
    }
    data[1] = 1;

    while(1){
        for(int i = 0; i < countin; i++){
            printf("%d ", data[i + originalsize]);
        }
        printf("|");

        for(int i = 0; i < numinlist; i++){
            struct gate gate = gates[i];
            if(strcmp(gate.circuitnode, "NOT") == 0){
                data[gate.outputptr[0]] = !data[gate.inputptr[0]];
            }
            else if(strcmp(gate.circuitnode, "OR") == 0){
                data[gate.outputptr[0]] = data[gate.inputptr[0]] || data[gate.inputptr[1]];
            }
            else if(strcmp(gate.circuitnode, "AND") == 0){
                AND(data, gate.inputptr[0], gate.inputptr[1], gate.outputptr[0]);
            }
            else if(strcmp(gate.circuitnode, "NOR") == 0){
                NOR(data, gate.inputptr[0], gate.inputptr[1], gate.outputptr[0]);
            }

            else if(strcmp(gate.circuitnode, "NAND") == 0){
                data[gate.outputptr[0]] = !(data[gate.inputptr[0]] && data[gate.inputptr[1]]);
            }
            else if(strcmp(gate.circuitnode, "XOR") == 0){
                XOR(data, gate.inputptr[0], gate.inputptr[1], gate.outputptr[0]);
            }
            else if(strcmp(gate.circuitnode, "DECODER") == 0){
                DECODER(data, gate.totalnuminputs, gate.inputptr, gate.outputptr);
            }
            else if(strcmp(gate.circuitnode, "MULTIPLEXER") == 0){
                MULTIPLEXER(data, gate.totalnumout, gate.inputptr, gate.tofillindex, gate.outputptr[0]);
            }
            else if(strcmp(gate.circuitnode, "PASS") == 0){
                data[gate.outputptr[0]] = data[gate.inputptr[0]];
            }
            

            
        }

        for(int i = 0; i < countout; i++){
            printf(" %d", data[countin + originalsize + i]);
        }
        printf("\n");

        if(counting(data, countin) != 1){
            break;
        }
    }


      
    for(int i = 0; i < size; i++)
    {
        free(truthtable[i]);
    }
    free(truthtable);

    for(int i = 0; i < numinlist; i++)
    {
        free(gates[i].inputptr);
        free(gates[i].outputptr);
        free(gates[i].tofillindex);
    }
    
    free(gates);
    free(inputstrings);   
    free(data);
     
    fclose(inputfile);
    return 0;
}*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h>
#include <math.h>

//holds more values realted to each gate
struct gate{
    struct gate* next;
    int tempm; 
    char* ops; 
    int inputnum;
    int outputnum; 
    int* inputtedarray; 
    int* outputtedarray; 
    
}; 


struct valueholder{
    char* charactername; 
    int value;
};
//linked list structure to keep track of gates
struct gate* gatecreation() {
    struct gate* createdgate = malloc(sizeof(struct gate)); 
    createdgate -> ops = NULL; 
    createdgate -> next = NULL; 
    return createdgate; 
}

int DECODER(int limitn, struct valueholder* truthtable, int* inputtedarray){
    int dex;  
    int addedtot = 0; 
    for (int i = 0; i < limitn; i++) {
        dex = inputtedarray[i]; 
        addedtot += truthtable[dex].value * (pow(2, limitn - 1 - i)); 
    }
    return addedtot; 
}

int MULTIPLEXER(int n, struct valueholder* truthtable, int* inputtedarray){
    int dex; 
    int addedtot = 0; 
    struct valueholder inputted; 
    int numbs; 
    for (int i = pow(2, n) + 1; i < pow(2,n) + n + 1; i++) {
        dex = inputtedarray[i]; 
        inputted = truthtable[dex]; 
        numbs = inputted.value; 
        addedtot += numbs * (pow(2, pow(2,n) + n - i));  
        
    }

    return inputtedarray[addedtot+1]; 

}
void circuitcntr(int number)
{
    int cntrnum=0;
    for(int i=0; i<number; i++)
    {
        if(i%2==0)
        {
            cntrnum++;
        }
    }
}

int check(struct valueholder* truthtable, int limit) {
    for (int i = 0; i < limit; i++) {
        if (truthtable[i].value == -5) {
            return -5; 
        }
    }

    return 0; 
}

int equivalencecheck(struct valueholder* truthtable, int* inputtedarray, int limit) {
    int dex; 
    for (int i = 0; i < limit; i++) {
        dex = inputtedarray[i]; 
        if (truthtable[dex].value == -5) {
            return -5; 
        }
    }

    return 0; 
}

int indexer(struct valueholder* truthtable, const char* charactername, int limit){
    for (int i = 0; i < limit; i++) {
        char* str = truthtable[i].charactername; 
        if (strcmp(str, charactername) == 0) {
            return i; 
        } 
    }

    return -1; 
}



int main(int argc, char** argv) {
    
    if(argc-1 != 1)
    {
        return 0;
    }
    
    
    FILE *inputfile;

    inputfile = fopen(argv[1], "r");
    if (inputfile == NULL) {
        return 0;
    }

    int originalsize=2;
    int numinp;  
    char* direct = (char*) malloc (17 * sizeof(char)); 
    circuitcntr(originalsize*100);
    fscanf(inputfile, "%16s", direct); 
    fscanf(inputfile, "%d", &numinp); 

    int totnum = numinp + originalsize; 
    struct valueholder* truthtable = (struct valueholder*) malloc ((totnum) * sizeof(struct valueholder)); 
    truthtable[0].charactername = (char*)malloc(17*sizeof(char)); 
    truthtable[1].charactername = (char*)malloc(17*sizeof(char)); 

    strcpy(truthtable[0].charactername, "0\0");
    strcpy(truthtable[1].charactername, "1\0");


    for (int i = originalsize; i < totnum; i++) {
        fscanf(inputfile, "%16s", direct); 
        truthtable[i].charactername = (char*) malloc (17 * sizeof(char)); 
        strcpy(truthtable[i].charactername, direct); 
        truthtable[i].value = -5; 
    }
    int outnum;
    fscanf(inputfile, "%16s", direct); 
    fscanf(inputfile, "%d", &outnum); 
    
    
    struct valueholder* truthtable2; 
    totnum += outnum; 
    truthtable2 = realloc(truthtable, (totnum) * sizeof(struct valueholder)); 
    truthtable = truthtable2;

    for (int i = 0; i < outnum; i++) {
        fscanf(inputfile, "%16s", direct); 
        truthtable[i+numinp+originalsize].charactername = (char*) malloc (17 * sizeof(char)); 
        strcpy(truthtable[i+numinp+originalsize].charactername, direct); 
        truthtable[i+numinp+2].value = -5; 
    }

    int dex; 
    int inpg; 
    struct gate* hd = gatecreation(); 
    struct gate* ptr = hd; 

    while (!feof(inputfile)) {
        struct gate* inputgate = gatecreation();
        inputgate->ops = (char*) malloc (17 * sizeof(char));  
        fscanf(inputfile, "%16s", direct); 
        strcpy(inputgate->ops, direct); 

        if (strcmp(direct, "NOT") == 0 || strcmp(direct, "PASS") == 0) {
            inputgate->inputnum = 1; 
            inputgate->outputnum = 1; 
        }

        else if(strcmp(direct, "MULTIPLEXER") == 0) {
            fscanf(inputfile, "%d", &inpg); 
            inputgate->tempm = inpg; 
            inputgate->inputnum = pow(originalsize, inpg) + inpg + 1; 
            inputgate->outputnum = 1; 
        }

        else if (strcmp(direct, "DECODER") == 0) {
            fscanf(inputfile, "%d", &inpg); 
            inputgate->inputnum = inpg; 
            inputgate->outputnum = pow(originalsize, inpg); 
        }



        else {
            inputgate->inputnum = 2; 
            inputgate->outputnum = 1; 
        }

        inputgate->inputtedarray = (int*)malloc(inputgate->inputnum * sizeof(int)); 
        inputgate->outputtedarray = (int*)malloc(inputgate->outputnum * sizeof(int)); 

        for (int ecloop = 0; ecloop < inputgate->inputnum; ecloop++) {
            if (strcmp(direct,"MULTIPLEXER") == 0 && ecloop == 0) {
                inputgate->inputtedarray[ecloop] = inputgate->tempm; 
            } else {
                fscanf(inputfile, "%16s", direct);
                dex = indexer(truthtable, direct, totnum); 
                if (dex == -1) {
                    truthtable2 = realloc(truthtable, (totnum + 1) * sizeof(struct valueholder)); 
                    truthtable = truthtable2;
                    truthtable[totnum].charactername = (char*) malloc(17 * sizeof(char)); 
                    strcpy(truthtable[totnum].charactername, direct); 
                    truthtable[totnum].value = -5;
                    inputgate->inputtedarray[ecloop] = totnum;
                    totnum = totnum +1 ;  
                } else {
                         inputgate->inputtedarray[ecloop] = dex;
                }
            } 
        }

        for (int b = 0; b < inputgate->outputnum; b++) {
            fscanf(inputfile, "%16s", direct); 
            dex = indexer(truthtable, direct, totnum); 
            if (dex == -1) {
                truthtable2 = realloc(truthtable, (totnum + 1) * sizeof(struct valueholder)); 
                truthtable = truthtable2;
                truthtable[totnum].charactername = (char*) malloc(17 * sizeof(char)); 
                strcpy(truthtable[totnum].charactername, direct); 
                truthtable[totnum].value = -5;
                inputgate->outputtedarray[b] = totnum;
                totnum++ ; 
            } 
            else { 
                inputgate->outputtedarray[b] = dex; 
            }
            }
            ptr-> next = inputgate; 
            ptr = ptr->next; 
        }

    
     
     truthtable[0].value = 0; 
     truthtable[1].value = 1; 
    int numbs = pow(originalsize, numinp); 
     for (int iter = 0; iter < numbs; iter++) {
        for (int pptr = originalsize; pptr < totnum; pptr++) {
            truthtable[pptr].value = -5; 
        }
         int i = iter; 

         if (iter == 0) {
             for (int pptr = 0; pptr < numinp; pptr++) {
                 truthtable[2+pptr].value = 0; 
                 printf("0 ");
             }
         }
         else if (iter != 0) {
             printf("\n"); 
             int n = log2(i); 
         for (int j = 2; numinp + 1 -j > n; j++) {
             truthtable[j].value = 0; 
             printf("0 "); 
         }

         while (n>=0) {
             if (i - pow(originalsize, n) < 0) {
                 truthtable[numinp+1-n].value = 0; 
                 printf("0 "); 
             } else {

                truthtable[numinp+1-n].value = 1; 
                 printf("1 "); 
                 i = i - pow(originalsize,n);
             }
             n--; 
         }
         }

         printf("|"); 

         ptr = hd;
         int value; 

        int checknum = -5; 
        while (checknum == -5) {

            for (ptr = hd -> next; ptr != NULL; ptr = ptr-> next) {

                if (equivalencecheck(truthtable, ptr->inputtedarray, ptr->inputnum) == -5) {
                    continue; 
                }

                else {

                if (strcmp(ptr->ops, "NOT") == 0) {
                value = !(truthtable[ptr->inputtedarray[0]].value); 
                dex = ptr->outputtedarray[0]; 
                truthtable[dex].value = value; 

             } 

             else if (strcmp(ptr->ops, "AND") == 0) {
                 value = truthtable[ptr->inputtedarray[0]].value && truthtable[ptr->inputtedarray[1]].value; 
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = value; 
             }

             else if(strcmp(ptr->ops, "OR") == 0) {
                 value =truthtable[ptr->inputtedarray[0]].value || truthtable[ptr->inputtedarray[1]].value; 
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = value; 

             }
             else if(strcmp(ptr->ops, "XOR") == 0) {
                 value = truthtable[ptr->inputtedarray[0]].value ^ truthtable[ptr->inputtedarray[1]].value; 
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = value; 
             }

             else if(strcmp(ptr->ops, "NAND") == 0) {
                 value = !(truthtable[ptr->inputtedarray[0]].value && truthtable[ptr->inputtedarray[1]].value); 
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = value; 
             }

             else if(strcmp(ptr->ops, "NOR") == 0) {
                 value = !(truthtable[ptr->inputtedarray[0]].value || truthtable[ptr->inputtedarray[1]].value);
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = value; 
             }


             else if(strcmp(ptr->ops, "DECODER") == 0) 
             {
                 value = DECODER(ptr->inputnum, truthtable, ptr->inputtedarray); 

                 for (int k = 0; k < ptr->outputnum; k++) 
                 {
                    dex = ptr->outputtedarray[k]; 
                     if (k == value) {
                         truthtable[dex].value = 1; 
                     } else {
                         truthtable[dex].value = 0; 
                     }
                 }
             }

             else if(strcmp(ptr->ops, "MULTIPLEXER") == 0) 
             {
                 int n = ptr->inputtedarray[0]; 
                 value = MULTIPLEXER(n, truthtable, ptr->inputtedarray); 
                 dex = ptr->outputtedarray[0]; 
                 truthtable[dex].value = truthtable[value].value; 
                 
             } 
             else 
             { 
                dex = ptr->inputtedarray[0]; 
                value = truthtable[dex].value; 
                dex = ptr->outputtedarray[0]; 
                truthtable[dex].value = value; 
             }

                }
            }
            checknum = check(truthtable, totnum); 
            
            
             }
        
         
             
        int output; 
         for (int i = originalsize + numinp; i < originalsize + numinp + outnum; i++) 
         {
             output = truthtable[i].value; 
             printf(" %d", output); 

         }


         }



    for (int i = 0; i < totnum; i++)
    {
        free(truthtable[i].charactername); 
    }

    ptr = hd->next; 
    free(hd); 
    while (ptr != NULL) 
    {
        struct gate* pptr = ptr; 
        free(pptr->ops); 
        free(pptr->inputtedarray); 
        free(pptr->outputtedarray); 
        ptr = ptr -> next; 
        free (pptr);
    }
     free(truthtable);
    free(direct); 
    fclose(inputfile);
    free(ptr); 
    return 0; 
    
}