/* Coding Assignment 4 */
//Asmin Pothula
//1001904488
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int A[], int low, int high)
{
    int i, j = 0;

    #if QSM
    int middle = (high+low)/2;
    swap(&A[middle], &A[high]);
    #elif QSRND
    int random = (rand() % (high-low+1)) + low;
    swap(&A[random], &A[high]);
    #endif
    int pivot = A[high];

    i = (low - 1);

    for (j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return (i + 1);
}

void QuickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int ndx = partition(A, low, high);
        QuickSort(A, low, ndx - 1);
        QuickSort(A, ndx + 1, high);
    }
}

void PrintArray(int ArrayToPrint[], int SizeAP)
{
    int i;
    for (i = 0; i < SizeAP; i++)
    {
        printf("%d\n", ArrayToPrint[i]);
    }
}

void ReadFileandFillArray(char *filename, int **arr, int* lineCount)
{
	FILE *file = fopen(filename, "r");
    
    if (file == NULL) 
    {
        printf("\nFailed to open the file.\n\n");
        exit(1);
    }

    char line[50];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        (*lineCount)++;
    }
    fseek(file, 0, SEEK_SET);  // Move the file pointer back to the beginning of the file

    *arr = malloc((*lineCount) * sizeof(int));
    
    int i = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        (*arr)[i] = atoi(line);
        i++;
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    clock_t start, end;
    int num_of_runs = 0;

    if (argc >= 3)
    {
        num_of_runs = atoi(argv[2]);
    }
    else
    {
        printf("\nNumber of runs not specified on the command line...defaulting to 10\n\n");
        num_of_runs = 10;
    }

    if (argc < 2)
    {
        printf("\nFile must be provided on command line...exiting.\n");
    }
    
    long totalTics = 0;
    int lineCount = 0;
    int *arr;

    for (int i = 0; i < num_of_runs; i++)
    {
        lineCount = 0;
        ReadFileandFillArray(argv[1], &arr, &lineCount);

        #ifdef PRINTARRAY
        printf("\n");
        PrintArray(arr, lineCount);
        printf("\n\n");
        #endif

        start = clock();
        QuickSort(arr, 0, lineCount - 1);
        end = clock();


        long tics = end - start;
        printf("Run %d complete : %ld tics\n\n", (i+1), tics);

        #ifdef PRINTARRAY
        printf("\n");
        PrintArray(arr, lineCount);
        printf("\n\n");
        #endif

        totalTics += tics;

        free(arr);
    }

    printf("The average run time for %d runs is %ld \n\n", num_of_runs, (totalTics / num_of_runs));
    

    printf("\nProcessed %d records\n\n", lineCount);

    return 0;
}
