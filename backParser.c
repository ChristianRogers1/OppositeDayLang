#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseFile(const char* program);
char* readFile(const char* filePath);
void writeFile(const char* filePath, const char* program);

int main(int argc, char** argv) {
    char* program = readFile("sample.etisoppo");
    char* reverse = reverseFile(program);
    writeFile("out.c", reverse);

    /*char* compileVal = (char*)malloc(256);
    strcpy(compileVal, "gcc out.c -o ");
    strcat(compileVal, argv[2]);*/

    int compileFailed = system("gcc out.c -o out.exe");
    if (compileFailed == 0) {
        printf("Compilation Successful!\n");
        
        int executeFailed = system("out.exe");
        if (executeFailed == 0) {
            printf("Execution Successful!\n");
        } else {
            printf("Execution Failed: %s", executeFailed);
        }
    } else {
        printf("Compilation Failed: %s", compileFailed);
    }
    /*free(compileVal);*/
    free(program);
    free(reverse);
    return 0;
}

void writeFile(const char* filePath, const char* program) {
    FILE* file = NULL;

    file = fopen("out.c", "w");
    if (file == NULL) {
        printf("Failed to write to file %s\n", filePath);
        return;
    }

    fprintf(file, "%s", program);

    fclose(file);
}

char* reverseFile(const char* program) {
    char* reverseProgram = (char*)malloc(sizeof(program));
    if (reverseProgram == NULL) {
        printf("Failed to allocate memory, reverseProgram.");
        return NULL;
    }

    int index = 0;
    int reverseIndex = 0;
    int nextIndex = 0;
    int forward = 1;
    while (program[index] != '\0') {
        if (forward) {
            
            if (program[index] == '\n' || program[index] == '\0') {
                nextIndex = index + 1;
                forward = 0;
                index--;
            }
            index++;
        } else {
            reverseProgram[reverseIndex] = program[index];
            index--;
            if (program[index] == '\n' || index < 0) {
                index = nextIndex;
                forward = 1;
            }
            reverseIndex++;
        }
    }

    reverseProgram[reverseIndex] = '\n';
    reverseIndex++;
    while (program[index] != '\n') {
        index--;
        reverseProgram[reverseIndex] = program[index];
        reverseIndex++;
    }
    reverseProgram[reverseIndex] = '\0';

    return reverseProgram;
}

char* readFile(const char* filePath) {
    FILE* file = NULL;
    int size = 0;
    char* buffer = NULL;

    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Failed to Open the File %s\n", filePath);
        return NULL;
    }

    char ch;
    while((ch = fgetc(file)) != EOF) {(size)++;}

    buffer = (char*)malloc((size+1) * sizeof(char));
    if (buffer == NULL) {
        fclose(file);
        printf("Failed to allocate memory");
        return NULL;
    }

    rewind(file);

    int i = 0;
    while((ch = fgetc(file)) != EOF) {
        if (i < size) {
            switch (ch) {
                case '{' : buffer[i] = '}'; break;
                case '}' : buffer[i] = '{'; break;
                case '(' : buffer[i] = ')'; break;
                case ')' : buffer[i] = '('; break;
                case '[' : buffer[i] = ']'; break;
                case ']' : buffer[i] = '['; break;
                case '<' : buffer[i] = '>'; break;
                case '>' : buffer[i] = '<'; break;
                case '+' : buffer[i] = '-'; break;
                case '-' : buffer[i] = '+'; break;
                //case '*' : buffer[i] = '/'; break;
                //case '/' : buffer[i] = '*'; break;
                default: buffer[i] = ch; break;
            }
        }
        i++;
    }
    buffer[size] = '\0';

    return buffer;
}