/* Coding Assignment 2 */
//Asmin Pothula
//1001904488
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#ifdef PRINTARRAY
#include <stdio.h>
#endif

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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

    *arr = (int *)malloc((*lineCount) * sizeof(int));
    
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
    if (argc < 2)
    {
        printf("\nFile must be provided on command line...exiting.\n");
    }
    
    int *arr;
    int lineCount = 0;
    ReadFileandFillArray(argv[1], &arr, &lineCount);

    #ifdef PRINTARRAY
    printf("\n");
    PrintArray(arr, lineCount);
    printf("\n\n");
    #endif

    start = clock();
    insertionSort(arr, lineCount);
    end = clock();

    #ifdef PRINTARRAY
    PrintArray(arr, lineCount);
    printf("\nProcessed %d records\n", lineCount);
    #endif

    printf("\nInsertion Sort = %ld Tics\n\n", end-start);
    free(arr);

    return 0;
}
