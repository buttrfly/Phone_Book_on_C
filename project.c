/*  TODO

    define 2 objectives - 2 main parts of application or 2 ultimate goals(simplicity&stability)

    find a way to link search with actual nodes

    add - something
    load - from strload
    delete - make it work
    save - from A3 or something
    sort - ICE_10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
	char fName[30];
    char lName[30];
    char number[10];
	struct node* next; // the next pointer
}Node, *NodePtr;

// make a new node
NodePtr makeNode(char *fn, char *ln, char *p){
	// allocate memory
	NodePtr np= (NodePtr) malloc(sizeof(Node));
	strcpy(np->fName,fn);
    strcpy(np->lName,ln);
    strcpy(np->number,p);
	np->next=NULL;
	return np;
}

int search( char name[], Node all[],int max){
	for(int i=0;i<max;i++)
		if(strcmp(name,all[i].fName)==0) // found it
			return i;
	return -1;
}

void load(char filename[10],Node container[]){
	// create temp variables to keep a single customer
	char firstName[10], lastName[10], num[10];
	int counter=0;
	// declare a file pointer
	FILE* input = fopen(filename,"r+");
	// check if the file opened successfully
	if(input==NULL) perror("Error opening the file");
	else{
		// continue in reading till the End of FIle
	 	while(!feof(input)){
             printf("count: %d\n",counter);
			strcpy(firstName,"");
			fscanf(input,"%s %s %s",firstName,lastName,&num);
            if(strcmp(firstName,"")!=0){
				// a record has been found in the file
				strcpy(container[counter].fName,firstName);
                strcpy(container[counter].lName,lastName);
                printf("name in damn list: %s %s\n",container[counter].fName,container[counter].lName);
				strcpy(container[counter].number,num);
                printf("number in fucking list: %s\n",container[counter].number);
				counter++;
			}
		}
		fclose(input);
		printf("\nRecords have been loaded into the memory");

	}
}

int listLength(NodePtr np)
{
  int size = 0;

  while (np != NULL)
  {
    ++size;
    np = np->next;
  }

  return size;
}

void printNode(Node c){
	printf("Name: %s %s\n Phone: %s\n",c.fName, c.lName, c.number);
}

//function to print linked list
void printList(NodePtr np){
	if(np!=NULL){
		printf("\nThe customers stored in the linked list are:\n");
		while(np!=NULL){ // as long as there's a node
			printf("Name: %s %s\n",np->fName,np->lName);
			printf("Number: %s\n",np->number);
			np=np->next;    // go on to the next node
		}
    }
}

/* FIND THE WAY TO FIX
void remove(NodePtr cur){
    if( cur!=NULL){
        old=cur; // save the node to be deleted
        cur=cur->next;
        free(old);
    }
}
*/

int main()
{
    int i=1;
	char *fname[30], *number[10], *lname[30];
	NodePtr first, np, last;
	// set the first pointer to NULL to indicate it's empty
	first=NULL;
    
    Node myNodes[50];
    
    load("bookData",myNodes);
    printList(myNodes);
    printf("Records: %d",listLength(myNodes));
	// read the first number
	while(true){
    printf("Record#%d\nEnter the first name: ",i);
	scanf("%s",&fname);
	if (strcmp(*fname,"end")==0) {
		printList(first);
		return 0;
	}else{
        printf("Record#%d\nEnter the last name: ",i);
	    scanf("%s",&lname);
		printf("Enter the number: ");
		scanf("%s",&number);
		//create a node for this data
		np=makeNode(*fname,*lname,*number);
		np->next=NULL;
		if(first==NULL)
			first=np; //make first to point to the new node
		else{
			// make the new node to point to the current first node
			np->next=first;
			first=np;
		}
		i++;
	}

    // call search function
	printf("*****************Search****************\n");
	//get the name from the user
	char fName[30];
	printf("Enter a name to be searched \n ");
	gets(fName); // read the name from the keyboard
	// and keep it into fName;

	// call the search
	int loc=-1; // loc is used to keep the return value of the search
	// it has been set to -1 that indicates not found

	//loc=search(fName,/*NodeName*/,3);

    if(loc!=-1)
		printNode(myNodes[loc]);
	else
		printf("\n Not Found");

  }

	return 0;
}