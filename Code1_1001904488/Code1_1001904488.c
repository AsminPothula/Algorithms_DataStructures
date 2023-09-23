/* Coding Assignment 1 */
//Asmin Pothula
//1001904488
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#ifdef PRINT
#include <stdio.h>
#endif

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
    new_node->number = Number;
    new_node->next_ptr = NULL;

	// if head pointer is NULL, put new node address in it
	if (*LinkedListHead == NULL)
    {
        *LinkedListHead = new_node;
        return;
    }

	NODE *temp = *LinkedListHead;
    while (temp->next_ptr != NULL)
    {
        temp = temp->next_ptr;
    }
	temp->next_ptr = new_node;
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
	FILE *file = fopen(argv[1], "r");

	int count = 0, sum = 0, num = 0;
    char line[50];

    while(fgets(line, sizeof(line), file) != NULL)
    {
        num = atoi(line);
        AddNodeToLL(num, LLH);
        
		sum += num;
		count++;
    }
    fclose(file);
    printf("\n%d records were read for a total sum of %d.\n", count, sum);
}

void PrintLL(NODE *LLH) 
{ 
	NODE *temp = LLH;

    while (temp != NULL)
    {
        printf("%p  %d  %p\n", temp, temp->number, temp->next_ptr);
        temp = temp->next_ptr;
    }

}

void FreeLL(NODE **LLH) 
{ 
	NODE *temp = *LLH, *curr;
    int count = 0, sum = 0;

    while (temp != NULL)
    {
        curr = temp;
        temp = temp->next_ptr;

        sum += curr->number;
		count++;
       
        #ifdef PRINT
        printf("\nFreeing %p  %d  %p.\n", curr, curr->number, curr->next_ptr);
        #endif
        
        free(curr);
    }
    *LLH = NULL;
    printf("\n%d nodes were deleted for a total sum of %d.\n", count, sum);
}

int main(int argc, char *argv[]) 
{ 
    if (argc < 2)
    {
        printf("\nFile must be provided on command line...exiting.\n");
        return 0;
    }

    NODE *LLH = NULL;
	clock_t start, end;
	
	/* capture the clock in a start time */
	start = clock();
	ReadFileIntoLL(argc, argv, &LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to write the file into the linked list\n", end-start);

	#ifdef PRINT
	/* capture the clock in a start time */
    start = clock();
    PrintLL(LLH);
	/* capture the clock in an end time */
    end = clock();
    printf("\n%ld tics to print the linked list\n", end-start);
	#endif
	
	/* capture the clock in a start time */
	start = clock();
	FreeLL(&LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to free the linked list\n", end-start);
	
	return 0; 
} 
