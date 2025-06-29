#include <stdio.h>
#include <string.h>
#include "locker.h"

int main() {
    char basePath[1024];
    char key;

    printf("Please Enter the Full Path of the Folder: ");
    fgets(basePath, sizeof(basePath), stdin);
    basePath[strlen(basePath) - 1] = '\0';

    // Normalize the path
    for (int i = 0; i < basePath[i] != '\0'; i++)
    {
        if (basePath[i] == '\\')
        {
            basePath[i] = '/';
        }
        
    }
    
    printf("Please Enter the Key (char): ");
    scanf(" %c", &key);

    processDirectory(basePath, key);

    return 0;
}
