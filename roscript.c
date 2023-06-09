//basic c code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



void debug(int flag, int tape[], int furthest, const char* input){
    if (flag){
        for (int i = 0; i < furthest; i++){
            printf("%c", tape[i]);
            printf(" | ");
        }
        printf("%c\n", tape[furthest]);
    }
}


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
    int furthest = 0;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-p") == 0){
            flagPrint = 1;
        } else if (!done){
            if (strstr(argv[i], ".rse") != NULL){
                FILE * fptr;
                fptr = fopen(argv[i], "r");
                if (fptr == NULL){
                    printf("File not found");
                    exit(1);
                }
                //putting file into string
                fseek(fptr, 0, SEEK_END);
                int fsize = ftell(fptr);
                fseek(fptr, 0, SEEK_SET);
                char *string = malloc(sizeof(char) * (fsize + 1));

                char c;
                int index = 0;
                while ((c = fgetc(fptr)) != EOF){
                    string[index] = c;
                    index++;
                }
                string[index] = '\0';

                fclose(fptr);
                input = string;
                done = 1;
            } else {
                input = argv[i];
                done = 1;
            }    
        }
    }

    int tape[tapeSize];
    int tapePointer = 0;
    for (int i = 0; i < tapeSize; i++){
        tape[i] = 0;
    }

    int instructionPointer = 0;
    char currentInstruction = input[instructionPointer];
    int pocket = 0;
    while (currentInstruction != '\0' && currentInstruction != EOF){ 
        if (currentInstruction == '<'){
            tapePointer--;
        } else if (currentInstruction == '>'){
            tapePointer++;
            if (tapePointer > furthest){
                furthest = tapePointer;
                debug(flagPrint, tape, furthest, input);
            }
        } else if (currentInstruction == '+'){
            tape[tapePointer]++;
            debug(flagPrint, tape, furthest, input);
        } else if (currentInstruction == '-'){
            tape[tapePointer]--;
            debug(flagPrint, tape, furthest, input);
        } else if (currentInstruction == '.'){
            printf("%c", tape[tapePointer]);
        } else if (currentInstruction == ','){
            tape[tapePointer] = getchar();
            if (!(input[instructionPointer+1] == '>' && input[instructionPointer+2] == ',')){
                int c;
                while ( (c = getchar()) != '\n' && c != EOF ) { }
            }
            debug(flagPrint, tape, furthest, input);
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
            instructionPointer--;
        } else if (currentInstruction == '{'){
            pocket = tape[tapePointer];
        } else if (currentInstruction == '}'){
            tape[tapePointer] = pocket;
            debug(flagPrint, tape, furthest, input);
        } else if (currentInstruction == '='){
            int tempPointer = tapePointer;
            while (tape[tempPointer] != 0){ //because 0 is /0 and technically we're using int array
                tempPointer++;
            }
            int length = tempPointer - tapePointer+1-1;
            char data[length];
            for (int i = 0; i < length; i++){
                data[i] = tape[tapePointer+i+1];
            }
            FILE * fptr;
            
            char saveName[] = "a.rsd";
            saveName[0] = tape[tapePointer];
            
            fptr = fopen(saveName, "w");
            if (fptr == NULL){
                printf("You can't save to this file");
                exit(1);
            }
            fputs(data, fptr);
            fclose(fptr);
        } else if (currentInstruction == '_'){
            FILE * fptr;
            char saveName[] = "a.rsd";
            saveName[0] = tape[tapePointer];
            fptr = fopen(saveName, "r");
            if (fptr == NULL){
                printf("You can't load from this file");
                exit(1);
            }
            int index = 1;
            char ch;
            do {
                ch = fgetc(fptr);
                tape[tapePointer+index] = ch;
                if (tapePointer+index > furthest){
                    furthest = tapePointer+index;
                }
                index++;
            } while (ch != EOF);
            fclose(fptr);
            debug(flagPrint, tape, furthest ,input);
        }  else if (currentInstruction == '^'){
            sleep(tape[tapePointer]);
            
        } else if (currentInstruction == '#'){
            int length = tape[tapePointer];
            for(int i = 0; i < length; i++){
                tape[tapePointer+i+1] = 0;
            }
            if (furthest <= tapePointer+length){
                furthest = tapePointer;
            }
            debug(flagPrint, tape, furthest, input);
        }         
        
        instructionPointer++;
        currentInstruction = input[instructionPointer];
    }
    
    return 0;
}


