#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    char* first = "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <unistd.h>\nint main(int argc, char const *argv[]){\n    int flagPrint = 0;\n    const char* input = \"";

    char* second = "\";\nint tapeSize = 1000;\nint furthest = 0;\nint tape[tapeSize];\nint tapePointer = 0;\nfor (int i = 0; i < tapeSize; i++){\ntape[i] = 0;\n}\nint instructionPointer = 0;\nchar currentInstruction = input[instructionPointer];\nint pocket = 0;\nwhile (currentInstruction != '\\0' && currentInstruction != EOF){\n if (currentInstruction == '<'){\n tapePointer--;\n } else if (currentInstruction == '>'){\n tapePointer++;\n if (tapePointer > furthest){\n furthest = tapePointer;\n }\n } else if (currentInstruction == '+'){\n tape[tapePointer]++;\n } else if (currentInstruction == '-'){\n tape[tapePointer]--;\n } else if (currentInstruction == '.'){\n printf(\"%c\", tape[tapePointer]);\n } else if (currentInstruction == ','){\n tape[tapePointer] = getchar();\n if (!(input[instructionPointer+1] == '>' && input[instructionPointer+2] == ',')){\n int c;\n while ( (c = getchar()) != '\\n' && c != EOF ) { } }\n } else if (currentInstruction == '['){\n if (tape[tapePointer] == 0){\n int bracketCount = 1;\n while (bracketCount != 0){\n instructionPointer++;\n if (input[instructionPointer] == '['){\n bracketCount++;\n } else if (input[instructionPointer] == ']'){\n bracketCount--;\n }\n }\n }\n } else if (currentInstruction == ']'){\n int bracketCount = 1;\n while (bracketCount != 0){\n instructionPointer--;\n if (input[instructionPointer] == ']'){\n bracketCount++;\n } else if (input[instructionPointer] == '[')\n{ bracketCount--; }\n }\n instructionPointer--; } else if (currentInstruction == '{'){\n pocket = tape[tapePointer];\n } else if (currentInstruction == '}'){\n tape[tapePointer] = pocket;\n } else if (currentInstruction == '='){\n int tempPointer = tapePointer;\n while (tape[tempPointer] != 0){\n //because 0 is /0 and technically we're using int array tempPointer++;\n }\n int length = tempPointer - tapePointer+1-1;\n char data[length];\n for (int i = 0; i < length; i++){\n data[i] = tape[tapePointer+i+1];\n } FILE * fptr;\n char saveName[] = \"a.rsd\";\n saveName[0] = tape[tapePointer];\n fptr = fopen(saveName, \"w\");\n if (fptr == NULL){\n printf(\"You can't save to this file\");\n exit(1);\n }\n fputs(data, fptr);\n fclose(fptr);\n } else if (currentInstruction == '_'){\n FILE * fptr;\n char saveName[] = \"a.rsd\";\n saveName[0] = tape[tapePointer];\n fptr = fopen(saveName, \"r\");\n if (fptr == NULL){\n printf(\"You can't load from this file\");\n exit(1);\n }\n int index = 1;\n char ch;\n do {\n ch = fgetc(fptr);\n tape[tapePointer+index] = ch;\n if (tapePointer+index > furthest){\n furthest = tapePointer+index;\n }\n index++;\n }\n while (ch != EOF);\n fclose(fptr);\n } else if (currentInstruction == '^'){\n sleep(tape[tapePointer]);\n } else if (currentInstruction == '#'){\n int length = tape[tapePointer];\n for(int i = 0; i < length; i++){\n tape[tapePointer+i+1] = 0;\n }\n if (furthest <= tapePointer+length){\n furthest = tapePointer;\n }\n }\n instructionPointer++;\n currentInstruction = input[instructionPointer];\n }\n return 0;\n  }";
    
    const char* input = NULL;
    const char* name = NULL;
    int keep = 0;
    for (int i = 1; i < argc; i++){
        if (i == 1){
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
            } else {
                input = argv[i];
            }    
        } else {
            if (strcmp(argv[i], "-c") == 0){
                keep = 1;
            } else {
                int len = strlen(argv[i]);
                char* string2 = malloc(sizeof(char) * (len + 1));
                strcpy(string2, argv[i]);
                name = string2;
            }
        }
    }   
    

    char hugeString[strlen(first) + strlen(input) + strlen(second) + 10];
    strcpy(hugeString, first);
    strcat(hugeString, input);
    strcat(hugeString, second);
    FILE * fptr;
    if (name == NULL) {
        name = "a";
    }
    char tempName[strlen(name) + 3];
    strcpy(tempName, name);
    strcat(tempName, ".c");
    fptr = fopen(tempName, "w");
    if (fptr == NULL){
        printf("You can't save to this file");
        exit(1);
    }
    fputs(hugeString, fptr);
    fclose(fptr);

    char sysString[100] = "gcc ";
    strcat(sysString, name);
    strcat(sysString, ".c -o ");
    strcat(sysString, name);
    
    system(sysString);

    if (!keep){
        char sysString2[100] = "del ";
        strcat(sysString2, name);
        strcat(sysString2, ".c");
        system(sysString2);
    }
    return 0;

}
