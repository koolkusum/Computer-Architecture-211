/* file that creates a binary search tree, with functions to add, delete, search, and print*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defining a Node
typedef struct Node {
	int data;
	struct Node* right;
	struct Node* left;
}Node;
//creating the Node that will hold the values
Node* root = NULL;

void FreeBST(Node*root)
{

	if (root==NULL)
	{
		return;
	}
	FreeBST(root->right);
	FreeBST(root->left);
	free(root);
}
 //INSERT NODE//
void Insert (int input) {

	if (root==NULL) 
	{
		//making a new node if tree is empty
        //or is last element to be inserted
		root = (Node *)malloc(sizeof(Node));
		root->right = NULL;
		root->left = NULL;
		root->data = input;
		printf("inserted\n");
		return;
	} 
	//to traverse through tree to find where to insert
    //we are going to use ptr and tptr(trace ptr)
    //tptr just follows ptr
	
	Node * ptr = root;
	Node * tptr = NULL;
	

	//find dupe or insert
	while (ptr!=NULL) 
	{
		//if dupe
		if (ptr->data == input) 
		{
			printf("not inserted\n"); return;
		} 
		//if input is larger than current node move right
		else if (input > ptr->data) 
		{
			tptr = ptr;
			ptr = ptr->right;
		} 
		 //if input is less than current node move left
		else 
		{
			tptr = ptr;
			ptr = ptr->left;
		}

	}
	
	//outside while loop
    //is at the bottom of the tree
    //tptr is the parent before ptr become null
	if (ptr==NULL) 
	{
		//creating a new node
		Node* endNode = (Node *)malloc(sizeof(Node));
		endNode->right = NULL;
		endNode->left = NULL;
		endNode->data = input;
//the input is less than the tptrdata
		if (input < tptr->data) 
		{
			tptr->left = endNode;
		} 
		else {
			tptr->right = endNode;
		}

		printf("inserted\n");
	}

		return;

}

/*method to search for a given value in the tree*/
void search (int input) {

	if (root == NULL) 
	{
		printf("absent\n");
		return;
	}

	Node * ptr = root;

	while (ptr!=NULL) 
	{
		if (ptr->data == input) 
		{
			printf("present\n");
			return;
		} 
		else if (ptr->data < input) 
		{
			ptr = ptr->right;
		} 
		else 
		{
			ptr = ptr->left;
		}
	}

	if (ptr==NULL) 
	{
		printf("absent\n");
	}

	return;

}

/*method to find the left most item in a suubtree
	used when deleting a node with two children*/

int findmin (Node* root) {

	struct Node * ptr = root;

	if (ptr->right==NULL) 
	{
		int data = ptr->data;
		free(ptr);
		return data;
	} 
	else 
	{
		return findmin(ptr->right);
	}
}


/*method to delete a node from the tree*/

void Delete (int input) {
	//the tree is empty
	if (root==NULL) {
		printf("absent\n");
		return;
	}
	//ptr and trace pointer
	Node * ptr=root;
	Node * tptr = NULL;
	//traversing through the tree
	while (ptr!=NULL) {
		//if the ptr is equal to what needs to be dated
		if (ptr->data==input) {

            //CASE 1
            //does not have any children
			if (ptr->left ==NULL && ptr->right == NULL) {
				//if the traceptr in NULL
				if (tptr==NULL) {
					root=NULL;
					free(ptr);
					printf("deleted\n");
					return;
				} else {
                    //if the node is on the left
                    //we need to set the parent node left to null
					if (input < tptr->data) {
						tptr->left = NULL;
						free(ptr);
						printf("deleted\n");
						return;

					} 
					                    
                    //if the node is on the right
                    //we need to set the parent node right to null
					else {
						tptr->right = NULL;
						free(ptr);
						printf("deleted\n");
						return;
					}
				}
			}


            //if theres only a left child
			if (ptr->right !=NULL && ptr->left == NULL) {
				
				//only two elements
				if (tptr==NULL) 
				{
					root = ptr->right;
					free (ptr);
					printf("deleted\n");
					return;
				} 
				else {
					//the trace is bigger than the input
                    //resorting

					if (tptr->data > input) 
					{
						tptr->left = ptr->right;
					}
					else {
						tptr->right = ptr->right;
					}

					free(ptr);
					printf("deleted\n");
					return;
				}
			}

			if (ptr->left !=NULL && ptr->right == NULL) {
				if (tptr==NULL) {
					root = ptr->left;
					free (ptr);
					printf("deleted\n");
					return;
				} else {
					if (tptr->data > input) {
						tptr->left = ptr->left;
					}else {
						tptr->right = ptr->left;
					}
					free(ptr);
					printf("deleted\n");
					return;
				}
			}


			//it has two children then we need to use the function find min
			//this will help find the replacement node so the order maintains
			if(ptr->left!=NULL && ptr->right!= NULL) 
			{
				int newFillIn = findmin(ptr->left);
				ptr->data = newFillIn;
				printf("deleted\n");
				return;
			}


		}
		//traversing throught the tree based on value
		else if (ptr->data>input) 
		{
			tptr = ptr;
			ptr = ptr->left;
		}
		else 
		{
			tptr = ptr;
			ptr = ptr->right;
		}


	}

	/*if the item was not found*/

	printf("absent\n");
	return;


}

/*recursive method to print the binary search tree
	prints a ( followed by the left subtree, followed by the root, then the right subtree*/
void printTree (Node* parent) {

	if (parent==NULL) {
		return;
	}

	printf("(");
	printTree(parent->left);
	printf("%d", parent->data);
	printTree(parent->right);
	printf(")");
	return;

}




int main (int argc, char** argv) {



    //Node *root=NULL;
    
    //nothing inputted
    if (argc != 1) 
    {
		return 0;
	} 

    //take in the inputs
    char variablecharacter;
    int input;

    do{
        if(feof(stdin)){break;}
        //printf("input read %c%d\n", variablecharacter, input);
        //searching if input is s
        if(variablecharacter=='p')
        {
            printTree(root);
            printf("\n");
        }
        else
        {
            scanf("%d",&input);

            if(variablecharacter=='s')
            {
                search(input);
            }
            
            //insert if input is i
            if (variablecharacter=='i')
            {
                //printf("in insert if statement\n");
                Insert(input);
            }
            //delete if input is d
            if (variablecharacter=='d')
            {
                Delete(input);
        
            }

        }


    }while (scanf(" %c", &variablecharacter)!=EOF);
	//free(root);
    //FreeBST(root);
   return EXIT_SUCCESS;
}