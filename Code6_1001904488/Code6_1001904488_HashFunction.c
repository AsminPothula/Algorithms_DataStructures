#include <stdio.h>
#include <string.h>

#define HASHTABLESIZE 10

int MyHashFunction(char *HashValue) 
{
    int sum = 0;
    for (int i = 0; i < strlen(HashValue); i++) 
    {
        sum += HashValue[i];
    }
    //int hashResult = sum % HASHTABLESIZE;
    //return hashResult;
    return sum % HASHTABLESIZE;
}

int main(void) 
{
    char HashValue[20];
    
    printf("Enter value: ");
    
    fgets(HashValue, sizeof(HashValue), stdin);
    
    if (HashValue[strlen(HashValue) - 1] == '\n') 
    {
        HashValue[strlen(HashValue) - 1] = '\0';
    }
    
    int hashResult = MyHashFunction(HashValue);
    printf("\nThe hash value for %s is %d\n", HashValue, hashResult);
    
    return 0;
}
