/* Coding Assignment 2 */
//Asmin Pothula
//1001904488
#include <stdlib.h> 
#include <stdio.h>
#include <time.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {       
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        //int m = l + (r - l) / 2;
        int m = (l+r)/2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
 
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
    mergeSort(arr, 0, lineCount - 1);
    end = clock();

    int mergeSortTime = end - start;

    #ifdef PRINTARRAY
    printf("\n");
    PrintArray(arr, lineCount);
    printf("\n\n");
    #endif
    
    //printf("\nProcessed %d records\n", lineCount);
    //printf("\nMerge Sort = %ld Tics\n\n", end-start);

    free(arr);
    lineCount = 0; 
    ReadFileandFillArray(argv[1], &arr, &lineCount);

    #ifdef PRINTARRAY
    printf("\n");
    PrintArray(arr, lineCount);
    printf("\n\n");
    #endif

    start = clock();
    insertionSort(arr, lineCount);
    end = clock();

    int insertionSortTime = end - start;

    #ifdef PRINTARRAY
    printf("\n");
    PrintArray(arr, lineCount);
    printf("\n\n");
    #endif
   
    printf("\nProcessed %d records\n", lineCount);
    printf("Merge Sort     = %d\n", mergeSortTime);
    printf("Insertion Sort = %d\n\n", insertionSortTime);
    free(arr);

    return 0;
}
