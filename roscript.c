//basic c code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //print hello world
    if (argc == 1){
        printf("Add an argument");
        return 0;
    }

    int flagPrint = 0;
    int done = 0;
    const char* input = NULL;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-p") == 0){
            flagPrint = 1;
        } else if (!done){
            input = argv[i];
            done = 1;
        }
    }
    

    printf("%s", input);
    return 0;
}
