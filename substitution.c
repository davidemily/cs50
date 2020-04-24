#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if(strlen(argv[1])!=26)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string enteredString = argv[1];
    char key[26];

    bool usedAlready[26];
    for(int i=0; i<26; i++)
    {
        usedAlready[i] = false;
    }

    for(int i=0; i<26; i++)
    {
        if(isalpha(enteredString[i]))
        {
            if(isupper(enteredString[i]))
            {
                if(usedAlready[enteredString[i] - 'A'] == true)
                {
                    printf("Key must not contain duplicate letters: %c\n", enteredString[i]);
                    return 1;
                }
                else
                {
                    usedAlready[enteredString[i]-'A'] = true;
                    key[i] = enteredString[i]-'A';
                }
            }
            else
            {
                if(usedAlready[enteredString[i] - 'a'] == true)
                {
                    printf("Key must not contain duplicate letters: %c\n", enteredString[i]);
                    return 1;
                }
                else
                {
                    usedAlready[enteredString[i]-'a'] = true;
                    key[i] = enteredString[i]-'a';
                }
            }
        }
        else
        {
            printf("Please use only letters\n");
            return 1;
        }
    }


    string plainText = get_string("plaintext: ");

    string cipherText = plainText;

    for(int i=0; i<strlen(plainText); i++)
    {
        if(isalpha(plainText[i]))
        {
            if(isupper(plainText[i]))
            {
                cipherText[i] = (key[plainText[i]-'A'] + 'A');
            }
            else
            {
                cipherText[i] = (key[plainText[i]-'a'] + 'a');
            }
        }
        else
        {
            cipherText[i] = plainText[i];
        }
    }

    printf("ciphertext: %s\n", cipherText);
    return 0;
}
