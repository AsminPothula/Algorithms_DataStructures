// Coding Assignment 6 - [Your Name] - [Your Student ID]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASHTABLESIZE 1

/* Node for storing information */
typedef struct DisneyCharacter
{
    char *name;
    char *movie;
    char gender;
    float movieCollections;
    int debutYear;
    int numberOfSongs;
    struct DisneyCharacter *next_ptr;
}
DISNEY_CHARACTER;

/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
    int HashIndex = 0;

    for (int i = 0; i < strlen(key); i++)
    {
        HashIndex += key[i];
    }

    return HashIndex %= HASHTABLESIZE;
}

void AddNode(DISNEY_CHARACTER *NewNode, DISNEY_CHARACTER *CharacterRegistry[])
{
    int HashIndex = CalculateHashIndex(NewNode->name);

    /* a linked list does not exist for this cell of the array */
    if (CharacterRegistry[HashIndex] == NULL)
    {
        #if PRINTINSERT
        printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
        #endif
        CharacterRegistry[HashIndex] = NewNode;
    }
    else /* A Linked List is present at given index of Hash Table */
    {
        DISNEY_CHARACTER *TempPtr = CharacterRegistry[HashIndex];

        /* Traverse linked list */
        while (TempPtr->next_ptr != NULL)
        {
            TempPtr = TempPtr->next_ptr;
        }
        TempPtr->next_ptr = NewNode;
        #if PRINTINSERT
        printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
        #endif
    }
}

void FreeDynamicMemory(DISNEY_CHARACTER *CharacterRegistry[])
{
    DISNEY_CHARACTER *TempPtr = NULL, *NextPtr = NULL;

    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        TempPtr = CharacterRegistry[i];

        if (TempPtr != NULL)
        {
            while (TempPtr != NULL)
            {
                free(TempPtr->name);
                free(TempPtr->movie);
                NextPtr = TempPtr->next_ptr;
                free(TempPtr);
                TempPtr = NextPtr;
            }
        }
    }
}

/* Remove an element from Hash Table */
int DeleteNode(DISNEY_CHARACTER *CharacterRegistry[])
{
    char LookupName[100] = {};
    int result = 0;

    printf("Enter the name of the Disney Character to delete from the CharacterRegistry: ");
    fgets(LookupName, sizeof(LookupName), stdin);
    if (LookupName[strlen(LookupName) - 1] == '\n')
    {
        LookupName[strlen(LookupName) - 1] = '\0';
    }

    int HashIndex = CalculateHashIndex(LookupName);

    /* Get linked list at key in array */
    DISNEY_CHARACTER *TempPtr = CharacterRegistry[HashIndex];
    DISNEY_CHARACTER *PrevPtr = NULL;
 
    /* This array index does not have a linked list; therefore, no keys */
    if (TempPtr == NULL)
    {
        printf("\n\nDisney Character %s does not exist in the CharacterRegistry\n\n", LookupName);
        result = 0;
    }
    else
    {
        while (TempPtr != NULL)
        {
            if (strcmp(TempPtr->name, LookupName) == 0)
            {
                /* If the node being deleted is the head node */
                if (TempPtr == CharacterRegistry[HashIndex])
                {
                    /* The node the head was pointing at is now the head */
                    CharacterRegistry[HashIndex] = TempPtr->next_ptr;
                    printf("\nDisney Character %s has been deleted from the CharacterRegistry\n\n", TempPtr->name);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                /* Found node to be deleted - node is not the head */
                else
                {
                    PrevPtr->next_ptr = TempPtr->next_ptr;
                    printf("\nDisney Character %s has been deleted from the CharacterRegistry\n\n", TempPtr->name);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                result = 1;
            }
            /* this is not the node that needs to be deleted but save */
            /* its info and move to the next node in the linked list  */
            else
            {
                PrevPtr = TempPtr;
                TempPtr = TempPtr->next_ptr;
            }
        }
        if (result == 0)
        {
            printf("\n\nDisney Character %s does not exist in the CharacterRegistry\n\n", LookupName);
        }
    }

    return result;
}

void DisplayHashTable(DISNEY_CHARACTER *CharacterRegistry[])
{
    int i;
    DISNEY_CHARACTER *TempPtr = NULL;
    
    for (i = 0; i < HASHTABLESIZE; i++)
    {
        TempPtr = CharacterRegistry[i];

        printf("\nCharacterRegistry[%d]-", i);
        
        if (TempPtr != NULL)
        {
            while (TempPtr != NULL)
            {
                printf("%s|", TempPtr->name);
                TempPtr = TempPtr->next_ptr;
            }
        }
    }
}

void ShowByLetter(DISNEY_CHARACTER *CharacterRegistry[])
{
    int i;
    DISNEY_CHARACTER *TempPtr = NULL;
    char LookupLetter = 'A';

    printf("\n\nEnter a letter of the alphabet ");
    scanf(" %c", &LookupLetter);
    LookupLetter = toupper(LookupLetter);

    for (i = 0; i < HASHTABLESIZE; i++)
    {
        TempPtr = CharacterRegistry[i];

        if (TempPtr != NULL)
        {
            while (TempPtr != NULL)
            {
                if (toupper(TempPtr->name[0]) == LookupLetter)
                {
                    printf("%s\n", TempPtr->name);
                }
                TempPtr = TempPtr->next_ptr;
            }
        }
    }
}

void ShowByName(DISNEY_CHARACTER *CharacterCatalog[])
{
    DISNEY_CHARACTER *TempPtr = NULL;
    char LookupName[100] = {};
    int FoundIt = 0;

    printf("\n\nEnter Disney character's name: ");
    scanf("%s", LookupName);

    #if TIMING
    clock_t start, end;
    start = clock();
    #endif

    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        TempPtr = CharacterCatalog[i];

        if (TempPtr != NULL)
        {
            while (TempPtr != NULL)
            {
                if (strcmp(TempPtr->name, LookupName) == 0)
                {
                    #if TIMING
                    end = clock();
                    printf("\n\nSearch took %ld tics\n\n", end - start);
                    #endif

                    FoundIt = 1;
                    printf("\n\n%s\n", TempPtr->name);
                    printf("Movie\t\t%s\n", TempPtr->movie);
                    printf("Gender\t\t%c\n", TempPtr->gender);
                    printf("Movie Collections\t%.1f million\n", TempPtr->movieCollections);
                    printf("Debut Year\t%d\n", TempPtr->debutYear);
                    printf("Number of Songs\t%d\n", TempPtr->numberOfSongs);
                }
                TempPtr = TempPtr->next_ptr;
            }
        }
    }

    if (FoundIt == 0)
        printf("\n\nDisney character %s not found\n\n", LookupName);
}

void AddNewDisneyCharacter(DISNEY_CHARACTER *CharacterCatalog[])
{
    int HashIndex = 0;
    DISNEY_CHARACTER *NewNode;
    char TempBuffer[100] = {};

    NewNode = malloc(sizeof(DISNEY_CHARACTER));
    NewNode->next_ptr = NULL;

    printf("\n\nEnter new Disney character's name: ");
    fgets(TempBuffer, sizeof(TempBuffer), stdin);
    TempBuffer[strlen(TempBuffer) - 1] = '\0';
    NewNode->name = malloc(strlen(TempBuffer) * sizeof(char) + 1);
    strcpy(NewNode->name, TempBuffer);

    printf("\n\nEnter %s's movie: ", NewNode->name);
    fgets(TempBuffer, sizeof(TempBuffer), stdin);
    TempBuffer[strlen(TempBuffer) - 1] = '\0';
    NewNode->movie = malloc(strlen(TempBuffer) * sizeof(char) + 1);
    strcpy(NewNode->movie, TempBuffer);

    printf("\n\nEnter %s's gender (M/F): ", NewNode->name);
    scanf("%c", &(NewNode->gender));
    NewNode->gender = toupper(NewNode->gender);

    printf("\n\nEnter %s's movie collections in millions: ", NewNode->name);
    scanf("%f", &(NewNode->movieCollections));

    printf("\n\nEnter %s's debut year: ", NewNode->name);
    scanf("%d", &(NewNode->debutYear));

    printf("\n\nEnter %s's number of songs: ", NewNode->name);
    scanf("%d", &(NewNode->numberOfSongs));

    AddNode(NewNode, CharacterCatalog);
}


int ReadFileIntoHashTable(int argc, char *argv[], DISNEY_CHARACTER *CharacterRegistry[])
{
    FILE *FH = NULL;
    char FileLine[100] = {};
    char *token = NULL;
    int counter = 0;
    int HashIndex = 0;
    DISNEY_CHARACTER *NewNode;

    if (argc > 1)
    {
        FH = fopen(argv[1], "r");

        if (FH == NULL)
        {
            perror("Exiting ");
            exit(0);
        }

        while (fgets(FileLine, sizeof(FileLine) - 1, FH))
        {
            token = strtok(FileLine, "|");

            NewNode = malloc(sizeof(DISNEY_CHARACTER));
            NewNode->next_ptr = NULL;

            NewNode->name = malloc(strlen(token) * sizeof(char) + 1);
            strcpy(NewNode->name, token);

            token = strtok(NULL, "|");
            NewNode->movie = malloc(strlen(token) * sizeof(char) + 1);
            strcpy(NewNode->movie, token);

            token = strtok(NULL, "|");
            NewNode->gender = *token;

            token = strtok(NULL, "|");
            NewNode->movieCollections = atof(token);

            token = strtok(NULL, "|");
            NewNode->debutYear = atoi(token);

            token = strtok(NULL, "|");
            NewNode->numberOfSongs = atoi(token);

            AddNode(NewNode, CharacterRegistry);

            counter++;
        }
    }
    else
    {
        printf("File must be provided on the command line...exiting\n");
        exit(0);
    }

    fclose(FH);

    return counter;
}

int main(int argc, char *argv[])
{
    int MenuChoice = 0;
    int counter = 0;
    DISNEY_CHARACTER *CharacterRegistry[HASHTABLESIZE] = {};

    enum Menu {SHOWBYLETTER = 1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};

    counter = ReadFileIntoHashTable(argc, argv, CharacterRegistry);

    do
    {
        printf("\n\nCharacterRegistry Menu\n\n"
               "1. Show all Disney Characters in CharacterRegistry for a given letter\n"
               "2. Look up Disney Character by name\n"
               "3. How many Disney Characters are in the CharacterRegistry?\n"
               "4. Display the CharacterRegistry\n"
               "5. Add a new Disney Character\n"
               "6. Delete a Disney Character from the CharacterRegistry\n"
               "7. Exit\n\n"
               "Enter menu choice ");
    
        scanf("%d", &MenuChoice);
        printf("\n\n");

        switch (MenuChoice)
        {
            case SHOWBYLETTER:
                ShowByLetter(CharacterRegistry);
                break;
            case SHOWBYNAME:
                ShowByName(CharacterRegistry);
                break;
            case COUNT:
                printf("Your CharacterRegistry contains %d Disney Character\n", counter);
                break;
             case DISPLAY:
                DisplayHashTable(CharacterRegistry);
                break;
            case ADD:
                getchar(); 
                AddNewDisneyCharacter(CharacterRegistry);
                counter++;
                break;
            case DELETE:
                getchar();
                if (DeleteNode(CharacterRegistry))
                {
                    counter--;
                }
                break;
            case EXIT:
                break;
            default :
                printf("Invalid menu choice\n\n");
        }
    }
    while (MenuChoice != EXIT);

    FreeDynamicMemory(CharacterRegistry);

    return 0;
}

