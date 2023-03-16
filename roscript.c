//basic c code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int flagPrint = 0;
    const char* input = NULL;
    int tapeSize = 1000;

    if (argc == 1){
        printf("Add an argument");
        return 0;
    }

    
    int done = 0;
    
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-p") == 0){
            flagPrint = 1;
        } else if (!done){
            input = argv[i];
            done = 1;
        }
    }

    int tape = [tapeSize];
    int tapePointer = 0;
    for (int i = 0; i < tapeSize; i++){
        tape[i] = 0;
    }

    int instructionPointer = 0;
    char currentInstruction = input[instructionPointer];
    int pocket = 0;
    while (currentInstruction != '\0'){
        if (currentInstruction == '<'){
            tapePointer--;
        } else if (currentInstruction == '>'){
            tapePointer++;
        } else if (currentInstruction == '+'){
            tape[tapePointer]++;
        } else if (currentInstruction == '-'){
            tape[tapePointer]--;
        } else if (currentInstruction == '.'){
            printf("%c", tape[tapePointer]);
        } else if (currentInstruction == ','){
            tape[tapePointer] = getchar();
        } else if (currentInstruction == '['){
            if (tape[tapePointer] == 0){
                int bracketCount = 1;
                while (bracketCount != 0){
                    instructionPointer++;
                    if (input[instructionPointer] == '['){
                        bracketCount++;
                    } else if (input[instructionPointer] == ']'){
                        bracketCount--;
                    }
                }
            }
        } else if (currentInstruction == ']'){
            int bracketCount = 1;
            while (bracketCount != 0){
                instructionPointer--;
                if (input[instructionPointer] == ']'){
                    bracketCount++;
                } else if (input[instructionPointer] == '['){
                    bracketCount--;
                }
            }
        } else if (currentInstruction == '{'){
            pocket = tape[tapePointer];
        } else if (currentInstruction == '}'){
            tape[tapePointer] = pocket;
        } else if (currentInstruction == '='){
            int tempPointer = tapePointer;
            tempPointer++;
            while (tape[tempPointer] != 0){ //because 0 is /0 and technically we're using int array
                tempPointer++;
            }
            int length = tempPointer - tapePointer+1;
            char data[length];
            for (int i = 1; i < length; i++){
                data[i] = tape[tapePointer+i];
            }
            FILE * fptr;
            char* saveName = "a.rsd";
            saveName[0] = (char)tape[tapePointer];
            fptr = fopen(saveName, "w");
            if (fptr == NULL){
                printf("Error!");
                exit(1);
            }
            fputs(data, fptr);
            fclose(fptr);
        } else if (currentInstruction == '_'){
            FILE * fptr;
            char* saveName = "a.rsd";
            saveName[0] = (char)tape[tapePointer];
            fptr = fopen(saveName, "r");
            if (fptr == NULL){
                printf("Error!");
                exit(1);
            }
            int index = 1;
            do {
                ch = fgetc(fptr);
                tape[tapePointer+index] = ch;
                index++;
            } while (ch != EOF);
            fclose(fptr);
        } 
        
        
        instructionPointer++;
        currentInstruction = input[instructionPointer];
    }
    

    printf("%s", input);
    return 0;
}
