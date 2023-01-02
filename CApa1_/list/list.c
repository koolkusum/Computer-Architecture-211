#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node* insert(Node* head, int integer)
{
    Node *prev;
    //when inserting and the linked has nothing in it
    //whatever is being inserted will be the first element
    //and  points to null
    //ex. 1->Null
    //if - else if - else (more efficient)
    //printf("Starting the insert method");
    if (head==NULL)
    {
        head = malloc (sizeof(Node));
        head -> data = integer;
        head -> next = NULL;
        //printf("Returning the insert method");
        return head;
    }

    //first element of the linked list is larger than new 
    //element that is being inseted
    //ex. 2->3->Null
    // i 1
    // 1->2->3->Null
    //insert in front method
    else if ( head -> data > integer)
    {
        //make pointer for new element (error fix this)
        Node *ipointer =malloc(sizeof (Node));
        //pointer data is integer
        ipointer->data = integer;
        ipointer->next = head;
        return ipointer;
        
    }

    //first element is less than integer
    else
    {
        //ptr to traverse linked list to compare
        Node *ptr= head;
        while (ptr!= NULL)
        {
            //taking the scenario when integer already exists
            //in the linked list
            //DO NOT ADD IT just return
            if (ptr->data == integer)
            {
                return head;
            }

            //insert before the ptr because ptr>integer
            else if (ptr->data > integer)
            {
                //pointer to point to integer
                Node *ipointer;
                ipointer = malloc (sizeof(Node));
                ipointer->data=integer;
                ipointer->next=prev->next;
                prev->next =ipointer;
                return head;
            }
            //moving down linked list within while loop
            prev = ptr;
            ptr=ptr->next;
        }
        //
        Node *ipointer;
        ipointer= malloc (sizeof(Node));
        ipointer->data=integer;
        ipointer -> next = NULL;
        prev->next=ipointer;
        return head;
    }
       /* while (head != NULL)
    {
      printf("%d", head->data);
      head = head->next;
    }*/
    //free(head);
    free(prev);
    
}

Node* delete (Node* head, int integer)
{
    //this will help us traverse through the list
    Node* ptr=head;
    Node* prev=head;
    
    //linked list is empty
    if (head==NULL)
    {
        return head;
    }
    
    //first element is the element to be deleted
    if(head->data==integer)
    {
        //returning linked list after first element
        head = head->next;
        free(ptr);
        return head;
    }
    //traversing through linked list to find integer
    while (ptr!=NULL)
    {
        //finds the integer to delete
        if (ptr->data==integer)
        {
            //make previous point to next
            //this maked ptr have nothing point to it
            //when nothing points to ptr then it gets
            //delted from list
            prev->next=ptr->next;
            free(ptr);
            return head;
        }
        //traverse through list in while
        prev=ptr;
        ptr=ptr->next;

    }
   free(ptr);
   return head;
}
//to print the list 
void printlist (Node *head)
{
    Node *ptr= head;
    Node *ptr2 = head;
    int count = 0;
   //i  printf("in print method");
    //first we are going to count how many elements 
    while (ptr!=NULL)
    {
        count++;
        ptr=ptr->next;
    }
    printf("%d :", count);
    //print linked list with the count number
    while (ptr2!=NULL)
    {
        printf (" %d", ptr2->data );
        ptr2=ptr2->next;
    }
    printf("\n");
    free(ptr);
    free(ptr2);

}


//NOTES TO SELF
//DONT FORGET MALLOC AND FREE

int main (int argc, char **argv)
{
   // printf("program started %d\n", argc);
    if (argc != 1) 
    {
		return 0;
	} 
    //basic method
    //check if i or d
    //compare from left to right of existing linked list
    //if first element no need to check
    //use standard input
    //char input;
    char variablecharacter;
    //char inputi = "i";
    //char inputd = "d";
    int integer;
    Node* head=NULL; 
    //int scannedCnt = 0;
    //printf("program started");
  // printf("Scanf Return %d\n" ,scanf("%c %d", &variablecharacter, &integer));
  // printf("\n");
  //char line;
 // scanf("%c \n", &line);
  // scannedCnt = scanf(" %c%d", &variablecharacter, &integer);
   
   // printf ( "zinitial Scanned count is %d \n" , scannedCnt);
   while (scanf(" %c%d", &variablecharacter, &integer)!=EOF){

  
  
   
  //printf("\n");
   // scannedCnt = 2;
    if(variablecharacter=='i')
    {
         // printf( " character: %c\n",variablecharacter );
      head= insert(head,integer);
      //printf ("Completed insert\n");


       
    }
    
    if (variablecharacter=='d')
    {
       head= delete(head,integer);
    }
    printlist(head);
  
   }
  // printf("came out of while loop");
   //printlist(head);
    /*while (head != NULL)
    {
      printf("%d", head->data);
      head = head->next;
    }*/
    Node *freedom =head;
   while(freedom!=NULL)
   {
    Node* temp =freedom;
    freedom=freedom->next;
    free(temp);
    
   }
    return 0;   

}
 