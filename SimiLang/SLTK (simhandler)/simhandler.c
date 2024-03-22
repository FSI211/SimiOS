#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LENGTH 1000


void handleDo() {
    printf("Do something!\n");
}

void handleEnd() {
    printf("End something!\n");
}

void handleCall() {
    printf("Do something after call!\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    char code[MAX_CODE_LENGTH];

    if (argc != 3) {
        printf("Usage: %s <action> <input_filename>\n", argv[0]);
        printf("Actions: -c (compile)\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-sys64") == 0) {
        printf("64 mode not supported!\n");
    } 
    else if (strcmp(argv[1], "-sys32") == 0) {
        
    } 
    else {
        printf("Invalid action specified.\n");
        return EXIT_FAILURE;
    }

    char *file_extension = strrchr(argv[2], '.');
    if (file_extension == NULL || strcmp(file_extension, ".simx32") != 0) {
        printf("Error: Input file must have .simx32 extension.\n");
        return EXIT_FAILURE;
    }


    input_file = fopen(argv[2], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }


    while (fgets(code, MAX_CODE_LENGTH, input_file) != NULL) {
        if (strstr(code, "do") != NULL) {
            handleDo();
        }

        if (strstr(code, "end") != NULL) {
            handleEnd();
        }

        if (strstr(code, "call") != NULL) {
            handleCall();
        }
    }
    fclose(input_file);

    return EXIT_SUCCESS;
}