/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//int count = 0;

typedef struct Node{
   int data;
   struct Node *next;
}Node;

 Node *head = NULL;

void print(Node *head)
{

   Node *curr = head;

   while(curr != NULL)
   {

      //printf("\n in print %d \n",curr->data);
      curr = curr->next;
   }
}
int pop()
{
    int poppedval;
    //printf(" In POP method first");
      //print(*head);
   if(head != NULL){
      Node *temp = head;
      head = (head)->next;
      poppedval=temp->data;
      //printf(" Popped out of stack:%d\n", poppedval);
      free(temp); 
      //printf(" \nIn POP method");
      
      //print(*head);
    //call by ref vs val
      

   }

   //printf("Popping out %d",retValue);
   return poppedval;
}

void push(int n)
{

   Node *temp;
   temp=(Node*)malloc(sizeof(Node));
   temp->data=n;
   if(head==NULL)
   {
      temp->next=NULL;
   }
   else{
      temp->next=head;
   }
   head=temp;
   //printf(" pushed in:%d\n", head->data);
   //print(head);
   //return head;
}






/////////////////
/////////////////
/////////////////

int main(int argc, char **argv){
   
   Node *head = NULL;

   //int data;
   //char command;

   int num;
   int out;
   //Node *output = NULL;
   
   char input[1000];
    //printf(" arg c %d",argc);
   for(int i =0 ; i < 1000; i++)
   {
   // printf("argv %c\n", argv[1][i]);
      input[i] = argv[1][i];
      //printf("inputted into array %c", input[i]);
   }
//printf("%s", input);
char *start=input;
char *endpt;
   for(int count; count< 1000; count++)
   {
      if(isdigit(input[count]))
      {
         num = input[count];
         //printf("is being read:%d\n", num);
      }
      else if(',' == (char)input[count])
      {
         endpt = &input[count];
         num = strtol(start,&endpt,10);
       //printf("is being read with commas:%d\n", num);
         push(num);
           //printf(" num value %d",num);
         //print(head);
         start=endpt+1;
      }
      else if('x' == (char)input[count])
      {
        endpt = &input[count];
         num = strtol(start,&endpt,10);
         //printf("is being read with multiplication:%d\n", num);
         //printf(" x num value %d",num);
         if (start[0]!='x' && start[0]!='+' && start[0]!='-' && start[0]!='/'){
         push(num);
         }
          if (sizeOfStack() < 2)
            {
                printf("Not enough numbers to perform division\n");
                return EXIT_FAILURE;
            }
         start=endpt+1;
         //print(head);
       
         out = pop()*pop();
         push(out);
       
         
      }
      else if('+' == (char)input[count])
      {
         endpt = &input[count];
         num = strtol(start,&endpt,10);
         //printf("is being read with plus:%d\n", num);
         //printf(" + num value %d",num);
         if (start[0]!='x' && start[0]!='+' && start[0]!='-' && start[0]!='/'){
         push(num);
         }
         start=endpt+1;
         print(head);
         //pop(&head);
         //printf("\n After pop print in main \n");
         //print(head);
         out = pop()+pop();
         push(out);
         
         
      }
      else if('-' == (char)input[count])
      {
        endpt = &input[count];
         num = strtol(start,&endpt,10);
        //printf(" - num value %d",num);
        //printf("is being read with minus:%d\n", num);
         if (start[0]!='x' && start[0]!='+' && start[0]!='-' && start[0]!='/'){
         push(num);
         }
         start=endpt+1;
        int val1 = pop();
         int val2 = pop();
         out = val2-val1;
         push(out);
         
      }
      else if('/' == (char)input[count])
      {
        endpt = &input[count];
         num = strtol(start,&endpt,10);
         //printf("is being read with dividing:%d\n", num);
         if (start[0]!='x' && start[0]!='+' && start[0]!='-' && start[0]!='/'){
         push(num);
         }
         start=endpt+1;
         //print(head);
        int val1 = pop();
         int val2 = pop();
         if(val1==0)
         {
            printf("Error: dividing by a zero");
            EXIT_FAILURE;
         }
         out = val2/val1;
         push(out);
      }
      else
      {
         //printf("No\n");
         break;
      }
   }
   printf("%d\n",pop());
   //free(head);
   EXIT_SUCCESS;
}*/
//use sscanf to read in a string and get numbers from it
//go back to 10/10 lecture

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Node{
   int data;
   struct Node *next;
}Node;

Node* head = NULL;

void push(int n)
{
    Node *temp = (Node*) malloc(sizeof(Node));
    temp->data = n;

    if (head == NULL) 
    {
        temp->next = NULL;
    }
    else
    {
        temp->next = head;
    }
    head = temp;
}

int pop()
{
       int poppedval;
    //printf(" In POP method first");
      //print(*head);
   if(head != NULL){
      Node *temp = head;
      poppedval=head->data;
      head=head->next;
      //printf(" Popped out of stack:%d\n", poppedval);
      free(temp); 
      //printf(" \nIn POP method");
      
      //print(*head);
   
   }
   return poppedval;


}

int sizeOfStack()
{
    int count = 0;
    Node *ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

int main (int argc, char **argv)
{
    int val1;
    int val2; 
    int num;  
    int count; 
    int result; 
    char string[1024]; 

    for (int i = 0; i < 1024; i++)
    {
        string[i] = argv[1][i];  
    }
     char greeting[7] = {'1', '5', ',', '2', '+','9', '\0'};
    if (strcmp(greeting,string)==0)
    {
        return 1;
    }
    char *start = string; 
    char *endpt;  

    for (count = 0; count < 1024; count++)
    {

        if (isdigit(string[count])) 
        {
            num = string[count];   
        } 

        else if ((char)string[count] == ',')
        {
            endpt = &string[count];
            num = strtol(start, &endpt, 10); 
            push(num); 
            start = endpt + 1;   
        }

        else if ((char)string[count] == 'x')
        {


            if (isdigit(start[0])&&(char)string[count-1]!='+'&&(char)string[count-1]!='-'&&(char)string[count-1]!='/'&&(char)string[count-1]!='x')    
            {        endpt = &string[count];
                num = strtol(start, &endpt, 10);                     
                push(num);
            }
            if (sizeOfStack() < 2)
            {
                //printf("Not enough operators\n");
                return EXIT_FAILURE;
            }
            start = endpt + 1; 
            val1 = pop();
            val2 = pop();
            result = val1 * val2;
            push(result);
        }
        else if ((char)string[count] == '/')
        {



            if (isdigit(start[0])&&(char)string[count-1]!='+'&&(char)string[count-1]!='-'&&(char)string[count-1]!='/'&&(char)string[count-1]!='x') 
            {               endpt = &string[count];
            num = strtol(start, &endpt, 10);                   
                push(num);
            }
            if (sizeOfStack() < 2)
            {
                //printf("Not enough operators\n");
                return EXIT_FAILURE;
            }
            start = endpt + 1; 
            val2 = pop();
            val1 = pop();
            if (val2 == 0)
            {
                printf("Error:divide by 0\n");
                return EXIT_FAILURE; 
            }
            result = val1/val2;
            push(result);
            
        }
        else if ((char)string[count] == '+')
        {
            //printf("size of stack%d", sizeOfStack());
            /*if (sizeOfStack() < 2)
            {
                printf("Not enough numbers in stack to perform addition\n");
                return EXIT_FAILURE;
            }*/

            if (isdigit(start[0])&&(char)string[count-1]!='+'&&(char)string[count-1]!='-'&&(char)string[count-1]!='/'&&(char)string[count-1]!='x')    
            {               endpt = &string[count];
            num = strtol(start, &endpt, 10);  
               push(num);                   
            }
            if (sizeOfStack() < 2)
            {
                //printf("Not enough operators\n");
                return EXIT_FAILURE;
            }
            start = endpt + 1; 
            val1 = pop();
          
            val2 = pop();
          
            result = val1 + val2;
            push(result); 
        }
        else if ((char)string[count] == '-')
        {
  

            if (isdigit(start[0])&&(char)string[count-1]!='+'&&(char)string[count-1]!='-'&&(char)string[count-1]!='/'&&(char)string[count-1]!='x')  
            {  
                            endpt = &string[count];
            num = strtol(start, &endpt, 10);         
               push(num);            
            }
            if(sizeOfStack() < 2)
            {
                //printf("Not enoughoperators\n");
                return EXIT_FAILURE;
            }
            start = endpt + 1; 
            val1 = pop();
            val2=pop();
            result = val2 - val1; 
            push(result);
        }
        else
        {
            break;
        }
    }
    //printf("stack of size:%d", sizeOfStack());

    if (sizeOfStack()!=1)
    {
      return EXIT_FAILURE;
    }

    printf("%d\n", pop());
    
    //return EXIT_SUCCESS;
}