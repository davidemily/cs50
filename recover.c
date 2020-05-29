#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCKSIZE 512
​
int inputError()
{
    printf("Usage: ./recover image\n");
    return 1;
}
​
int fileError(char filename[])
{
    printf("Unable to open file: %s\n", filename);
    return 1;
}
​
bool isJpegHeader(uint8_t buffer[])
{
    //logic given in walkthrough
    return buffer[0] == 0xff
        && buffer[1] == 0xd8
        && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0;
}
​
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        return inputError();
    }
​
    char* inputFile = argv[1];
​
    if(inputFile == NULL)
    {
        return inputError();
    }
​
    FILE* inputPtr = fopen(inputFile, "r");
    if(inputPtr == NULL)
    {
        return fileError(inputFile);
    }
​
    //initialize variables we need to file writing
    uint8_t buffer[BLOCKSIZE];
    char filename[8]; //xxx.jpg'\0'
    int jpegCounter = 0;
    FILE* outputPtr = NULL;
​
    //keep running while we can read from input file
    //&&
    //keep running while there is data to read and not end of file
    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputPtr) || feof(inputPtr)==0)
    {
​
        // if we found a JPEG
        if (isJpegHeader(buffer))
        {
            //if file is open, close it
            if(outputPtr!=NULL)
            {
                fclose(outputPtr);
            }
            sprintf(filename, "%03i.jpg", jpegCounter);
            outputPtr = fopen(filename, "w");
            jpegCounter++;
        }
​
        // if we have a file, write to it
        if (outputPtr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outputPtr);
        }
    }
​
    //we opened pointers to files
    //we need to close to prevent memory problems
    if(inputPtr!=NULL)
    {
        fclose(inputPtr);
    }
    if(outputPtr!=NULL)
    {
        fclose(outputPtr);
    }
    return 0;
}
