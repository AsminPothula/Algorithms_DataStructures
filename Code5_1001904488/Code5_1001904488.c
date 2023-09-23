#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX 50

typedef struct
{
    char label[100];
    int distance;
    int previous;
    int visited;
}
Vertex;

void PrintArray(int Adjmatrix[MAX][MAX], int VertexCount)
{
    printf("\n");
    for(int i = 0; i < VertexCount; i++)
    {
        for(int j = 0; j < VertexCount; j++)
        {
            printf("%4d\t", Adjmatrix[i][j]);
        }
        printf("\n");
    }
}

void PrintPath(int totalVerticesInPath, int path[MAX], Vertex VertexLabel[6])
{
    int isFirstVertex = 1;

    while (totalVerticesInPath != -1)
    {
        if (path[totalVerticesInPath] != -1)
        {
            if (!isFirstVertex)
            {
                printf(" -> ");
            }
            printf("%s", VertexLabel[path[totalVerticesInPath]].label);
            isFirstVertex = 0;
        }
        totalVerticesInPath--;
    }
    printf("\n");
} 

void dijkstara(int StartVertexIndex, int VertexCount, int Adjmatrix[MAX][MAX], char startingVertex[100], Vertex VertexLabel[MAX], char endingVertex[6], int EndVertexIndex)
{
    Vertex VertexArray[MAX] = {};
    int path[MAX] = {};
    int CurrentVertex = StartVertexIndex;
    VertexArray[StartVertexIndex].distance = 0;
    VertexArray[StartVertexIndex].previous = -1;
    VertexArray[StartVertexIndex].visited = 1;
    int SmallestVertexIndex = -1;

    for (int i = 0; i < MAX; i++)
    {
        VertexArray[i].distance = INT_MAX;
    }
    VertexArray[StartVertexIndex].distance = 0;

    for (int x = 0; x < VertexCount - 1; x++)
    {
        for (int i = 0; i < VertexCount; i++)
        {
            if (Adjmatrix[CurrentVertex][i] != -1 && !VertexArray[i].visited)
            {
                if (VertexArray[CurrentVertex].distance + Adjmatrix[CurrentVertex][i] < VertexArray[i].distance)
                {
                    VertexArray[i].distance = VertexArray[CurrentVertex].distance + Adjmatrix[CurrentVertex][i];
                    VertexArray[i].previous = CurrentVertex;
                }
            }
        }

        SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        for (int i = 0; i < VertexCount; i++)
        {
            if (!VertexArray[i].visited && VertexArray[i].distance < SmallestVertex)
            {
                SmallestVertex = VertexArray[i].distance;
                SmallestVertexIndex = i;
            }
        }

        CurrentVertex = SmallestVertexIndex;
        VertexArray[CurrentVertex].visited = 1;
    }
    printf("\n");

#ifdef PRINTIT
    printf("\n\n I   \t L   \t D   \t P  \t V\n");
    for (int i = 0; i < VertexCount; i++)
    {
        printf("%2d\t%2s\t%2d\t%2d\t%2d\n", i, VertexLabel[i].label, VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
    }
    printf("\n");
#endif

    path[0] = EndVertexIndex;
    int source = StartVertexIndex;
    int index = 2;
    int totalVerticesInPath = 2;
    int current_vertex;
    printf("\nThe distance from %s to %s is %d and the path is ", VertexLabel[source].label, VertexLabel[EndVertexIndex].label, VertexArray[EndVertexIndex].distance);
    path[1] = VertexArray[EndVertexIndex].previous;
    current_vertex = path[1];

    while (current_vertex != -1)
    {
        path[index] = VertexArray[current_vertex].previous;
        current_vertex = path[index];
        index++;
        totalVerticesInPath++;
    }
    PrintPath(totalVerticesInPath - 1, path, VertexLabel); 
}

int ReadFileIntoArray(int Adjmatrix[MAX][MAX], char *argv[], int *startingVertexIndexPtr, char startingVertex[6], Vertex VertexLabel[MAX], char endingVertex[6], int *endingVertexIndexPtr)
{
    char line[100];
    FILE *file;
    file = fopen(argv[1], "r");
    int i, count = -1, VertexCount = 0, k = 0;
    char *token_1, *token_2;

    if (file == NULL)
    {
        printf("\nFailed to open the file.\n\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL) 
    {
        count++;

        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0'; 
        }

        token_1 = strtok(line, ",");
        strcpy(VertexLabel[k].label, token_1);
        k++;

        if (strcmp(token_1, startingVertex) == 0)
        {
            (*startingVertexIndexPtr) = count;
        }
        if (strcmp(token_1, endingVertex) == 0)
        {
            (*endingVertexIndexPtr) = count;
        }

        int k = 0;
        while (k != 1)
        {
            token_1 = strtok(NULL, ",");
            if (token_1 == NULL)
            {
                k = 1;
            }
            else
            {
                token_2 = strtok(NULL, ",");
                if (token_2 == NULL)
                {
                    k = 1;
                }
                else
                {
                    Adjmatrix[count][atoi(token_1)] = atoi(token_2);
                }
            }
        }
        VertexCount++;
    }

    fseek(file, 0, SEEK_SET); 
    fclose(file);
    return VertexCount;
}

int main(int argc, char* argv[])
{
    int Adjmatrix[MAX][MAX];

    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            Adjmatrix[i][j] = -1;
        }
    }

    int startingVertexIndexPtr, endingVertexIndexPtr;
    char startingVertex[100] = {};
    char endingVertex[100] = {};
    Vertex VertexLabel[MAX];
    int VertexCount = ReadFileIntoArray(Adjmatrix, argv, &startingVertexIndexPtr, startingVertex, VertexLabel, endingVertex, &endingVertexIndexPtr);
    
    #ifdef PRINTIT
    PrintArray(Adjmatrix, VertexCount);
    printf("\n");
    #endif

    printf("What is the starting vertex? ");
    scanf("%s", startingVertex);

    int StartVertexIndex = -1;
    for (int i = 0; i < VertexCount; i++)
    {
        if (strcmp(VertexLabel[i].label, startingVertex) == 0)
        {
            StartVertexIndex = i;
            break;
        }
    }

    if (StartVertexIndex == -1)
    {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    printf("What is the destination vertex? ");
    scanf("%s", endingVertex);

    int EndVertexIndex = -1;
    for (int i = 0; i < VertexCount; i++)
    {
        if (strcmp(VertexLabel[i].label, endingVertex) == 0)
        {
            EndVertexIndex = i;
            break;
        }
    }

    if (EndVertexIndex == -1)
    {
        printf("Invalid ending vertex.\n");
        return 1;
    }

    dijkstara(StartVertexIndex, VertexCount, Adjmatrix, startingVertex, VertexLabel, endingVertex, EndVertexIndex);
    return 0; 
}
